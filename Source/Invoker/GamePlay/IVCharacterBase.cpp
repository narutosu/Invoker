// Fill out your copyright notice in the Description page of Project Settings.


#include "IVCharacterBase.h"


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