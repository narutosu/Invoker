// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "IVAttributeSet.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class INVOKER_API UIVAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UIVAttributeSet();
	// AttributeSet Overrides
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, Level)
	
	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornStrength;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornStrength)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornAgility;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornAgility)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornIntelligence;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornIntelligence)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornAttack;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornAttack)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornArmor;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornArmor)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornSpeed;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornMaxHP;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornMaxHP)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornMaxMP;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornMaxMP)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornHpRegenNum;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornHpRegenNum)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData BornMpRegenNum;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, BornMpRegenNum)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData GrowStrength;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, GrowStrength)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData GrowAgility;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, GrowAgility)

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FGameplayAttributeData GrowIntelligence;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, GrowIntelligence)

	UPROPERTY(BlueprintReadOnly, Category = "state")
	FGameplayAttributeData CurHP;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, CurHP)

	UPROPERTY(BlueprintReadOnly, Category = "state")
	FGameplayAttributeData CurMP;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, CurMP)

	UPROPERTY(BlueprintReadOnly, Category = "state")
	FGameplayAttributeData CurExp;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, CurExp)

	//从装备或者物品之类的得到的属性
	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherStrength;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherStrength)

	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherAgility;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherAgility)

	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherIntelligence;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherIntelligence)

	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherAttack;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherAttack)

	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherArmor;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherArmor)

	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherSpeed;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherMaxHP;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherMaxHP)

	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherMaxMP;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherMaxMP)

	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherHpRegenNum;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherHpRegenNum)

	UPROPERTY(BlueprintReadOnly, Category = "FromOther")
	FGameplayAttributeData OtherMpRegenNum;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, OtherMpRegenNum)
	
	//推导属性 通过GE_HeroDerivedAttributes计算
	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, Agility)

	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, Attack)

	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, Armor)

	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, Speed)

	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, MaxHP)

	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, MaxMP)
	
	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData NeedExp;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, NeedExp)
	
	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData HpRegenRate;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, HpRegenRate)

	UPROPERTY(BlueprintReadOnly, Category = "Derived")
	FGameplayAttributeData MpRegenRate;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, MpRegenRate)
	
	UPROPERTY(BlueprintReadOnly, Category = "Meta")
	FGameplayAttributeData HpRegenNum;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, HpRegenNum)

	UPROPERTY(BlueprintReadOnly, Category = "Meta")
	FGameplayAttributeData MpRegenNum;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, MpRegenNum)
	
	//临时属性
	UPROPERTY(BlueprintReadOnly, Category = "Meta")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, Damage)
	
	UPROPERTY(BlueprintReadOnly, Category = "Meta")
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UIVAttributeSet, Healing)
};
