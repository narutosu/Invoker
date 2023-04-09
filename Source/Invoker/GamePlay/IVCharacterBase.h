// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "IVCharacterBase.generated.h"

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//GAS
public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	TWeakObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UIVAttributeSet> AttributeSetBase;
};
