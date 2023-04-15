#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "AttackModCal.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UAttackModCal : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UAttackModCal();
	FGameplayEffectAttributeCaptureDefinition LevelDef;
	FGameplayEffectAttributeCaptureDefinition BornAttackDef;
	FGameplayEffectAttributeCaptureDefinition StrengthDef;
	FGameplayEffectAttributeCaptureDefinition AgilityDef;
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	FGameplayEffectAttributeCaptureDefinition OtherAttackDef;
	bool IsMainAttrDefInit;
	void MainAttrDefInit(const FGameplayEffectSpec& Spec);
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
