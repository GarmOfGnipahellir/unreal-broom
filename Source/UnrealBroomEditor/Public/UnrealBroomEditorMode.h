// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tools/UEdMode.h"
#include "UnrealBroomEditorMode.generated.h"

class AUnrealBroomActor;
/**
 * 
 */
UCLASS()
class UNREALBROOMEDITOR_API UUnrealBroomEditorMode : public UEdMode
{
	GENERATED_BODY()

public:
	static FEditorModeID EM_UnrealBroomEditorModeId;
	
	UUnrealBroomEditorMode();

	virtual void Enter() override;
	virtual void CreateToolkit() override;
	virtual TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetModeCommands() const override;
};
