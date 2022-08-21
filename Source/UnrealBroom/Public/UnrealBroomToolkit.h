// Copyright Henrik Melsom. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SUnrealBroomEdModeWidget.h"
#include "Toolkits/BaseToolkit.h"

/**
 * This FModeToolkit just creates a basic UI panel that allows various InteractiveTools to
 * be initialized, and a DetailsView used to show properties of the active Tool.
 */
class FUnrealBroomToolkit : public FModeToolkit
{
public:
	FUnrealBroomToolkit();

	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;
	virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<SWidget> GetInlineContent() const override;

protected:
	TSharedPtr<SUnrealBroomEdModeWidget> UnrealBroomEdModeWidget;
};
