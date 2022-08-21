// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnrealBroomSelection.generated.h"

class UUnrealBroomFace;
class UUnrealBroomBrush;

UCLASS()
class UUnrealBroomSelection : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UUnrealBroomBrush*> Brushes;

	UPROPERTY()
	TArray<UUnrealBroomFace*> Faces;

	void Select(UUnrealBroomBrush* Brush);
	void Select(UUnrealBroomFace* Face);

	void Deselect(UUnrealBroomBrush* Brush);
	void Deselect(UUnrealBroomFace* Face);

	void DeselectAll();

	bool IsSelected(UUnrealBroomBrush* Brush) const;
	bool IsSelected(UUnrealBroomFace* Face) const;
};
