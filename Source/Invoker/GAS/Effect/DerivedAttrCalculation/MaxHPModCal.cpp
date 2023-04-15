#include "MaxHpModCal.h"

#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UMaxHPModCal::UMaxHPModCal()
{
	BornMaxHPDef.AttributeToCapture = UIVAttributeSet::GetBornMaxHPAttribute();
	BornMaxHPDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornMaxHPDef.bSnapshot = false;
	
	StrengthDef.AttributeToCapture = UIVAttributeSet::GetStrengthAttribute();
	StrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	StrengthDef.bSnapshot = false;
	
	OtherMaxHPDef.AttributeToCapture = UIVAttributeSet::GetOtherMaxHPAttribute();
	OtherMaxHPDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherMaxHPDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(BornMaxHPDef);
	RelevantAttributesToCapture.Add(StrengthDef);
	RelevantAttributesToCapture.Add(OtherMaxHPDef);
}

float UMaxHPModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float BornMaxHp = 0.f;
	GetCapturedAttributeMagnitude(BornMaxHPDef, Spec, EvaluationParameters, BornMaxHp);
	BornMaxHp = FMath::Max<float>(BornMaxHp, 0.0f);

	float Strength = 0.f;
	GetCapturedAttributeMagnitude(StrengthDef, Spec, EvaluationParameters, Strength);
	Strength = FMath::Max<float>(Strength, 0.0f);

	float OtherMaxHp = 0.f;
	GetCapturedAttributeMagnitude(OtherMaxHPDef, Spec, EvaluationParameters, OtherMaxHp);
	OtherMaxHp = FMath::Max<float>(OtherMaxHp, 0.0f);

	float FinalMaxHp = BornMaxHp+OtherMaxHp+(Strength*20);
	return FinalMaxHp;
	
}
