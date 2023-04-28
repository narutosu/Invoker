#include "DamageAttackBaseCal.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"

UDamageAttackBaseCal::UDamageAttackBaseCal()
{
	AttackDef.AttributeToCapture = UIVAttributeSet::GetAttackAttribute();
	AttackDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	AttackDef.bSnapshot = true;

	ArmorDef.AttributeToCapture = UIVAttributeSet::GetBornAgilityAttribute();
	ArmorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ArmorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(AttackDef);
	RelevantAttributesToCapture.Add(ArmorDef);
}

float UDamageAttackBaseCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Attack = 0.f;
	GetCapturedAttributeMagnitude(AttackDef, Spec, EvaluationParameters, Attack);
	Attack = FMath::Max<float>(Attack, 0.0f);

	float Armor = 0.f;
	GetCapturedAttributeMagnitude(ArmorDef, Spec, EvaluationParameters, Armor);
	Armor = FMath::Max<float>(Armor, 0.0f);

	float FinalDamage =Attack*100/(100+6*Armor);
	return FinalDamage;
	
}