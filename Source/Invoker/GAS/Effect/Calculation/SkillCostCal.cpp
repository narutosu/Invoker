#include "SkillCostCal.h"

#include "Invoker/GamePlay/IVCharacterBase.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"

USkillCostCal::USkillCostCal()
{
}

float USkillCostCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UIVGameplayAbility* Ability = Cast<UIVGameplayAbility>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (!Ability)
	{
		return 0.0f;
	}

	return Ability->Cost.GetValueAtLevel(Ability->GetAbilityLevel());
}