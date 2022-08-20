// Copyright Arctic Beard Studios. All Rights Reserved.


#include "UnrealBroomActor.h"

#include "Components/DynamicMeshComponent.h"


AUnrealBroomActor::AUnrealBroomActor()
{
	PrimaryActorTick.bCanEverTick = false;

	DynamicMeshComponent = CreateDefaultSubobject<UDynamicMeshComponent>(TEXT("DynamicMeshComponent"));
	DynamicMeshComponent->SetMobility(EComponentMobility::Movable);
	DynamicMeshComponent->SetGenerateOverlapEvents(false);
	DynamicMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

	DynamicMeshComponent->CollisionType = CTF_UseDefault;

	DynamicMeshComponent->SetMaterial(0, UMaterial::GetDefaultMaterial(MD_Surface)); // is this necessary?

	SetRootComponent(DynamicMeshComponent);
}

void AUnrealBroomActor::BeginPlay()
{
	Super::BeginPlay();
}
