// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IVCharacterBase.h"
#include "IVCharacterRole.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API AIVCharacterRole : public AIVCharacterBase
{
	GENERATED_BODY()
public:
	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;
};
