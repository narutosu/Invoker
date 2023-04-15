#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "SpeedModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API USpeedModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	USpeedModCal();
	FGameplayEffectAttributeCaptureDefinition BornSpeedDef;
	FGameplayEffectAttributeCaptureDefinition OtherSpeedDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
