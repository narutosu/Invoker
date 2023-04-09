// Copyright Epic Games, Inc. All Rights Reserved.

#include "InvokerGameMode.h"
#include "InvokerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInvokerGameMode::AInvokerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
