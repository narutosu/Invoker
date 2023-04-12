// Fill out your copyright notice in the Description page of Project Settings.


#include "IVPlayerState.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"
#include "Invoker/GAS/IVAbilitySystemComponent.h"
AIVPlayerState::AIVPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UIVAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UIVAttributeSet>(TEXT("AttributeSetBase"));
}

UAbilitySystemComponent * AIVPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UIVAttributeSet * AIVPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

int32 AIVPlayerState::GetCharacterLevel() const
{
	if (AttributeSet)
	{
		return static_cast<int32>(AttributeSet->GetLevel());
	}
	return 0;
}