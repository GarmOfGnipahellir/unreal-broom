// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UUnrealBroomFace;

struct FUnrealBroomVert
{
	FVector Location;
	FVector Normal;
	FVector2D UV;
};

class FUnrealBroomPoly
{
public:
	FVector Normal;
	TArray<FUnrealBroomVert> Verts;
	uint16 MaterialID;

	explicit FUnrealBroomPoly(const FVector Normal, const uint16 MaterialID) : Normal(Normal), MaterialID(MaterialID)
	{
	}

	void CreateVert(const FVector Location, const UUnrealBroomFace* Face);

	void OrderVerts();
};
