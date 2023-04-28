// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Containers/UnrealString.h"
#include "Logging/LogMacros.h"

class UObject;

INVOKER_API DECLARE_LOG_CATEGORY_EXTERN(LogInvoker, Log, All);
INVOKER_API DECLARE_LOG_CATEGORY_EXTERN(LogInvokerAbilitySystem, Log, All);

INVOKER_API FString GetClientServerContextString(UObject* ContextObject = nullptr);
