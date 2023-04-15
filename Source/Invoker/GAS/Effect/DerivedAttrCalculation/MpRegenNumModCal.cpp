#include "MpRegenNumModCal.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UMpRegenNumModCal::UMpRegenNumModCal()
{
	BornMpRegenNumDef.AttributeToCapture = UIVAttributeSet::GetBornMpRegenNumAttribute();
	BornMpRegenNumDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornMpRegenNumDef.bSnapshot = false;
	
	OtherMpRegenNumDef.AttributeToCapture = UIVAttributeSet::GetOtherMpRegenNumAttribute();
	OtherMpRegenNumDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherMpRegenNumDef.bSnapshot = false;
	
	MpRegenRateDef.AttributeToCapture = UIVAttributeSet::GetMpRegenRateAttribute();
	MpRegenRateDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	MpRegenRateDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(BornMpRegenNumDef);
	RelevantAttributesToCapture.Add(OtherMpRegenNumDef);
	RelevantAttributesToCapture.Add(MpRegenRateDef);
}

float UMpRegenNumModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float BornMpRegenNum = 0.f;
	GetCapturedAttributeMagnitude(BornMpRegenNumDef, Spec, EvaluationParameters, BornMpRegenNum);
	BornMpRegenNum = FMath::Max<float>(BornMpRegenNum, 0.0f);

	float OtherMpRegenNum = 0.f;
	GetCapturedAttributeMagnitude(OtherMpRegenNumDef, Spec, EvaluationParameters, OtherMpRegenNum);
	OtherMpRegenNum = FMath::Max<float>(OtherMpRegenNum, 0.0f);

	float MpRegenRate = 0.f;
	GetCapturedAttributeMagnitude(MpRegenRateDef, Spec, EvaluationParameters, MpRegenRate);
	MpRegenRate = FMath::Max<float>(MpRegenRate, 0.0f);

	float FinalMaxMp =(BornMpRegenNum+OtherMpRegenNum)*(1+MpRegenRate);
	return FinalMaxMp;
	
}
