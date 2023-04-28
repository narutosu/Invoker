// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "IVGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UIVGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UIVGameplayAbility();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	float CD;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	bool isPassive;
};
