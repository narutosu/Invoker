// Fill out your copyright notice in the Description page of Project Settings.


#include "IVPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//input
void AIVPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 先添加IMC还是绑定IA不重要，因为IMC代表的只是一个从按键到Action的关系，下面的Action是怎么到一个回调
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 100);
	}
	
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_AttackSelect,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputAttackSelect);
		EnhancedInputComponent->BindAction(IA_CameraMove,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputCameraMove);
		EnhancedInputComponent->BindAction(IA_Cancel,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputCancel);
		EnhancedInputComponent->BindAction(IA_HeroSelect,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputHeroSelect);
		EnhancedInputComponent->BindAction(IA_LeftClick,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputLeftClick);
		EnhancedInputComponent->BindAction(IA_Move,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputMove);
		EnhancedInputComponent->BindAction(IA_Skill,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputSkill);
		EnhancedInputComponent->BindAction(IA_Stop,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputStop);
	}
}

void AIVPlayerController::OnInputAttackSelect(const FInputActionValue& value)
{
}
void AIVPlayerController::OnInputCameraMove(const FInputActionValue& value)
{
}
void AIVPlayerController::OnInputCancel(const FInputActionValue& value)
{
}
void AIVPlayerController::OnInputHeroSelect(const FInputActionValue& value)
{
}
void AIVPlayerController::OnInputLeftClick(const FInputActionValue& value)
{
}

void AIVPlayerController::OnInputMove(const FInputActionValue& value)
{
	
}

void AIVPlayerController::OnInputSkill(const FInputActionValue& value)
{
}
void AIVPlayerController::OnInputStop(const FInputActionValue& value)
{
}