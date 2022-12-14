// Copyright Arctic Beard Studios. All Rights Reserved.


#include "UnrealBroomGlobals.h"

#include "EngineUtils.h"
#include "UnrealBroomActor.h"
#include "Components/DynamicMeshComponent.h"
#include "Model/UnrealBroomBrush.h"

AUnrealBroomActor* UUnrealBroomGlobals::GetWorldData(const UWorld* World)
{
	if (const TActorIterator<AUnrealBroomActor> It(World); It)
	{
		return *It;
	}
	return nullptr;
}

AUnrealBroomActor* UUnrealBroomGlobals::GetOrCreateWorldData(UWorld* World)
{
	if (AUnrealBroomActor* Actor = GetWorldData(World))
	{
		return Actor;
	}
	AUnrealBroomActor* Actor = World->SpawnActor<AUnrealBroomActor>();
	Actor->Entity->AddBrush(UUnrealBroomBrush::CreateBox(FVector::ZeroVector, FVector::OneVector * 100.0));
	Actor->DynamicMeshComponent->SetMesh(Actor->Entity->GetDynamicMesh());
	return Actor;
}
