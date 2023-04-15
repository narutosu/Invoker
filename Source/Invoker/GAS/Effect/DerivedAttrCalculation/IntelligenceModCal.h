#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "IntelligenceModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UIntelligenceModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UIntelligenceModCal();
	FGameplayEffectAttributeCaptureDefinition LevelDef;
	FGameplayEffectAttributeCaptureDefinition BornIntelligenceDef;
	FGameplayEffectAttributeCaptureDefinition GrowIntelligenceDef;
	FGameplayEffectAttributeCaptureDefinition OtherIntelligenceDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
