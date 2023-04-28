// Fill out your copyright notice in the Description page of Project Settings.


#include "IVCharacterBase.h"
#include "Invoker/GAS/IVAbilitySystemComponent.h"
#include "Invoker/GAS/Attribute/IVAttributeSet.h"
#include "Invoker/GAS/Ability/IVGameplayAbility.h"


// Sets default values
AIVCharacterBase::AIVCharacterBase(const class FObjectInitializer& ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIVCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	SkillNeedNewDeltaYaw.AddDynamic(this,&AIVCharacterBase::OnSkillNeedNewDeltaYaw);
}

void AIVCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	for(auto item:SkillItemArr)
	{
		UIVAssetManager::GetAsset(item,true);
		item.LoadSynchronous();
	}
}

void AIVCharacterBase::UnPossessed()
{
	Super::UnPossessed();
	
}

// Called every frame
void AIVCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateOrientid(DeltaTime);
}

// Called to bind functionality to input
void AIVCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AIVCharacterBase::UpdateOrientid(float DeltaTime)
{
	float factor = SkillNeedYawDelta>=0.f?1:-1;
	if(factor*SkillNeedYawDelta>=1.f)//abs
	{
		float NeedYaw = factor*180.f*DeltaTime/YawTime;
		if(factor*NeedYaw>factor*SkillNeedYawDelta)
		{
			NeedYaw = SkillNeedYawDelta;
		}
		AddActorWorldRotation(FRotator(0,NeedYaw,0));
		LastFrameYaw = NeedYaw;
		SkillNeedYawDelta -=NeedYaw;
		if(isWaitSkill&&factor*SkillNeedYawDelta<=10.f)//小于10度可释放朝向技能
		{
			isWaitSkill = false;
			CanSkillDelegate.Broadcast();
		}
	}
	else if(isWaitSkill)
	{
		isWaitSkill = false;
		CanSkillDelegate.Broadcast();
	}
}

void AIVCharacterBase::OnSkillNeedNewDeltaYaw(float DeltaYaw,bool isWait)
{
	SkillNeedYawDelta = DeltaYaw;
	isWaitSkill = isWait;
}

//GAS
UAbilitySystemComponent* AIVCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void AIVCharacterBase::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!DefaultAttributes||!DefaultDerivedAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
	
	FGameplayEffectSpecHandle NewHandle2 = AbilitySystemComponent->MakeOutgoingSpec(DefaultDerivedAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle2.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle2.Data.Get(), AbilitySystemComponent.Get());
	}
}

void AIVCharacterBase::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bStartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void AIVCharacterBase::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	//if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bCharacterAbilitiesGiven)
	//{
	//	return;
	//}
	AbilitiesHandles.Empty();
	for (TSoftObjectPtr<UIVSkillItem>& StartupAbility : SkillItemArr)
	{
		auto item = StartupAbility.LoadSynchronous();
		auto handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(item->GrantedAbility, 1, INDEX_NONE, this));
		AbilitiesHandles.Add(handle);
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = true;
}

void AIVCharacterBase::TryActivateAbilityByIndex(int32 index)
{
	if(AbilitiesHandles.Num()<=index)
	{
		checkf(false,TEXT("CharacterAbilities range out"));
		return;
	}
	FGameplayAbilitySpecHandle targetAbility = AbilitiesHandles[index];
	AbilitySystemComponent->TryActivateAbility(targetAbility);	
}

int32 AIVCharacterBase::GetCharacterLevel() const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetLevel());
	}
	return 0;
}

float AIVCharacterBase::GetStrength()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetStrength());
	}
	return 0;
}

float AIVCharacterBase::GetAgility()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetAgility());
	}
	return 0;
}
float AIVCharacterBase::GetIntelligence()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetIntelligence());
	}
	return 0;
}
float AIVCharacterBase::GetAttack()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetAttack());
	}
	return 0;
}
float AIVCharacterBase::GetArmor()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetArmor());
	}
	return 0;
}
float AIVCharacterBase::GetSpeed()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetSpeed());
	}
	return 0;
}
float AIVCharacterBase::GetMaxHP()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetMaxHP());
	}
	return 0;
}
float AIVCharacterBase::GetMaxMP()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetMaxMP());
	}
	return 0;
}
float AIVCharacterBase::GetCurHP()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetCurHP());
	}
	return 0;
}

float AIVCharacterBase::GetCurMP()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetCurMP());
	}
	return 0;
}

float AIVCharacterBase::GetHpRegenNum()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetHpRegenNum());
	}
	return 0;
}


float AIVCharacterBase::GetMpRegenNum()  const
{
	if (AttributeSetBase.IsValid())
	{
		return static_cast<int32>(AttributeSetBase->GetLevel());
	}
	return 0;
}