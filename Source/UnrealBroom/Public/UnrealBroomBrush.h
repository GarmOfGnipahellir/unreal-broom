// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealBroomCsg.h"
#include "UObject/Object.h"
#include "UnrealBroomBrush.generated.h"

using UnrealBroom::Csg::FBrush;

USTRUCT(BlueprintType)
struct FUnrealBroomPolygon
{
	GENERATED_BODY()

	TArray<FVector> Points;
	FPlane Plane;
};

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALBROOM_API UUnrealBroomBrush : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(Category="Unreal Broom|Brush", BlueprintCallable)
	static UUnrealBroomBrush* Cuboid(const FVector& Center, const FVector& Extent);

	UFUNCTION(Category="Unreal Broom|Brush", BlueprintCallable)
	TArray<FUnrealBroomPolygon> GetPolygons() const;

protected:
	FBrush Brush;
};
