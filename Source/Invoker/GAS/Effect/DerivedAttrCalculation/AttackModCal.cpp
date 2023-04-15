#include "AttackModCal.h"

#include "Invoker/GamePlay/IVCharacterRole.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UAttackModCal::UAttackModCal()
{
	LevelDef.AttributeToCapture = UIVAttributeSet::GetLevelAttribute();
	LevelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	LevelDef.bSnapshot = false;

	BornAttackDef.AttributeToCapture = UIVAttributeSet::GetBornAttackAttribute();
	BornAttackDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornAttackDef.bSnapshot = false;

	StrengthDef.AttributeToCapture = UIVAttributeSet::GetStrengthAttribute();
	StrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	StrengthDef.bSnapshot = false;

	AgilityDef.AttributeToCapture = UIVAttributeSet::GetAgilityAttribute();
	AgilityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	AgilityDef.bSnapshot = false;
	
	IntelligenceDef.AttributeToCapture = UIVAttributeSet::GetStrengthAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	IntelligenceDef.bSnapshot = false;
	
	OtherAttackDef.AttributeToCapture = UIVAttributeSet::GetOtherAttackAttribute();
	OtherAttackDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherAttackDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(LevelDef);
	RelevantAttributesToCapture.Add(BornAttackDef);
	RelevantAttributesToCapture.Add(StrengthDef);
	RelevantAttributesToCapture.Add(AgilityDef);
	RelevantAttributesToCapture.Add(IntelligenceDef);
	RelevantAttributesToCapture.Add(OtherAttackDef);
}

float UAttackModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Level = 0.f;
	GetCapturedAttributeMagnitude(LevelDef, Spec, EvaluationParameters, Level);
	Level = FMath::Max<float>(Level, 1.0f);

	float BornAttack = 0.f;
	GetCapturedAttributeMagnitude(BornAttackDef, Spec, EvaluationParameters, BornAttack);
	BornAttack = FMath::Max<float>(BornAttack, 0.0f);

	float MainAttr = 0.f;
	UAbilitySystemComponent* ASC = Cast<UAbilitySystemComponent>(Spec.GetContext().GetInstigatorAbilitySystemComponent());
	if(ASC)
	{
		if(ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("MainAttr.Strength"))))
		{
			GetCapturedAttributeMagnitude(StrengthDef, Spec, EvaluationParameters, MainAttr);
		}
		else if(ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("MainAttr.Agility"))))
		{
			GetCapturedAttributeMagnitude(AgilityDef, Spec, EvaluationParameters, MainAttr);
		}
		else if(ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("MainAttr.Intelligence"))))
		{
			GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, MainAttr);
		}
		else
		{
			checkf(false,TEXT("not has MainAttr"))
		}
	}
	MainAttr = FMath::Max<float>(MainAttr, 0.0f);

	float OtherAttack = 0.f;
	GetCapturedAttributeMagnitude(OtherAttackDef, Spec, EvaluationParameters, OtherAttack);
	OtherAttack = FMath::Max<float>(OtherAttack, 0.0f);

	float FinalAttack = BornAttack+OtherAttack+MainAttr;
	return FinalAttack;
	
}
