#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "AgilityModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UAgilityModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UAgilityModCal();
	FGameplayEffectAttributeCaptureDefinition LevelDef;
	FGameplayEffectAttributeCaptureDefinition BornAgilityDef;
	FGameplayEffectAttributeCaptureDefinition GrowAgilityDef;
	FGameplayEffectAttributeCaptureDefinition OtherAgilityDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
