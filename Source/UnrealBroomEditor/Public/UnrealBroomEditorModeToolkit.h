// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALBROOMEDITOR_API FUnrealBroomEditorModeToolkit : public FModeToolkit
{
public:
	FUnrealBroomEditorModeToolkit() {}

	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override
	{
		FModeToolkit::Init(InitToolkitHost, InOwningMode);
	}

	virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override { PaletteNames.Add(NAME_Default); }
	virtual FName GetToolkitFName() const override { return FName("UnrealBroomEditorModeToolkit"); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString("UnrealBroom Editor Mode"); }
};
