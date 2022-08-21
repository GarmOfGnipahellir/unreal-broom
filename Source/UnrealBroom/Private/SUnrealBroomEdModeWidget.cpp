// Copyright Arctic Beard Studios. All Rights Reserved.


#include "SUnrealBroomEdModeWidget.h"

#include "EditorModeManager.h"
#include "SlateOptMacros.h"
#include "UnrealBroomEdMode.h"
#include "Widgets/Layout/SScrollBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUnrealBroomEdModeWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		  .VAlign(VAlign_Top)
		  .Padding(5.0f)
		[
			SNew(STextBlock)
			.Text(FText::FromString("This is an editor mode example."))
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FUnrealBroomEdMode* SUnrealBroomEdModeWidget::GetEdMode() const
{
	return (FUnrealBroomEdMode*)(GLevelEditorModeTools().GetActiveMode(FUnrealBroomEdMode::EM_UnrealBroom));
}
