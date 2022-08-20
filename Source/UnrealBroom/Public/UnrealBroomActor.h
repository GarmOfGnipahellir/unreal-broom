// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Model/Entity.h"
#include "UnrealBroomActor.generated.h"

UCLASS()
class UNREALBROOM_API AUnrealBroomActor : public AActor
{
	GENERATED_BODY()

public:
	FEntity Entity;

	AUnrealBroomActor();

protected:
	virtual void BeginPlay() override;
};
