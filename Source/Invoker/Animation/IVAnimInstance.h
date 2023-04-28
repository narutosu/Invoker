// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Invoker/GamePlay/IVCharacterBase.h"
#include "IVAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UIVAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UIVAnimInstance(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(BlueprintReadOnly,Category="Native")
	AIVCharacterBase* character = nullptr;
	
	UPROPERTY(BlueprintReadOnly,Category="Native")
	float Speed = 0.f;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	bool IsInAir = false;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	float Pitch = 0.f;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	float Roll = 0.f;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	float Yaw = 0.f;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	FRotator RotationLastTick;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	float YawDelta = 0.f;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	float LastFrameYaw = 0.f;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	bool IsAccelerating = false;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	bool isAttacking = false;
	UPROPERTY(BlueprintReadOnly,Category="Native")
	bool FullBody = false;
	
};
