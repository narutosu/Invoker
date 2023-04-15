#include "SpeedModCal.h"

#include "Invoker/GAS/Attribute/IVAttributeSet.h"

USpeedModCal::USpeedModCal()
{
	BornSpeedDef.AttributeToCapture = UIVAttributeSet::GetBornSpeedAttribute();
	BornSpeedDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornSpeedDef.bSnapshot = false;
	
	OtherSpeedDef.AttributeToCapture = UIVAttributeSet::GetOtherSpeedAttribute();
	OtherSpeedDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherSpeedDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(BornSpeedDef);
	RelevantAttributesToCapture.Add(OtherSpeedDef);
}

float USpeedModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float BornSpeed = 0.f;
	GetCapturedAttributeMagnitude(BornSpeedDef, Spec, EvaluationParameters, BornSpeed);
	BornSpeed = FMath::Max<float>(BornSpeed, 0.0f);

	float OtherSpeed = 0.f;
	GetCapturedAttributeMagnitude(OtherSpeedDef, Spec, EvaluationParameters, OtherSpeed);
	OtherSpeed = FMath::Max<float>(OtherSpeed, 0.0f);

	float FinalSpeed = BornSpeed+OtherSpeed;
	return FinalSpeed;
	
}
