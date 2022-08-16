// Copyright Henrik Melsom. All Rights Reserved.

#include "UnrealBroomCommands.h"
#include "UnrealBroomEditorMode.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "UnrealBroomCommands"

FUnrealBroomCommands::FUnrealBroomCommands()
	: TCommands<FUnrealBroomCommands>(
		"UnrealBroomEditorMode",
		NSLOCTEXT("UnrealBroomEditorMode", "UnrealBroomCommands", "UnrealBroom Editor Mode"),
		NAME_None,
		FEditorStyle::GetStyleSetName()
	)
{
}

void FUnrealBroomCommands::RegisterCommands()
{
	TArray<TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);

	UI_COMMAND(
		DefaultTool,
		"Show Actor Info",
		"Opens message box with info about a clicked actor",
		EUserInterfaceActionType::Button,
		FInputChord()
	);
	ToolCommands.Add(DefaultTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FUnrealBroomCommands::GetCommands()
{
	return Get().Commands;
}

#undef LOCTEXT_NAMESPACE
