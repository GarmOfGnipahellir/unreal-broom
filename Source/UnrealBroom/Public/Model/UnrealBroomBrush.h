// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnrealBroomHitResult.h"
#include "UnrealBroomBrush.generated.h"

class UUnrealBroomEntity;
class FUnrealBroomPoly;
class UUnrealBroomFace;

UCLASS()
class UUnrealBroomBrush : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UUnrealBroomEntity* Entity;

	UPROPERTY()
	TArray<UUnrealBroomFace*> Faces;

	/**
	 * @brief Creates a brush with faces to make a box.
	 * @param Location Box center
	 * @param Extent How far from the center each face is
	 * @return The constructed brush
	 */
	static UUnrealBroomBrush* CreateBox(const FVector Location, const FVector Extent);

	void AddFace(const FVector Location, const FVector Normal);

	/**
	 * @brief Computes the polygons making up this brush, and returns them.
	 * @return Array of polygons
	 */
	TArray<FUnrealBroomPoly> GetPolys();

	bool ContainsPoint(FVector Point) const;

	TOptional<FUnrealBroomHitBrush> IntersectsLine(FVector Start, FVector End, FUnrealBroomHitResult& Result);
};
