// Copyright Henrik Melsom. All Rights Reserved.

#include "UnrealBroomToolkit.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "UnrealBroomEditorModeToolkit"

FUnrealBroomToolkit::FUnrealBroomToolkit()
{
}

void FUnrealBroomToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FUnrealBroomToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FUnrealBroomToolkit::GetToolkitFName() const
{
	return FName("UnrealBroomEditorMode");
}

FText FUnrealBroomToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "UnrealBroomEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE
