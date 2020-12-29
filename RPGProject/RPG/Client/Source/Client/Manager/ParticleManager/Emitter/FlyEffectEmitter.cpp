// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyEffectEmitter.h"
#include "GameFramework/Character.h"
#include "Character/ServerCharacter.h"
// ��������

// CS3����

#pragma optimize("", off)
AFlyEffectEmitter::AFlyEffectEmitter()
{
	
}

void AFlyEffectEmitter::BeginPlay()
{
	// �������Ч��ͳͳ����Tick
	PrimaryActorTick.bCanEverTick = true;

	// �󶨷��й�Ч�ִ��¼�
	OnEffectArrived.AddDynamic(this, &AFlyEffectEmitter::OnFlyFinished);

	Super::BeginPlay();
}

void AFlyEffectEmitter::InitFromConfig()
{
	Super::InitFromConfig();
	OtherEffectData			= &(EffectEmitterData->OtherEffectData);

	// �ڶ��׶��˶����
	bCanSpecialMove			= OtherEffectData->bCanSpecialMove;
	TransformationDistance	= OtherEffectData->TransformationDistance;
	RisingDistance			= OtherEffectData->RisingDistance;

	// �ٶ�
	FlySpeed				= OtherEffectData->FlySpeed;
	bFlyOfTime				= OtherEffectData->bFlyOfTime;
}

void AFlyEffectEmitter::InitEmitterTransform()
{
	ACharacter* Character = Cast<ACharacter>(FirstTarget);

	//����λ��
	FTransform Transform = Character && FirstTransform->Socket != "" ? Character->GetMesh()->GetSocketTransform(FName(*FirstTransform->Socket)) : FirstTarget->GetActorTransform();
	//����bLocationOnWorld��������λ��
	FVector Location;
	if (FirstTransform->bLocationOnWorld)
	{
		Location = FirstTransform->Transform.GetLocation();
	}
	else
	{
		Location = Transform.TransformPosition(FirstTransform->Transform.GetLocation());
	}
	//����bRotationOnWorld��������λ��
	FRotator Rotation;
	if (FirstTransform->bRotationOnWorld)
	{
		Rotation = FirstTransform->Transform.GetRotation().Rotator();
	}
	else
	{
		Rotation = Transform.TransformRotation(FirstTransform->Transform.GetRotation()).Rotator();
	}
	SetActorLocation(Location);
	SetActorRotation(Rotation);
	//���󶨵Ĺ�ЧΪ���ñ�����
	SetActorScale3D(FirstTransform->Transform.GetScale3D());

	//������ʼ��
	SourcePos = GetActorLocation();
	//����Ŀ���
	GetFlyTargetPos(true);

	//���ó���
	if (FirstTarget != SecondTarget)
	{
		FRotator LookRotation = FRotationMatrix::MakeFromX(TargetPos - FirstTarget->GetActorLocation()).Rotator();
		SetActorRotation(LookRotation);
	}

	//�Ƿ�������ڶ��׶��˶�
	if ((TargetPos - GetActorLocation()).Size() < TransformationDistance && 
		TransformationDistance > 0.0f && RisingDistance > 0.0f)
	{
		bCanSpecialMove = false;
	}

	//�����ƶ�ƽ̨�������
	if (CheckAndSetEmitterBase() && Cast<AServerCharacter>(ParentActor)->GetSelfEntity())
	{
		AttachToActor(ParentActor, FAttachmentTransformRules::KeepWorldTransform);
	}
	
	////�����������Ӵ˹�Ч
	//if (Cast<AGameCharacter>(FirstTarget) && EffectData->bBindingVisibility)
	//{
	//	Cast<AGameCharacter>(FirstTarget)->GetPerformanceComponent()->AddEffect(UID);
	//}

	//��·����Դ�Ĺ�Ч����ͼ�г�ʼ��λ��
	if (Spline)
	{
		InitSplineTransform();
	}
}

FVector AFlyEffectEmitter::GetFlyTargetPos(bool bInit /* = false */)
{

	// ����Ŀ������ص㣬�ж�SecondTransform��������������
	if ((SecondTransform->bLocationOnWorld || !SecondTransform->bBindSocket) && !bInit)
	{
		return TargetPos;
	}

	if (IsValid(SecondTarget))
	{
		ACharacter* Character = Cast<ACharacter>(SecondTarget);
		//ˢ��Ŀ��㣬�Լ���λ�ü������ƫ��
		FTransform Transform;
		Transform = Character && SecondTransform->Socket != "" ? Character->GetMesh()->GetSocketTransform(FName(*SecondTransform->Socket)) : SecondTarget->GetActorTransform();
		TargetPos = Transform.TransformPosition(SecondTransform->Transform.GetLocation());
	}

	if (!SecondTransform->bBindSocket && SecondTransform->bLocationOnWorld)
	{
		return TargetPos = SecondTransform->Transform.GetLocation();
	}

	return TargetPos;
}

FVector AFlyEffectEmitter::GetFlySourcePos(bool bInit /* = false */)
{
	// ����Ŀ������ص㣬�ж�SecondTransform��������������
	if ((FirstTransform->bLocationOnWorld) && !bInit)
	{
		return SourcePos;
	}

	if (IsValid(FirstTarget))
	{
		ACharacter* Character = Cast<ACharacter>(FirstTarget);
		//ˢ��Ŀ��㣬�Լ���λ�ü������ƫ��
		FTransform Transform;
		Transform = Character && FirstTransform->Socket != "" ? Character->GetMesh()->GetSocketTransform(FName(*FirstTransform->Socket)) : FirstTarget->GetActorTransform();
		SourcePos = Transform.TransformPosition(FirstTransform->Transform.GetLocation());
	}
	
	if (FirstTransform->bLocationOnWorld)
	{
		return SourcePos = FirstTransform->Transform.GetLocation();
	}

	return SourcePos;
}

void AFlyEffectEmitter::PlayTriggerParticle()
{
	for (auto TriggerID : OtherEffectData->TriggerEffect)
	{
		UClientGameInstance::Instance->ParticleManager->PlayParticle(TriggerID, 0.0f, FirstTarget, SecondTarget);
	}
}

void AFlyEffectEmitter::OnFlyFinished()
{
	PlayTriggerParticle();
}

void AFlyEffectEmitter::Tick(float DeltaTime)
{
	if (bPlaying)
	{
		//ˢ��Ŀ���
		GetFlyTargetPos();

		//ˢ���ƶ�ƽ̨��ֻ�г�ʼ����ʱ�����ƶ�ƽ̨�ϲż��
		if (ParentActor && !CheckAndSetEmitterBase())
		{
			DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}

		//���ݷ���ʱ������ٶ�
		if (bFlyOfTime)
		{
			FlySpeed = (GetActorLocation() - FVector(0, 0, TotalRisingOffset) - TargetPos).Size() / (OtherEffectData->FlyTime - CurrentTime);
		}

		switch (FlyType)
		{
		case FLY_TYPE::NORMAL:
			NormalMove(DeltaTime);
			break;
		case FLY_TYPE::SECOND:
			SecondMove(DeltaTime);
			break;
		default:
			break;
		}
	}
	
	AEffectEmitter::Tick(DeltaTime);
}

void AFlyEffectEmitter::NormalMove(float DeltaTime, FVector RisingOffset /*= FVector(0,0,0)*/)
{

	//λ�úͷ���
	FVector Location;
	FRotator Rotation;

	float MoveLength = FlySpeed * DeltaTime;
	float CurrentLength = 60;//�������Ϊ60��Ӧ��1���Ľ�����ֱ��Ϊ68��60��֤���ԽӴ���

	// �ڶ�֡�������Ҳ���Ա�֤��ײ��������
	while (MoveLength - CurrentLength > 0)
	{
		// ���糯��
		Rotation = FRotationMatrix::MakeFromX(TargetPos - GetActorLocation()).Rotator();
		
		if (ParentActor)
		{
			// ������ƶ�ƽ̨����Գ���
			FQuat Quaternion = ParentActor->GetActorTransform().InverseTransformRotation(Rotation.Quaternion());
			// Delta�����λ���ƶ�����Ҫ��������
			Location = Quaternion.GetAxisX() * CurrentLength * GetActorRelativeScale3D();
			// ʵ�ʵ����λ�ø���
			Location += RootComponent->RelativeLocation;
			// ���ó��򣬼�-90��ƫ��
			Rotation = (Quaternion * FRotator(0, -90, 0).Quaternion()).Rotator();
			
			SetActorRelativeTransform(FTransform(Rotation, Location, GetActorRelativeScale3D()));
		}
		else
		{
			// λ��
			Location = (TargetPos - GetActorLocation() + FVector(0, 0, TotalRisingOffset)).GetSafeNormal() * CurrentLength + GetActorLocation();

			// ���ó���
			Rotation = (Rotation.Quaternion() * FRotator(0, -90, 0).Quaternion()).Rotator();

			SetActorLocationAndRotation(Location, Rotation);
		}

		MoveLength -= CurrentLength;

		// ����Ƿ��Ѿ�����,�����ص��¼�
		if ((GetActorLocation() - TargetPos - FVector(0, 0, TotalRisingOffset)).Size() < FlySpeed * DeltaTime)
		{
			SetActorLocation(TargetPos);
			OnEffectArrived.Broadcast();
			Stop();
			return;
		}
	}

	// ���糯��
	Rotation = FRotationMatrix::MakeFromX(TargetPos - GetActorLocation()).Rotator();

	if (ParentActor)
	{
		// ������ƶ�ƽ̨����Գ���
		FQuat Quaternion = ParentActor->GetActorTransform().InverseTransformRotation(Rotation.Quaternion());
		// Delta�����λ���ƶ�����Ҫ��������
		Location = (Quaternion.GetAxisX() * MoveLength + Quaternion.GetAxisZ() * RisingOffset.Z) * GetActorRelativeScale3D();
		// ʵ�ʵ����λ�ø���
		Location += RootComponent->RelativeLocation;
		// ���ó��򣬼�-90��ƫ��
		Rotation = (Quaternion * FRotator(0, -90, 0).Quaternion()).Rotator();
		// �����׶����ó���
		if (FlyType == FLY_TYPE::SECOND)
		{
			GetSecondMoveRotation(Rotation);
		}

		SetActorRelativeTransform(FTransform(Rotation, Location, GetActorRelativeScale3D()));
	}
	else
	{
		// λ��
		Location = (TargetPos - GetActorLocation() + FVector(0, 0, TotalRisingOffset)).GetSafeNormal() * MoveLength + RisingOffset + GetActorLocation();

		// ���ó���
		Rotation = (Rotation.Quaternion() * FRotator(0, -90, 0).Quaternion()).Rotator();

		if (FlyType == FLY_TYPE::SECOND)
		{
			GetSecondMoveRotation(Rotation);
		}

		SetActorLocationAndRotation(Location, Rotation);
	}

	// ����Ƿ��Ѿ�����,�����ص��¼�
	if ((GetActorLocation() - TargetPos - FVector(0, 0, TotalRisingOffset)).Size() < FlySpeed * DeltaTime)
	{
		SetActorLocation(TargetPos);
		OnEffectArrived.Broadcast();
		Stop();
		return;
	}

	// �ۼ������߶�
	TotalRisingOffset += RisingOffset.Z;

	// �ж��Ƿ�Ҫ������һ�׶�
	EnterNextMove();
}

void AFlyEffectEmitter::SecondMove(float DeltaTime)
{
	LastRisingPercent = RisingPercent;
	// ���㵱ǰ�Ľ���
	if (bFlyOfTime)
	{
		RisingPercent = (CompletedTime - (OtherEffectData->FlyTime - CurrentTime)) / CompletedTime;
	}
	else
	{
		float CurrentPercent = 1 - (GetActorLocation() - FVector(0, 0, FMath::Sin(RisingPercent * PI) * RisingDistance) - TargetPos).Size() / TransformationDistance;

		if (CurrentPercent> RisingPercent)
		{
			RisingPercent = CurrentPercent;
		}
	}

	// �����ľ���
	float RisingLength = (FMath::Sin(RisingPercent * PI) - FMath::Sin(LastRisingPercent * PI)) * RisingDistance;
	
	NormalMove(DeltaTime, FVector(0, 0, RisingLength));
}

void AFlyEffectEmitter::GetSecondMoveRotation(FRotator& OutRotation)
{
	// б��
	float k = FMath::Cos(RisingPercent * PI) * (RisingDistance / (GetActorLocation() - FVector(0, 0, TotalRisingOffset) - TargetPos).Size());
	float Angle = -atan(k) * 180 / PI;
	OutRotation.Roll = Angle;
}

void AFlyEffectEmitter::EnterNextMove()
{
	// �ж��Ƿ�Ҫ�������߽׶�
	if (bCanSpecialMove && (GetActorLocation() - TargetPos).Size() < TransformationDistance)
	{
		FlyType = FLY_TYPE::SECOND;
		bCanSpecialMove = false;

		// ���ŵڶ��׶ζ���
		if (AnimAsset.Num() > 1 && SKComponent)
		{
			SKComponent->PlayAnimation(AnimAsset[1], true);
		}

		if (bFlyOfTime)
		{
			CompletedTime = OtherEffectData->FlyTime - CurrentTime;
		}
	}
}

bool AFlyEffectEmitter::CheckAndSetEmitterBase()
{
	// ��ʩ���ߺ�Ŀ�궼����ͬ���ƶ�ƽ̨��ʱ���󶨹�Ч���ƶ�ƽ̨��
	AServerCharacter* SFTarget = Cast<AServerCharacter>(FirstTarget);
	AServerCharacter* SSTarget = Cast<AServerCharacter>(SecondTarget);
	// ��ʼ����ʱ���ж�����Ŀ���Parent������ֻ�ж�Ŀ��
	if (!ParentActor)
	{
		if (SFTarget && SSTarget && SFTarget->GetSelfEntity() && SSTarget->GetSelfEntity() && SFTarget->GetSelfEntity()->ParentID() != 0
			&& SFTarget->GetSelfEntity()->ParentID() == SSTarget->GetSelfEntity()->ParentID())
		{
			AActor* MovingPlatform = SFTarget->GetSelfEntity()->Parent()->Actor();
			if (MovingPlatform)
			{
				ParentActor = MovingPlatform;
				return true;
			}
		}
	}
	else
	{
		if (SSTarget && SSTarget->GetSelfEntity() && SSTarget->GetSelfEntity()->ParentID())
		{
			return true;
		}
	}
	// ʧ�������
	ParentActor = nullptr;
	return false;
}

#pragma optimize("", on)
