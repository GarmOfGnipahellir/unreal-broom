// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveTool.h"
#include "InteractiveToolBuilder.h"
#include "UnrealBroomActor.h"
#include "BaseTools/ClickDragTool.h"
#include "DefaultTool.generated.h"

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
	virtual void Setup() override;
	virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;

	virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;
	virtual void OnClickPress(const FInputDeviceRay& PressPos) override;
	virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;
	virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;
	virtual void OnTerminateDragSequence() override;
	
	virtual void Render(IToolsContextRenderAPI* RenderAPI) override;

	void SetTarget(AUnrealBroomActor* NewTarget);

protected:
	UPROPERTY()
	TObjectPtr<UDefaultToolProperties> Properties;

	UPROPERTY()
	AUnrealBroomActor* Target;

	static constexpr int ShiftModifierID = 1;
	static constexpr int CtrlModifierID = 2;
	static constexpr int AltModifierID = 3;

	bool bShiftDown = false;
	bool bCtrlDown = false;
	bool bAltDown = false;
};
