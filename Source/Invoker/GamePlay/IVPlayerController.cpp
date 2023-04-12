// Fill out your copyright notice in the Description page of Project Settings.


#include "IVPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/UserWidget.h"

AIVPlayerController::AIVPlayerController()
:SelectedCharacter(nullptr)
{
	
}

void AIVPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	CreateHUD();
}

void AIVPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

//input
void AIVPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_AttackSelect,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputAttackSelect);
		EnhancedInputComponent->BindAction(IA_CameraMove,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputCameraMove);
		EnhancedInputComponent->BindAction(IA_Cancel,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputCancel);
		EnhancedInputComponent->BindAction(IA_HeroSelect,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputHeroSelect);
		EnhancedInputComponent->BindAction(IA_LeftClick,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputLeftClick);
		EnhancedInputComponent->BindAction(IA_Move,ETriggerEvent::Started,this,&AIVPlayerController::OnInputMove);
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

void AIVPlayerController::OnInputMove()
{
	StopMovement();
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Hit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void AIVPlayerController::OnInputSkill(const FInputActionValue& value)
{
}

void AIVPlayerController::OnInputStop(const FInputActionValue& value)
{
}

void AIVPlayerController::CreateHUD()
{
	// Only create once
	if (UIMainWidget)
	{
		return;
	}

	if (!UIMainWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing UIHUDWidgetClass. Please fill in on the Blueprint of the PlayerController."), *FString(__FUNCTION__));
		return;
	}

	// Only create a HUD for local player
	if (!IsLocalPlayerController())
	{
		return;
	}

	UIMainWidget = CreateWidget<UUserWidget>(this, UIMainWidgetClass);
	UIMainWidget->AddToViewport();
}

void AIVPlayerController::SetSelectedCharacter(AIVCharacterBase* targe)
{
	if(SelectedCharacter==targe)
		return;;
	SelectedCharacter = targe;
	OnSelectedCharacterChanged.Broadcast(targe);
}

AIVCharacterBase* AIVPlayerController::GetSelectedCharacter()
{
	return  SelectedCharacter;
}