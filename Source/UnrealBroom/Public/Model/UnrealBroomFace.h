// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnrealBroomFace.generated.h"

UCLASS()
class UUnrealBroomFace : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FVector Normal;

	static UUnrealBroomFace* Create(const FVector Location, const FVector Normal);

	static TOptional<FVector> IntersectPoint(
		const UUnrealBroomFace* Face0,
		const UUnrealBroomFace* Face1,
		const UUnrealBroomFace* Face2);

	bool IntersectsLine(FVector Start, FVector End, FVector& OutPoint) const;
};
