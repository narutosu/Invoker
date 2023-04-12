// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "IVCharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "IVPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSeletedCharacterChanged, AIVCharacterBase*, Character);
/**
 * 
 */
UCLASS()
class INVOKER_API AIVPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AIVPlayerController();
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	
	//Input
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UNiagaraSystem* FXCursor;
	virtual void SetupInputComponent() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> IA_AttackSelect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> IA_CameraMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> IA_Cancel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> IA_HeroSelect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> IA_LeftClick;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> IA_Move;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> IA_Skill;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="EnhancedInput|Action", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> IA_Stop;

	void OnInputAttackSelect(const FInputActionValue& value);
	void OnInputCameraMove(const FInputActionValue& value);
	void OnInputCancel(const FInputActionValue& value);
	void OnInputHeroSelect(const FInputActionValue& value);
	void OnInputLeftClick(const FInputActionValue& value);
	void OnInputMove();
	void OnInputSkill(const FInputActionValue& value);
	void OnInputStop(const FInputActionValue& value);

	//UI
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> UIMainWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UUserWidget* UIMainWidget;
	
	void CreateHUD();
private:
	AIVCharacterBase* SelectedCharacter;
public:
	UPROPERTY(BlueprintAssignable, Category = "IV")
	FOnSeletedCharacterChanged OnSelectedCharacterChanged;
	
	void SetSelectedCharacter(AIVCharacterBase* targe);
	AIVCharacterBase* GetSelectedCharacter();
};
