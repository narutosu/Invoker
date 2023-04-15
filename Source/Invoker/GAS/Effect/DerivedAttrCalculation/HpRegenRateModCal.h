#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "HpRegenRateModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UHpRegenRateModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UHpRegenRateModCal();
	FGameplayEffectAttributeCaptureDefinition StrengthDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
