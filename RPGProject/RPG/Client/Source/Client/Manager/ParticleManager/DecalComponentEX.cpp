// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalComponentEX.h"


void UDecalComponentEX::SendRenderTransform_Concurrent()
{
	//If Decal isn't hidden update its transform.
	if (ShouldComponentAddToScene() && ShouldRender())
	{
		//����Ⱦǰ����������Transform��ÿ֡����
		SetComponentTransform();
		GetWorld()->Scene->UpdateDecalTransform(this);
	}

	UDecalComponent::Super::SendRenderTransform_Concurrent();
}

void UDecalComponentEX::CreateRenderState_Concurrent()
{
	UDecalComponent::Super::CreateRenderState_Concurrent();

	// Mimics UPrimitiveComponent's visibility logic, although without the UPrimitiveCompoent visibility flags
	if (ShouldComponentAddToScene() && ShouldRender())
	{
		//����Ⱦǰ����������Transform����ʼ������
		SetComponentTransform();
		GetWorld()->Scene->AddDecal(this);
	}
}

void UDecalComponentEX::SetComponentTransform()
{
	RealYaw = 0;
	ParentComponent = this;

	FTransform& Ret = const_cast<FTransform&>(GetComponentToWorld());
	FVector CurScale = FVector(Ret.GetScale3D().Z, Ret.GetScale3D().X, Ret.GetScale3D().Y);

	CalculateDecalRealYaw();
	//����up����������ʵ��Yawֵ
	if (GetUpVector().Z < 0)
	{
		RealYaw += 180;
	}
	//���������������ʵ��ת������scale X,Y,Z��λ��
	//X,Y�����ķ���������Z�����ĸ߶�
	//ԭZ,Y�����ķ���������X�����ĸ߶�
	Ret.SetRotation(FRotator(-90, RealYaw, 0).Quaternion());
	Ret.SetScale3D(CurScale);
}

void UDecalComponentEX::CalculateDecalRealYaw()
{
	//�ݹ��ۼ������ʵ��Yawֵ
	ParentComponent = ParentComponent->GetAttachParent();
	if (ParentComponent && IsValid(ParentComponent))
	{
		RealYaw += ParentComponent->GetRelativeTransform().GetRotation().Rotator().Yaw;
		CalculateDecalRealYaw();
	}
	else
	{
		RealYaw += GetRelativeTransform().GetRotation().Rotator().Yaw;
	}
}