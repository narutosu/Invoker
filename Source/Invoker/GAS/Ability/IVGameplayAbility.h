// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "IVGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UIVGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UIVGameplayAbility();

	//cd
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Cooldown)
	FScalableFloat CooldownDuration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Cooldown)
	FGameplayTagContainer CooldownTags;
	UPROPERTY()
	FGameplayTagContainer TempCooldownTags;

	//cost
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Cost)
	FScalableFloat Cost;

	//当技能被赋予时，是否马上生效
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = trait)
	bool ActivateAbilityOnGranted = false;

	virtual const FGameplayTagContainer* GetCooldownTags() const override;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
