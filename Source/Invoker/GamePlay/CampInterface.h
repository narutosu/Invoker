// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "CampInterface.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UCampInterface : public UObject
{
	GENERATED_BODY()

	//是否可以通过点击 移动到它旁边并攻击或交互
	bool CanClickMoveTo(UCampInterface* target);
public:
	//所属的阵营
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camp)
	FGameplayTag CampTag;
};
