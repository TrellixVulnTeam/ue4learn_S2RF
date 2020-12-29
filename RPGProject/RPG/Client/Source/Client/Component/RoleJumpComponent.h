#pragma once
#include "ClientActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/EngineTypes.h"
#include "RoleJumpComponent.generated.h"

/**
* ��Ծ״̬
*/
UENUM(BlueprintType)
enum class JUMP_STATE : uint8
{
	///����Ծ״̬
	NO_JUMP = 0,
	///��ʼһ����
	START_FIRST_JUMP,
	///������һ������������
	FIRST_JUMP_UPING,
	///��ʼ������
	START_SECOND_JUMP,
	///�����ڶ�������������
	SECOND_JUMP_UPING,
	///�����½���
	JUMP_FALLING,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CLIENT_API URoleJumpComponent : public UClientActorComponent
{
	GENERATED_BODY()

public:
	URoleJumpComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitComponent(UCharacterMovementComponent *InCharacterMovement);

	void Jump();
	void StopJumping();
	///������Ծ״̬
	void UpdateRoleJumpState(JUMP_STATE InJumpState);
	UFUNCTION(BluePrintPure, Category = "Player|JumpState")
		JUMP_STATE GetCurJumpState() { return CurJumpState; };
	void OnRoleJumpStateChanged(JUMP_STATE InJumpState);
	///������Ծʱ�ĳ�ʼ�ٶȣ�˲ʱ��ֱ���ٶȣ��ٶ�
	void SetJumpZVelocity(float InJumpHeight);
	///������������ֵ
	void SetGravityScale(float InGravityScale);
	///��Ծģ�ͷ����ı�ʱ
	void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0);
	///ͬ����Ծ״̬
	void OnRepJumpState(uint8 InJumpState, FVector InVelocity, FVector InPos);

private:
	///����Ƿ�����Ծ���������
	void CheckJumpState();
	///���Ǳ��ͻ��˵����ִ��ģ�����
	void SimulatedFalling( float DeltaTime );
	void SmoothAdjustPosition();

	ACharacter* GetOwnerCharacter();
	UCharacterMovementComponent* GetCharacterMovement() { return CharacterMovement; };

public:
	float GravityZ;
private:
	UCharacterMovementComponent *CharacterMovement;
	JUMP_STATE CurJumpState;
	FVector TargetVelocity;
	FVector TargetPos;
	FTimerHandle SmoothMoveTimer;
	bool IsSmoothAdjust;
};