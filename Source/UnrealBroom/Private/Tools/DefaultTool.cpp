// Copyright Arctic Beard Studios. All Rights Reserved.


#include "DefaultTool.h"

#include "InteractiveToolManager.h"
#include "BaseBehaviors/ClickDragBehavior.h"

UInteractiveTool* UDefaultToolBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	UDefaultTool* NewTool = NewObject<UDefaultTool>(SceneState.ToolManager);
	NewTool->SetWorld(SceneState.World);
	return NewTool;
}

UDefaultTool::UDefaultTool()
{
}

void UDefaultTool::Setup()
{
	Super::Setup();

	UClickDragInputBehavior* MouseBehavior = NewObject<UClickDragInputBehavior>();
	MouseBehavior->Modifiers.RegisterModifier(ShiftModifierID, FInputDeviceState::IsShiftKeyDown);
	MouseBehavior->Modifiers.RegisterModifier(CtrlModifierID, FInputDeviceState::IsCtrlKeyDown);
	MouseBehavior->Modifiers.RegisterModifier(AltModifierID, FInputDeviceState::IsAltKeyDown);
	MouseBehavior->Initialize(this);
	AddInputBehavior(MouseBehavior);

	Properties = NewObject<UDefaultToolProperties>(this);
	AddToolPropertySource(Properties);
}

void UDefaultTool::OnUpdateModifierState(const int ModifierID, const bool bIsOn)
{
	switch (ModifierID)
	{
	case ShiftModifierID:
		bShiftDown = bIsOn;
		break;
	case CtrlModifierID:
		bCtrlDown = bIsOn;
		break;
	case AltModifierID:
		bAltDown = bIsOn;
		break;
	default: break;
	}
}

void UDefaultTool::SetWorld(UWorld* NewWorld)
{
	World = NewWorld;
}
