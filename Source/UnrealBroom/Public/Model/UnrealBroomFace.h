// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnrealBroomHitResult.h"
#include "UnrealBroomFace.generated.h"

class UUnrealBroomBrush;

UCLASS()
class UUnrealBroomFace : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UUnrealBroomBrush* Brush;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FVector Normal;

	static UUnrealBroomFace* Create(const FVector Location, const FVector Normal);

	static TOptional<FVector> IntersectPoint(
		const UUnrealBroomFace* Face0,
		const UUnrealBroomFace* Face1,
		const UUnrealBroomFace* Face2);

	TOptional<FUnrealBroomHitFace> IntersectsLine(FVector Start, FVector End, FUnrealBroomHitResult& Result);
};
