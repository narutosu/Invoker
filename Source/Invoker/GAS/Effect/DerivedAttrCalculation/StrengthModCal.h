#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "StrengthModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UStrengthModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UStrengthModCal();
	FGameplayEffectAttributeCaptureDefinition LevelDef;
	FGameplayEffectAttributeCaptureDefinition BornStrengthDef;
	FGameplayEffectAttributeCaptureDefinition GrowStrengthDef;
	FGameplayEffectAttributeCaptureDefinition OtherStrengthDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
