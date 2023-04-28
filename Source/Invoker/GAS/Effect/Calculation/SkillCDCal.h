#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "SkillCDCal.generated.h"

UCLASS()
class INVOKER_API USkillCDCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	USkillCDCal();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
