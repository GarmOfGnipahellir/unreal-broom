// Copyright Henrik Melsom. All Rights Reserved.

#include "UnrealBroomEditorModule.h"

#include "UnrealBroomEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "FUnrealBroomEditorModule"

class FUnrealBroomEditorModule : public IUnrealBroomEditorModule
{
public:
	virtual void StartupModule() override
	{
		FUnrealBroomEditorModeCommands::Register();
	}

	virtual void ShutdownModule() override
	{
		FUnrealBroomEditorModeCommands::Unregister();
	}
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealBroomEditorModule, UnrealBroomEditor);
DEFINE_LOG_CATEGORY(LogUnrealBroomEditor);
