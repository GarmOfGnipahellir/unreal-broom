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
		"Default",
		"",
		EUserInterfaceActionType::RadioButton,
		FInputChord()
	);
	ToolCommands.Add(DefaultTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FUnrealBroomCommands::GetCommands()
{
	return Get().Commands;
}

#undef LOCTEXT_NAMESPACE
