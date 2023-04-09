// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IVCharacterBase.h"
#include "IVCharacterMonster.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API AIVCharacterMonster : public AIVCharacterBase
{
	GENERATED_BODY()
public:
	AIVCharacterMonster(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void BeginPlay() override;
	
	//GAS
protected:
	UPROPERTY()
	class UIVAbilitySystemComponent* HardRefAbilitySystemComponent;
	UPROPERTY()
	class UIVAttributeSet* HardRefAttributeSetBase;
};
