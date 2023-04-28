// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAssetCharacter.generated.h"

/**
 * 
 */
UCLASS()
class INVOKER_API UDataAssetCharacter : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UDataAssetCharacter();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Invoker|character")
	TArray<TSoftObjectPtr<class USkeletalMesh>> SkeletalMeshAssets;
};
