// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Face.h"

class FPoly
{
public:
	struct FVert
	{
		FVector Location;
		FVector Normal;
		FVector2D UV;
	};

	FVector Normal;
	TArray<FVert> Verts;
	uint16 MaterialID;

	explicit FPoly(const FVector Normal, const uint16 MaterialID) : Normal(Normal), MaterialID(MaterialID)
	{
	}

	void CreateVert(const FVector Location, const FFace Face);

	TOptional<TArray<FVert>> GetOrderedVerts() const;
};
