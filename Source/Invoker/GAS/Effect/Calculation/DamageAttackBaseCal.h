#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "DamageAttackBaseCal.generated.h"

UCLASS()
class INVOKER_API UDamageAttackBaseCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UDamageAttackBaseCal();
	FGameplayEffectAttributeCaptureDefinition AttackDef;
	FGameplayEffectAttributeCaptureDefinition ArmorDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
