// Fill out your copyright notice in the Description page of Project Settings.


#include "IVAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Invoker/GamePlay/IVCharacterBase.h"

UIVAnimInstance::UIVAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UIVAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	character = Cast<AIVCharacterBase>(GetOwningActor());
}

void UIVAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(!character) return;

	UCharacterMovementComponent* movementCmp = character->GetCharacterMovement();
	IsInAir = movementCmp->IsFalling();
	Speed = character->GetVelocity().Length();
	FRotator AimRotation = character->GetBaseAimRotation();
	FRotator ActorRotation = character->GetActorRotation();
	FRotator DeltaRotation = AimRotation-ActorRotation;
	Roll = DeltaRotation.Roll;
	Pitch = DeltaRotation.Pitch;
	Yaw = DeltaRotation.Yaw;

	FRotator DeltaActorRotation = ActorRotation - RotationLastTick;
	RotationLastTick = ActorRotation;
	float YawRate = DeltaActorRotation.Yaw/DeltaSeconds;

	YawDelta = FMath::FInterpTo(YawDelta, YawRate/7.f, DeltaSeconds, 6);
	if(YawDelta>180.f) YawDelta-=180.f;
	if(YawDelta<-180.f) YawDelta+=180.f;
	float Acceleration = movementCmp->GetCurrentAcceleration().Length();
	IsAccelerating = Acceleration>0.f;
	LastFrameYaw = character->LastFrameYaw;
	FullBody =  GetCurveValue(TEXT("FullBody"))>0.f;
}