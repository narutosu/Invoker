#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxHPModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UMaxHPModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMaxHPModCal();
	FGameplayEffectAttributeCaptureDefinition BornMaxHPDef;
	FGameplayEffectAttributeCaptureDefinition StrengthDef;
	FGameplayEffectAttributeCaptureDefinition OtherMaxHPDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
