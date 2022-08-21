// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputState.h"
#include "UnrealBroomActor.h"

class FUnrealBroomClient
{
public:
	TObjectPtr<AUnrealBroomActor> Target;

	explicit FUnrealBroomClient(AUnrealBroomActor* Target) : Target(Target)
	{
	}
};
