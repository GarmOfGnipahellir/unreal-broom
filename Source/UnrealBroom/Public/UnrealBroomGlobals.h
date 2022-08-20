// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnrealBroomActor.h"
#include "UObject/Object.h"
#include "UnrealBroomGlobals.generated.h"

UCLASS(config=UnrealBroom)
class UNREALBROOM_API UUnrealBroomGlobals : public UObject
{
	GENERATED_BODY()

public:
	static AUnrealBroomActor* GetWorldData(const UWorld* World);
	static AUnrealBroomActor* GetOrCreateWorldData(UWorld* World);
};
