// Copyright Arctic Beard Studios. All Rights Reserved.

#include "UnrealBroomSelection.h"

void UUnrealBroomSelection::Select(UUnrealBroomBrush* Brush)
{
	if (!IsSelected(Brush))
	{
		const FScopedTransaction Transaction(FText::FromString("Select Brush"));
		Modify();

		Brushes.Add(Brush);
	}
}

void UUnrealBroomSelection::Select(UUnrealBroomFace* Face)
{
	if (!IsSelected(Face))
	{
		Faces.Add(Face);
	}
}

void UUnrealBroomSelection::Deselect(UUnrealBroomBrush* Brush)
{
	if (IsSelected(Brush))
	{
		Brushes.Remove(Brush);
	}
}

void UUnrealBroomSelection::Deselect(UUnrealBroomFace* Face)
{
	if (IsSelected(Face))
	{
		Faces.Remove(Face);
	}
}

void UUnrealBroomSelection::DeselectAll()
{
	FScopedTransaction Transaction(FText::FromString("Deselect All"));
	Modify();

	Brushes.Empty();
	Faces.Empty();
}

bool UUnrealBroomSelection::IsSelected(UUnrealBroomBrush* Brush) const
{
	return Brushes.Contains(Brush);
}

bool UUnrealBroomSelection::IsSelected(UUnrealBroomFace* Face) const
{
	return Faces.Contains(Face);
}
