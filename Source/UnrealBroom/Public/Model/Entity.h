// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace UE::Geometry
{
	class FDynamicMesh3;
}

class FBrush;

class FEntity
{
public:
	TArray<TSharedRef<FBrush>> Brushes;

	/**
	 * @brief Computes a triangulated dynamic mesh from brush faces.
	 * @return Computed dynamic mesh
	 */
	UE::Geometry::FDynamicMesh3 GetDynamicMesh();
};
