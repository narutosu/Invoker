// Fill out your copyright notice in the Description page of Project Settings.


#include "IVCharacterRole.h"
#include "IVPlayerState.h"
#include "Invoker/GAS/IVAbilitySystemComponent.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"

// Server only
void AIVCharacterRole::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	AIVPlayerState* PS = GetPlayerState<AIVPlayerState>();
	if (PS)
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UIVAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		// Set the AttributeSetBase for convenience attribute functions
		AttributeSetBase = PS->GetAttributeSet();
	}
}