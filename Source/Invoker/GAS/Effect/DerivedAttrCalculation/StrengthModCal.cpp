#include "StrengthModCal.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UStrengthModCal::UStrengthModCal()
{
	LevelDef.AttributeToCapture = UIVAttributeSet::GetLevelAttribute();
	LevelDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	LevelDef.bSnapshot = false;

	BornStrengthDef.AttributeToCapture = UIVAttributeSet::GetBornStrengthAttribute();
	BornStrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornStrengthDef.bSnapshot = false;
	
	GrowStrengthDef.AttributeToCapture = UIVAttributeSet::GetGrowStrengthAttribute();
	GrowStrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	GrowStrengthDef.bSnapshot = false;
	
	OtherStrengthDef.AttributeToCapture = UIVAttributeSet::GetOtherStrengthAttribute();
	OtherStrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherStrengthDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(LevelDef);
	RelevantAttributesToCapture.Add(BornStrengthDef);
	RelevantAttributesToCapture.Add(GrowStrengthDef);
	RelevantAttributesToCapture.Add(OtherStrengthDef);
}

float UStrengthModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Level = 0.f;
	GetCapturedAttributeMagnitude(LevelDef, Spec, EvaluationParameters, Level);
	Level = FMath::Max<float>(Level, 1.0f);

	float BornStrength = 0.f;
	GetCapturedAttributeMagnitude(BornStrengthDef, Spec, EvaluationParameters, BornStrength);
	BornStrength = FMath::Max<float>(BornStrength, 0.0f);

	float GrowStrength = 0.f;
	GetCapturedAttributeMagnitude(GrowStrengthDef, Spec, EvaluationParameters, GrowStrength);
	GrowStrength = FMath::Max<float>(GrowStrength, 0.0f);

	float OtherStrength = 0.f;
	GetCapturedAttributeMagnitude(OtherStrengthDef, Spec, EvaluationParameters, OtherStrength);
	OtherStrength = FMath::Max<float>(OtherStrength, 0.0f);

	float FinalStrength = BornStrength+OtherStrength+(GrowStrength*(Level-1.0f));
	return FinalStrength;
	
}
