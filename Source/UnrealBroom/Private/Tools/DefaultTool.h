// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveTool.h"
#include "InteractiveToolBuilder.h"
#include "BaseTools/ClickDragTool.h"

UCLASS()
class UNREALBROOM_API UDefaultToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override
	{
		return true;
	}

	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};

UCLASS(Transient)
class UNREALBROOM_API UDefaultToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()
};

UCLASS()
class UNREALBROOM_API UDefaultTool : public UInteractiveTool, public IClickDragBehaviorTarget
{
	GENERATED_BODY()

public:
	UDefaultTool();

	virtual void Setup() override;
	virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;

	void SetWorld(UWorld* NewWorld);

protected:
	UPROPERTY()
	TObjectPtr<UDefaultToolProperties> Properties;

	UPROPERTY()
	UWorld* World;

	static const int ShiftModifierID = 1;
	static const int CtrlModifierID = 2;
	static const int AltModifierID = 3;

	bool bShiftDown = false;
	bool bCtrlDown = false;
	bool bAltDown = false;
};
