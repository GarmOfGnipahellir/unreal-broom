// Copyright Henrik Melsom. All Rights Reserved.

#include "UnrealBroomModule.h"
#include "UnrealBroomCommands.h"

class FUnrealBroomModule : public IUnrealBroomModule
{
public:
	virtual void StartupModule() override
	{
		FUnrealBroomCommands::Register();
	}

	virtual void ShutdownModule() override
	{
		FUnrealBroomCommands::Unregister();
	}
};

IMPLEMENT_MODULE(FUnrealBroomModule, UnrealBroom);
DEFINE_LOG_CATEGORY(LogUnrealBroom);
