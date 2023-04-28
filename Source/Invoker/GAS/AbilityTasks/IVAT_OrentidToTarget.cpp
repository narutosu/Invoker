// Fill out your copyright notice in the Description page of Project Settings.


#include "IVAT_OrentidToTarget.h"
#include "Invoker/GamePlay/IVCharacterBase.h"
#include "Invoker/GamePlay/IVPlayerController.h"

UIVAT_OrentidToTarget::UIVAT_OrentidToTarget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RegisteredCallback = false;
}

UIVAT_OrentidToTarget* UIVAT_OrentidToTarget::OrentedToTarget(class UGameplayAbility* OwningAbility)
{
	UIVAT_OrentidToTarget* MyObj = NewAbilityTask<UIVAT_OrentidToTarget>(OwningAbility);
	return  MyObj;
}

void UIVAT_OrentidToTarget::Activate()
{
	if (Ability)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		AIVCharacterBase* character = Cast<AIVCharacterBase>(ActorInfo->AvatarActor);
		AIVPlayerController* controller = Cast<AIVPlayerController>(character->GetController());
		//FRotator DeltaRotator;
		FHitResult Hit;
		bool bHitSuccessful = controller->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);
		FVector ActorLocation = character->GetActorLocation();
		FVector MouseLocation = Hit.Location;
		FRotator TargetRotator = (MouseLocation-ActorLocation).Rotation();
		FRotator CharacterRotation = character->GetActorTransform().Rotator();
		float DeltaYaw = TargetRotator.Yaw-CharacterRotation.Yaw;
		DeltaYaw = UE::Math::TRotator<float>::NormalizeAxis(DeltaYaw);
		character->CanSkillDelegate.AddDynamic(this, &UIVAT_OrentidToTarget::OnOrentidEnd);
		character->SkillNeedNewDeltaYaw.Broadcast(DeltaYaw,true);
	}
}

void UIVAT_OrentidToTarget::OnOrentidEnd()
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnOrentidEndDelegate.Broadcast();
	}
	EndTask();
}

//end ability的时候调用
void UIVAT_OrentidToTarget::OnDestroy(bool AbilityEnded)
{
	//先停止技能转身
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	AIVCharacterBase* character = Cast<AIVCharacterBase>(ActorInfo->AvatarActor);
	character->SkillNeedNewDeltaYaw.Broadcast(0,false);
	
	Super::OnDestroy(AbilityEnded);
}
