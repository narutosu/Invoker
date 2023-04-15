#include "AgilityModCal.h"

#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UAgilityModCal::UAgilityModCal()
{
	LevelDef.AttributeToCapture = UIVAttributeSet::GetLevelAttribute();
	LevelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	LevelDef.bSnapshot = false;

	BornAgilityDef.AttributeToCapture = UIVAttributeSet::GetBornAgilityAttribute();
	BornAgilityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornAgilityDef.bSnapshot = false;
	
	GrowAgilityDef.AttributeToCapture = UIVAttributeSet::GetGrowAgilityAttribute();
	GrowAgilityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	GrowAgilityDef.bSnapshot = false;
	
	OtherAgilityDef.AttributeToCapture = UIVAttributeSet::GetOtherAgilityAttribute();
	OtherAgilityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherAgilityDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(LevelDef);
	RelevantAttributesToCapture.Add(BornAgilityDef);
	RelevantAttributesToCapture.Add(GrowAgilityDef);
	RelevantAttributesToCapture.Add(OtherAgilityDef);
}

float UAgilityModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Level = 0.f;
	GetCapturedAttributeMagnitude(LevelDef, Spec, EvaluationParameters, Level);
	Level = FMath::Max<float>(Level, 1.0f);

	float BornAgility = 0.f;
	GetCapturedAttributeMagnitude(BornAgilityDef, Spec, EvaluationParameters, BornAgility);
	BornAgility = FMath::Max<float>(BornAgility, 0.0f);

	float GrowAgility = 0.f;
	GetCapturedAttributeMagnitude(GrowAgilityDef, Spec, EvaluationParameters, GrowAgility);
	GrowAgility = FMath::Max<float>(GrowAgility, 0.0f);

	float OtherAgility = 0.f;
	GetCapturedAttributeMagnitude(OtherAgilityDef, Spec, EvaluationParameters, OtherAgility);
	OtherAgility = FMath::Max<float>(OtherAgility, 0.0f);

	float FinalAgility = BornAgility+OtherAgility+(GrowAgility*(Level-1.0f));
	return FinalAgility;
	
}
