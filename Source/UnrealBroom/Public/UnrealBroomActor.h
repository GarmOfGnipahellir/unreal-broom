// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Model/UnrealBroomEntity.h"
#include "UnrealBroomActor.generated.h"

class UDynamicMeshComponent;

UCLASS()
class UNREALBROOM_API AUnrealBroomActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UUnrealBroomEntity* Entity;

	UPROPERTY(Category=UnrealBroomActor, VisibleAnywhere, BlueprintReadOnly)
	UDynamicMeshComponent* DynamicMeshComponent;

	AUnrealBroomActor();

protected:
	virtual void BeginPlay() override;
};
