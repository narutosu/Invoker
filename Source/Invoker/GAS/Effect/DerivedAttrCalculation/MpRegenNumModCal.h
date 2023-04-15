#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MpRegenNumModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UMpRegenNumModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMpRegenNumModCal();
	FGameplayEffectAttributeCaptureDefinition BornMpRegenNumDef;
	FGameplayEffectAttributeCaptureDefinition OtherMpRegenNumDef;
	FGameplayEffectAttributeCaptureDefinition MpRegenRateDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
