#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "ArmorModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UArmorModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UArmorModCal();
	FGameplayEffectAttributeCaptureDefinition BornArmorDef;
	FGameplayEffectAttributeCaptureDefinition AgilityDef;
	FGameplayEffectAttributeCaptureDefinition OtherArmorDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
