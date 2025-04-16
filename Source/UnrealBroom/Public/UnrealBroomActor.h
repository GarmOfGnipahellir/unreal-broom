// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "UnrealBroomActor.generated.h"

USTRUCT()
struct UNREALBROOM_API FUnrealBroomFace
{
	GENERATED_BODY()

	UPROPERTY()
	FPlane Plane;

	UPROPERTY()
	TObjectPtr<UMaterialInterface> Material;

	FUnrealBroomFace();
	explicit FUnrealBroomFace(const FPlane& InPlane);
};

USTRUCT()
struct UNREALBROOM_API FUnrealBroomBrush
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FUnrealBroomFace> Faces;

	FUnrealBroomBrush();
	explicit FUnrealBroomBrush(const FBox& InBox);

	void BuildMesh(FMeshDescription* Desc) const;
};

UCLASS()
class UNREALBROOM_API AUnrealBroomActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> MyRootComponent;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UStaticMeshComponent>> MeshComponents;

	UPROPERTY()
	TArray<FUnrealBroomBrush> Brushes;

	AUnrealBroomActor();

	void AddBrush(const FUnrealBroomBrush& InBrush);
};
