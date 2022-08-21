// Copyright Henrik Melsom. All Rights Reserved.

#include "UnrealBroomToolkit.h"
#include "EditorModeManager.h"
#include "UnrealBroomEdMode.h"

#define LOCTEXT_NAMESPACE "UnrealBroomEditorModeToolkit"

FUnrealBroomToolkit::FUnrealBroomToolkit()
{
	SAssignNew(UnrealBroomEdModeWidget, SUnrealBroomEdModeWidget);
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

FEdMode* FUnrealBroomToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FUnrealBroomEdMode::EM_UnrealBroom);
}

TSharedPtr<SWidget> FUnrealBroomToolkit::GetInlineContent() const
{
	return UnrealBroomEdModeWidget;
}

#undef LOCTEXT_NAMESPACE
