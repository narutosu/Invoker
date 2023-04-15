#include "ArmorModCal.h"

#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UArmorModCal::UArmorModCal()
{
	BornArmorDef.AttributeToCapture = UIVAttributeSet::GetBornArmorAttribute();
	BornArmorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	BornArmorDef.bSnapshot = false;
	
	AgilityDef.AttributeToCapture = UIVAttributeSet::GetAgilityAttribute();
	AgilityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	AgilityDef.bSnapshot = false;
	
	OtherArmorDef.AttributeToCapture = UIVAttributeSet::GetOtherArmorAttribute();
	OtherArmorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	OtherArmorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(BornArmorDef);
	RelevantAttributesToCapture.Add(AgilityDef);
	RelevantAttributesToCapture.Add(OtherArmorDef);
}

float UArmorModCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float BornArmor = 0.f;
	GetCapturedAttributeMagnitude(BornArmorDef, Spec, EvaluationParameters, BornArmor);
	BornArmor = FMath::Max<float>(BornArmor, 0.0f);

	float Agility = 0.f;
	GetCapturedAttributeMagnitude(AgilityDef, Spec, EvaluationParameters, Agility);
	Agility = FMath::Max<float>(Agility, 0.0f);

	float OtherArmor = 0.f;
	GetCapturedAttributeMagnitude(OtherArmorDef, Spec, EvaluationParameters, OtherArmor);
	OtherArmor = FMath::Max<float>(OtherArmor, 0.0f);

	float FinalArmor = BornArmor+OtherArmor+(Agility/6.f);
	return FinalArmor;
	
}
