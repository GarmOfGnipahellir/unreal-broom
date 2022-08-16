// Copyright Henrik Melsom. All Rights Reserved.

#include "UnrealBroomEditorMode.h"
#include "UnrealBroomToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "UnrealBroomCommands.h"

#include "Tools/UnrealBroomSimpleTool.h"
#include "Tools/UnrealBroomInteractiveTool.h"


#define LOCTEXT_NAMESPACE "UnrealBroomEditorMode"

const FEditorModeID UUnrealBroomEditorMode::EM_UnrealBroomEditorModeId = TEXT("EM_UnrealBroomEditorMode");

FString UUnrealBroomEditorMode::SimpleToolName = TEXT("UnrealBroom_ActorInfoTool");
FString UUnrealBroomEditorMode::InteractiveToolName = TEXT("UnrealBroom_MeasureDistanceTool");


UUnrealBroomEditorMode::UUnrealBroomEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(
		UUnrealBroomEditorMode::EM_UnrealBroomEditorModeId,
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

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UUnrealBroomSimpleToolBuilder>(this));
	RegisterTool(
		SampleToolCommands.InteractiveTool,
		InteractiveToolName,
		NewObject<UUnrealBroomInteractiveToolBuilder>(this)
	);

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
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
