#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "NeedExpModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UNeedExpModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UNeedExpModCal();
	FGameplayEffectAttributeCaptureDefinition LevelDef;
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
