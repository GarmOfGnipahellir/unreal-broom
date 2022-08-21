// Copyright Henrik Melsom. All Rights Reserved.

#include "UnrealBroomModule.h"

#include "EditorModeRegistry.h"
#include "UnrealBroomEdMode.h"

class FUnrealBroomModule : public IUnrealBroomModule
{
public:
	virtual void StartupModule() override
	{
		FEditorModeRegistry::Get().RegisterMode<FUnrealBroomEdMode>(
			FUnrealBroomEdMode::EM_UnrealBroom,
			FText::FromString("Unreal Broom"),
			FSlateIcon(),
			true,
			100
		);
	}

	virtual void ShutdownModule() override
	{
		FEditorModeRegistry::Get().UnregisterMode(FUnrealBroomEdMode::EM_UnrealBroom);
	}
};

IMPLEMENT_MODULE(FUnrealBroomModule, UnrealBroom);
DEFINE_LOG_CATEGORY(LogUnrealBroom);
