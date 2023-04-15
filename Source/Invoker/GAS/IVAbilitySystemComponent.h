// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "IVAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UIVAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;
};
