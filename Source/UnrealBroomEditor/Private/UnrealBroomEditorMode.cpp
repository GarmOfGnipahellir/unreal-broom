// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealBroomEditorMode.h"

#include "InteractiveToolManager.h"
#include "UnrealBroomEditorModeCommands.h"
#include "UnrealBroomEditorModeToolkit.h"
#include "Tools/SelectionTool.h"

FEditorModeID UUnrealBroomEditorMode::EM_UnrealBroomEditorModeId("EditorMode.UnrealBroom");

UUnrealBroomEditorMode::UUnrealBroomEditorMode()
{
	Info = FEditorModeInfo(EM_UnrealBroomEditorModeId, FText::FromString("UnrealBroom"), FSlateIcon(), true);
}

void UUnrealBroomEditorMode::Enter()
{
	Super::Enter();

	const FUnrealBroomEditorModeCommands& Commands = FUnrealBroomEditorModeCommands::Get();

	RegisterTool(Commands.SelectionTool, TEXT("SelectionTool"), NewObject<USelectionToolBuilder>(this));

	GetToolManager()->SelectActiveToolType(EToolSide::Left, TEXT("SelectionTool"));
	GetToolManager()->ActivateTool(EToolSide::Left);
}

void UUnrealBroomEditorMode::CreateToolkit()
{
	Toolkit = MakeShared<FUnrealBroomEditorModeToolkit>();
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UUnrealBroomEditorMode::GetModeCommands() const
{
	return FUnrealBroomEditorModeCommands::GetCommands();
}
