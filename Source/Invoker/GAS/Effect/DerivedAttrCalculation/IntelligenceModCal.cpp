#include "IntelligenceModCal.h"

#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UIntelligenceModCal::UIntelligenceModCal()
{
	LevelDef.AttributeToCapture = UIVAttributeSet::GetLevelAttribute();
	LevelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	LevelDef.bSnapshot = false;

	BornIntelligenceDef.AttributeToCapture = UIVAttributeSet::GetBornIntelligenceAttribute();
	BornIntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornIntelligenceDef.bSnapshot = false;
	
	GrowIntelligenceDef.AttributeToCapture = UIVAttributeSet::GetGrowIntelligenceAttribute();
	GrowIntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	GrowIntelligenceDef.bSnapshot = false;
	
	OtherIntelligenceDef.AttributeToCapture = UIVAttributeSet::GetOtherIntelligenceAttribute();
	OtherIntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherIntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(LevelDef);
	RelevantAttributesToCapture.Add(BornIntelligenceDef);
	RelevantAttributesToCapture.Add(GrowIntelligenceDef);
	RelevantAttributesToCapture.Add(OtherIntelligenceDef);
}

float UIntelligenceModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Level = 0.f;
	GetCapturedAttributeMagnitude(LevelDef, Spec, EvaluationParameters, Level);
	Level = FMath::Max<float>(Level, 1.0f);

	float BornIntelligence = 0.f;
	GetCapturedAttributeMagnitude(BornIntelligenceDef, Spec, EvaluationParameters, BornIntelligence);
	BornIntelligence = FMath::Max<float>(BornIntelligence, 0.0f);

	float GrowIntelligence = 0.f;
	GetCapturedAttributeMagnitude(GrowIntelligenceDef, Spec, EvaluationParameters, GrowIntelligence);
	GrowIntelligence = FMath::Max<float>(GrowIntelligence, 0.0f);

	float OtherIntelligence = 0.f;
	GetCapturedAttributeMagnitude(OtherIntelligenceDef, Spec, EvaluationParameters, OtherIntelligence);
	OtherIntelligence = FMath::Max<float>(OtherIntelligence, 0.0f);

	float FinalIntelligence = BornIntelligence+OtherIntelligence+(GrowIntelligence*(Level-1.0f));
	return FinalIntelligence;
	
}
