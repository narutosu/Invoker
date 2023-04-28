// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Invoker/GAS/Ability/IVGameplayAbility.h"
#include "Invoker/GAS/Asset/IVItem.h"
#include "Invoker/System/IVAssetManager.h"
#include "IVSkillItem.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UIVSkillItem : public UIVItem
{
	GENERATED_BODY()
public:
	UIVSkillItem()
	{
		ItemType = UIVAssetManager::SkillItem;
	}
	
	/** Ability to grant if this item is slotted */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TSubclassOf<UIVGameplayAbility> GrantedAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	float AbilityCD;//暂时无用

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	bool IsPassive;

	/** Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
