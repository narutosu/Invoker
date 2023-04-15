#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxMPModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UMaxMPModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMaxMPModCal();
	FGameplayEffectAttributeCaptureDefinition BornMaxMPDef;
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	FGameplayEffectAttributeCaptureDefinition OtherMaxMPDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
