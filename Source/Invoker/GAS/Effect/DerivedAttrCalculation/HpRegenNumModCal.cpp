#include "HpRegenNumModCal.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UHpRegenNumModCal::UHpRegenNumModCal()
{
	BornHpRegenNumDef.AttributeToCapture = UIVAttributeSet::GetBornHpRegenNumAttribute();
	BornHpRegenNumDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornHpRegenNumDef.bSnapshot = false;
	
	OtherHpRegenNumDef.AttributeToCapture = UIVAttributeSet::GetOtherHpRegenNumAttribute();
	OtherHpRegenNumDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherHpRegenNumDef.bSnapshot = false;
	
	HpRegenRateDef.AttributeToCapture = UIVAttributeSet::GetHpRegenRateAttribute();
	HpRegenRateDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	HpRegenRateDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(BornHpRegenNumDef);
	RelevantAttributesToCapture.Add(OtherHpRegenNumDef);
	RelevantAttributesToCapture.Add(HpRegenRateDef);
}

float UHpRegenNumModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float BornHpRegenNum = 0.f;
	GetCapturedAttributeMagnitude(BornHpRegenNumDef, Spec, EvaluationParameters, BornHpRegenNum);
	BornHpRegenNum = FMath::Max<float>(BornHpRegenNum, 0.0f);

	float OtherHpRegenNum = 0.f;
	GetCapturedAttributeMagnitude(OtherHpRegenNumDef, Spec, EvaluationParameters, OtherHpRegenNum);
	OtherHpRegenNum = FMath::Max<float>(OtherHpRegenNum, 0.0f);

	float HpRegenRate = 0.f;
	GetCapturedAttributeMagnitude(HpRegenRateDef, Spec, EvaluationParameters, HpRegenRate);
	HpRegenRate = FMath::Max<float>(HpRegenRate, 0.0f);

	float FinalMaxHp =(BornHpRegenNum+OtherHpRegenNum)*(1+HpRegenRate);
	return FinalMaxHp;
	
}
