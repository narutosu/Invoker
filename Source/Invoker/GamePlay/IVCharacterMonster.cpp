// Fill out your copyright notice in the Description page of Project Settings.


#include "IVCharacterMonster.h"
#include "Invoker/GAS/IVAbilitySystemComponent.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"


AIVCharacterMonster::AIVCharacterMonster(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	HardRefAbilitySystemComponent = CreateDefaultSubobject<UIVAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent = HardRefAbilitySystemComponent;

	HardRefAttributeSetBase = CreateDefaultSubobject<UIVAttributeSet>(TEXT("AttributeSetBase"));
	AttributeSetBase = HardRefAttributeSetBase;
	
}

void AIVCharacterMonster::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	InitializeAttributes();
	AddStartupEffects();
}
