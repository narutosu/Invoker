// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CampInterface.h"
#include "GameFramework/Character.h"
#include "Invoker/GAS/Asset/Ability/IVSkillItem.h"
#include "IVCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIVCharacterBase_DeltaYaw,float,DeltaYaw,bool,isWaitSkill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIVCharacterBase_DeltaYawCanSkill);

UCLASS()
class INVOKER_API AIVCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIVCharacterBase(const class FObjectInitializer& ObjectInitializer);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
public:
	//技能资源
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	TArray<TSoftObjectPtr<UIVSkillItem>> SkillItemArr;
	
	//技能释放 原地旋转
	UPROPERTY(BlueprintAssignable)
	FIVCharacterBase_DeltaYaw SkillNeedNewDeltaYaw;

	FIVCharacterBase_DeltaYawCanSkill CanSkillDelegate;
	float SkillNeedYawDelta = 0.f;
	//旋转180度需要的时间
	float YawTime = 0.4f;
	float LastFrameYaw = 0.f;//上一帧人物Yaw的值
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Native")
	bool isWaitSkill = false;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateOrientid(float DeltaTime);

	UFUNCTION()
	void OnSkillNeedNewDeltaYaw(float DeltaYaw,bool isWait);
	
	TSoftObjectPtr<class UAssetAbilityBase> AssetAbility;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultDerivedAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	//所属的阵营
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camp)
	FGameplayTag CampTag;
	
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASDocumentation|Abilities")
	TArray<FGameplayAbilitySpecHandle> AbilitiesHandles;
	//GAS
public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	TWeakObjectPtr<class UIVAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UIVAttributeSet> AttributeSetBase;
public:
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();
	virtual void AddCharacterAbilities();
	virtual void TryActivateAbilityByIndex(int32 index);
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetStrength() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetAgility() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetIntelligence() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetAttack() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetArmor() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxHP() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxMP() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetCurHP() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetCurMP() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHpRegenNum() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMpRegenNum() const;
};
