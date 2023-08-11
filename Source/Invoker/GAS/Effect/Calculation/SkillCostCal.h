#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "SkillCostCal.generated.h"

UCLASS()
class INVOKER_API USkillCostCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	USkillCostCal();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
