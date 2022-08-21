// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FUnrealBroomEdMode;

/**
 * 
 */
class UNREALBROOM_API SUnrealBroomEdModeWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUnrealBroomEdModeWidget)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FUnrealBroomEdMode* GetEdMode() const;
};
