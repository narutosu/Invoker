#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "HpRegenNumModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UHpRegenNumModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UHpRegenNumModCal();
	FGameplayEffectAttributeCaptureDefinition BornHpRegenNumDef;
	FGameplayEffectAttributeCaptureDefinition OtherHpRegenNumDef;
	FGameplayEffectAttributeCaptureDefinition HpRegenRateDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
