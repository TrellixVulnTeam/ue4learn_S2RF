// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleModuleCollisionEX.h"
// UE4
#include "Particles/ParticleModule.h"
#include "Particles/ParticleLODLevel.h"
#include "ParticleEmitterInstances.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleModuleRequired.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UBeginParticleModuleCollisionEX::UBeginParticleModuleCollisionEX(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bSpawnModule = true;
	bUpdateModule = true;
}

void UBeginParticleModuleCollisionEX::Update(FParticleEmitterInstance* Owner, int32 Offset, float DeltaTime)
{
	// ����ط�����Ϊ�գ�ֻ��PVS������⣬�Ӹ��ж�
	if (Owner == nullptr)
	{
		return;
	}

	UWorld* World = Owner->Component->GetWorld();
	if (World && World->IsGameWorld() && World->bDropDetail)
	{
		bCurrentDropDetail = World->bDropDetail;
		World->bDropDetail = 0;
		// ���ú���������ײ��ʱ��Ϊ1�룬��ÿһ֡��ʱ�����1��ʱ������������ײ
		FString cmd = TEXT("fx.ParticleCollisionIgnoreInvisibleTime = 1");
		UKismetSystemLibrary::ExecuteConsoleCommand(World, cmd);
	}
}

UEndParticleModuleCollisionEX::UEndParticleModuleCollisionEX(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bSpawnModule = true;
	bUpdateModule = true;
}

void UEndParticleModuleCollisionEX::Update(FParticleEmitterInstance* Owner, int32 Offset, float DeltaTime)
{
	// ����ط�����Ϊ�գ�ֻ��PVS������⣬�Ӹ��ж�
	if (Owner == nullptr)
	{
		return;
	}

	UWorld* World = Owner->Component->GetWorld();

	if (World && World->IsGameWorld())
	{
		UParticleEmitter* CurEmitters;
		UParticleLODLevel* CurLOD;
		for (int i = 0; i < Owner->Component->Template->Emitters.Num(); i++)
		{
			CurEmitters = Owner->Component->Template->Emitters[i];

			for (int j = 0; j < CurEmitters->LODLevels.Num(); j++)
			{
				CurLOD = CurEmitters->LODLevels[j];

				for (int k = 0; k < CurLOD->Modules.Num(); k++)
				{
					if (CurLOD->Modules[k]->IsA(UBeginParticleModuleCollisionEX::StaticClass()))
					{
						if (!World->bDropDetail)
						{
							World->bDropDetail = Cast<UBeginParticleModuleCollisionEX>(CurLOD->Modules[k])->bCurrentDropDetail;
							// ���ú���������ײ��ʱ��Ϊ0.1�룬��ÿһ֡��ʱ�����0.1��ʱ������������ײ
							FString cmd = TEXT("fx.ParticleCollisionIgnoreInvisibleTime = 0.1");
							UKismetSystemLibrary::ExecuteConsoleCommand(World, cmd);
							return;
						}
					}
				}
			}
		}
	}
	// ��������׷�ٵ���
	/*BEGIN_UPDATE_LOOP;
	{
		const FTransform& OwnerTM = Owner->Component->GetAsyncComponentToWorld();
		const FVector ParentScale = OwnerTM.GetScale3D();

		FVector			Location;
		FVector			OldLocation;

		Location = Particle.Location + Particle.Velocity * DeltaTime;

		UParticleLODLevel* LODLevel = Owner->SpriteTemplate->GetCurrentLODLevel(Owner);
		if (LODLevel->RequiredModule->bUseLocalSpace)
		{
			// Transform the location and old location into world space
			Location = OwnerTM.TransformPosition(Location);
			OldLocation = OwnerTM.TransformPosition(Particle.OldLocation);
		}
		else
		{
			OldLocation = Particle.OldLocation;
		}

		FVector	Direction = (Location - OldLocation).GetSafeNormal();
		FVector Size = Particle.Size * ParentScale;

		FVector End = Location + Direction * Size / 3.5f;

		DrawDebugLine(Owner->Component->GetWorld(), OldLocation, End, FColor::Red, false, 2.0f);

	}
	END_UPDATE_LOOP;*/
}
