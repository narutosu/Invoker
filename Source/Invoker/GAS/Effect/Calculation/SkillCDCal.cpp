#include "SkillCDCal.h"

#include "Invoker/GamePlay/IVCharacterBase.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"

USkillCDCal::USkillCDCal()
{
}

float USkillCDCal::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UIVGameplayAbility* Ability = Cast<UIVGameplayAbility>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (!Ability)
	{
		return 0.0f;
	}

	return Ability->CooldownDuration.GetValueAtLevel(Ability->GetAbilityLevel());
}