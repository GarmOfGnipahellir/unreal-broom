// Copyright Henrik Melsom. All Rights Reserved.

#include "UnrealBroomModule.h"

class FUnrealBroomModule : public IUnrealBroomModule
{
public:
	virtual void StartupModule() override{}

	virtual void ShutdownModule() override{}
};

IMPLEMENT_MODULE(FUnrealBroomModule, UnrealBroom);
DEFINE_LOG_CATEGORY(LogUnrealBroom);
