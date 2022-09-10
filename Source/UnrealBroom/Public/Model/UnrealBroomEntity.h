// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnrealBroomHitResult.h"
#include "UnrealBroomEntity.generated.h"

namespace UE::Geometry
{
	class FDynamicMesh3;
}

class UUnrealBroomBrush;

UCLASS()
class UUnrealBroomEntity : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UUnrealBroomBrush*> Brushes;

	void AddBrush(UUnrealBroomBrush* Brush);

	/**
	 * @brief Computes a triangulated dynamic mesh from brush faces.
	 * @return Computed dynamic mesh
	 */
	UE::Geometry::FDynamicMesh3 GetDynamicMesh();

	TOptional<TUnrealBroomHit<UUnrealBroomEntity>> IntersectsLine(
		FVector Start,
		FVector End,
		FUnrealBroomHitResult& Result);
};
