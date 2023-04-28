// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "IVAT_OrentidToTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIVAT_OrentidToTargetDelegate);
/**
 * 
 */
UCLASS()
class INVOKER_API UIVAT_OrentidToTarget : public UAbilityTask
{
	GENERATED_BODY()
public:
	// Constructor and overrides
	UIVAT_OrentidToTarget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	FIVAT_OrentidToTargetDelegate OnOrentidEndDelegate;

	virtual void Activate() override;
	UFUNCTION()
	void OnOrentidEnd();
	
	/** Wait until the server confirms the use of this ability. This is used to gate predictive portions of the ability */
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UIVAT_OrentidToTarget* OrentedToTarget(UGameplayAbility* OwningAbility);

protected:

	virtual void OnDestroy(bool AbilityEnded) override;
	bool RegisteredCallback;
};
