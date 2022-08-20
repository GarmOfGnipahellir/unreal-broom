// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FFace
{
public:
	FVector Location;
	FVector Normal;

	FFace(const FVector Location, const FVector Normal) : Location(Location), Normal(Normal)
	{
	}

	static TOptional<FVector> IntersectPoint(const FFace Face0, const FFace Face1, const FFace Face2);
};
