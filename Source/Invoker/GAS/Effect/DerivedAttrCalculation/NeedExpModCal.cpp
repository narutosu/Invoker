#include "NeedExpModCal.h"

#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UNeedExpModCal::UNeedExpModCal()
{
	LevelDef.AttributeToCapture = UIVAttributeSet::GetLevelAttribute();
	LevelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	LevelDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(LevelDef);
}

float UNeedExpModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Level = 0.f;
	GetCapturedAttributeMagnitude(LevelDef, Spec, EvaluationParameters, Level);
	Level = FMath::Max<float>(Level, 1.0f);

	float FinalExp = Level*300;
	return FinalExp;
	
}
