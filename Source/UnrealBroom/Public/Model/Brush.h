// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FFace;

class FBrush
{
public:
	TArray<TSharedRef<FFace>> Faces;

	/**
	 * @brief Creates a brush with faces to make a box.
	 * @param Location Box center
	 * @param Extent How far from the center each face is
	 * @return The constructed brush
	 */
	static FBrush* CreateBox(const FVector Location, const FVector Extent);

	/**
	 * @brief Computes the polygons making up this brush, and returns them.
	 * @return Array of polygons
	 */
	TArray<FPoly> GetPolys();
};
