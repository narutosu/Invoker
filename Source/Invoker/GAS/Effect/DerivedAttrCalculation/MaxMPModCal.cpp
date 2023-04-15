#include "MaxMpModCal.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UMaxMPModCal::UMaxMPModCal()
{
	BornMaxMPDef.AttributeToCapture = UIVAttributeSet::GetBornMaxMPAttribute();
	BornMaxMPDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornMaxMPDef.bSnapshot = false;
	
	IntelligenceDef.AttributeToCapture = UIVAttributeSet::GetStrengthAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	IntelligenceDef.bSnapshot = false;
	
	OtherMaxMPDef.AttributeToCapture = UIVAttributeSet::GetOtherMaxMPAttribute();
	OtherMaxMPDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherMaxMPDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(BornMaxMPDef);
	RelevantAttributesToCapture.Add(IntelligenceDef);
	RelevantAttributesToCapture.Add(OtherMaxMPDef);
}

float UMaxMPModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float BornMaxMp = 0.f;
	GetCapturedAttributeMagnitude(BornMaxMPDef, Spec, EvaluationParameters, BornMaxMp);
	BornMaxMp = FMath::Max<float>(BornMaxMp, 0.0f);

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.0f);

	float OtherMaxMp = 0.f;
	GetCapturedAttributeMagnitude(OtherMaxMPDef, Spec, EvaluationParameters, OtherMaxMp);
	OtherMaxMp = FMath::Max<float>(OtherMaxMp, 0.0f);

	float FinalMaxMp = BornMaxMp+OtherMaxMp+(Intelligence*14);
	return FinalMaxMp;
	
}
