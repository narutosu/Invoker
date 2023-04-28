// Fill out your copyright notice in the Description page of Project Settings.


#include "IVPlayerController.h"

#include "AbilitySystemComponent.h"
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
	SetSelectedCharacter(Cast<AIVCharacterBase>(InPawn));
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
		EnhancedInputComponent->BindAction(IA_Skill,ETriggerEvent::Started,this,&AIVPlayerController::OnInputSkill);
		EnhancedInputComponent->BindAction(IA_Stop,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputStop);
		EnhancedInputComponent->BindAction(IA_Comfirm,ETriggerEvent::Triggered,this,&AIVPlayerController::OnInputComfirm);
	}
}

void AIVPlayerController::OnInputAttackSelect(const FInputActionValue& value)
{
}
void AIVPlayerController::OnInputCameraMove(const FInputActionValue& value)
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

	InterruptAbility();
}

void AIVPlayerController::OnInputSkill(const FInputActionValue& value)
{
	SelectedCharacter->TryActivateAbilityByIndex(value.Get<FInputActionValue::Axis1D>());
}

void AIVPlayerController::OnInputStop(const FInputActionValue& value)
{
}

void AIVPlayerController::OnInputComfirm(const FInputActionValue& value)
{
	SelectedCharacter->GetAbilitySystemComponent()->LocalInputConfirm();
}

void AIVPlayerController::OnInputCancel(const FInputActionValue& value)
{
	SelectedCharacter->GetAbilitySystemComponent()->LocalInputCancel();
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

void AIVPlayerController::InterruptAbility()
{
	UAbilitySystemComponent* Component = Cast<AIVCharacterBase>(GetCharacter())->GetAbilitySystemComponent();
	//Component->CancelAllAbilities();
	FGameplayTagContainer AbilityTagsToCancel;
	AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Trait.CanBeInterrupt")));

	FGameplayTagContainer AbilityTagsToIgnore;
	//AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));
	Component->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore, nullptr);
}