// Fill out your copyright notice in the Description page of Project Settings.


#include "IVAttributeSet.h"
#include "GameplayEffectExtension.h"

UIVAttributeSet::UIVAttributeSet()
{
}

void UIVAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UIVAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetCurHPAttribute())
	{
		SetCurHP(FMath::Clamp(GetCurHP(), 0.0f, GetMaxHP()));
	}
	else if (Data.EvaluatedData.Attribute == GetCurMPAttribute())
	{
		// Handle mana changes.
		SetCurMP(FMath::Clamp(GetCurMP(), 0.0f, GetMaxMP()));
	} // Mana
}

void UIVAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}