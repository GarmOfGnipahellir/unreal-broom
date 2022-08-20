// Copyright Henrik Melsom. All Rights Reserved.

#include "UnrealBroomEditorMode.h"

#include "EditorModeManager.h"
#include "UnrealBroomToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "UnrealBroomCommands.h"
#include "Tools/DefaultTool.h"


#define LOCTEXT_NAMESPACE "UnrealBroomEditorMode"

const FEditorModeID UUnrealBroomEditorMode::EM_UnrealBroomEditorModeId = TEXT("EM_UnrealBroomEditorMode");

FString UUnrealBroomEditorMode::SimpleToolName = TEXT("UnrealBroom_ActorInfoTool");
FString UUnrealBroomEditorMode::InteractiveToolName = TEXT("UnrealBroom_MeasureDistanceTool");
FString UUnrealBroomEditorMode::DefaultToolName = TEXT("UnrealBroom_DefaultTool");

UUnrealBroomEditorMode::UUnrealBroomEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(
		EM_UnrealBroomEditorModeId,
		LOCTEXT("ModeName", "UnrealBroom"),
		FSlateIcon(),
		true
	);
}


UUnrealBroomEditorMode::~UUnrealBroomEditorMode()
{
}


void UUnrealBroomEditorMode::ActorSelectionChangeNotify()
{
}

void UUnrealBroomEditorMode::Enter()
{
	UEdMode::Enter();

	const FUnrealBroomCommands& SampleToolCommands = FUnrealBroomCommands::Get();
	RegisterTool(
		SampleToolCommands.DefaultTool,
		DefaultToolName,
		NewObject<UDefaultToolBuilder>(this)
	);

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, DefaultToolName);
	GetToolManager()->ActivateTool(EToolSide::Left);
}

void UUnrealBroomEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FUnrealBroomToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UUnrealBroomEditorMode::GetModeCommands() const
{
	return FUnrealBroomCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
