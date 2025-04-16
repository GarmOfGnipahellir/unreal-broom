// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealBroomEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "FUnrealBroomEditorMode"

FUnrealBroomEditorModeCommands::FUnrealBroomEditorModeCommands()
	: TCommands<FUnrealBroomEditorModeCommands>(
		"UnrealBroomEditorMode",
		FText::FromString("UnrealBroom Editor Mode"),
		NAME_None,
		FAppStyle::GetAppStyleSetName()
	) {}

void FUnrealBroomEditorModeCommands::RegisterCommands()
{
	TArray<TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);
	UI_COMMAND(
		SelectionTool,
		"Selection",
		"Select brushes and faces",
		EUserInterfaceActionType::ToggleButton,
		FInputChord()
	);
	ToolCommands.Add(SelectionTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FUnrealBroomEditorModeCommands::GetCommands()
{
	return Get().Commands;
}

#undef LOCTEXT_NAMESPACE
