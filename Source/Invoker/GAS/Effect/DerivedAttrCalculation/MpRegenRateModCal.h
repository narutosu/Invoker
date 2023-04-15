#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MpRegenRateModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UMpRegenRateModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMpRegenRateModCal();
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
