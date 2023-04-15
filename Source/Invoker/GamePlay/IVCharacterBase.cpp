// Fill out your copyright notice in the Description page of Project Settings.


#include "IVCharacterBase.h"

#include "Invoker/GAS/Attribute/IVAttributeSet.h"


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
	
}

// Called every frame
void AIVCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AIVCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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