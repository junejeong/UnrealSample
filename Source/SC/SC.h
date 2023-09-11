// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(SC_LOG, Log, All);

#define SCLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define SC_LOG_S(Verbosity) UE_LOG(SC_LOG, Verbosity, TEXT("%s"), *SCLOG_CALLINFO)
#define SC_LOG(Verbosity, Format, ...) UE_LOG(SC_LOG, Verbosity, TEXT("%s %s"), *SCLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))


