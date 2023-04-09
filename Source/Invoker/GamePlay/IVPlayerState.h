// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "IVPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API AIVPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AIVPlayerState();
	//GAS
public:
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	class UIVAttributeSet* GetAttributeSet() const;

protected:
	UPROPERTY()
	class UIVAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	class UIVAttributeSet* AttributeSet;
};
