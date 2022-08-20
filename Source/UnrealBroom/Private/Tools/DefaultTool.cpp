// Copyright Arctic Beard Studios. All Rights Reserved.


#include "DefaultTool.h"

#include "EngineUtils.h"
#include "InteractiveToolManager.h"
#include "UnrealBroomGlobals.h"
#include "BaseBehaviors/ClickDragBehavior.h"
#include "Model/Brush.h"
#include "Model/Face.h"
#include "Model/Poly.h"

UInteractiveTool* UDefaultToolBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	UDefaultTool* NewTool = NewObject<UDefaultTool>(SceneState.ToolManager);
	NewTool->SetTarget(UUnrealBroomGlobals::GetOrCreateWorldData(SceneState.World));
	return NewTool;
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

FInputRayHit UDefaultTool::CanBeginClickDragSequence(const FInputDeviceRay& PressPos)
{
	return FInputRayHit();
}

void UDefaultTool::OnClickPress(const FInputDeviceRay& PressPos)
{
}

void UDefaultTool::OnClickDrag(const FInputDeviceRay& DragPos)
{
}

void UDefaultTool::OnClickRelease(const FInputDeviceRay& ReleasePos)
{
}

void UDefaultTool::OnTerminateDragSequence()
{
}

void UDefaultTool::Render(IToolsContextRenderAPI* RenderAPI)
{
	FPrimitiveDrawInterface* PDI = RenderAPI->GetPrimitiveDrawInterface();
	for (const auto Brush : Target->Entity.Brushes)
	{
		for (const auto Face : Brush->Faces)
		{
			PDI->DrawPoint(Face->Location, FLinearColor::White, 16.0f, SDPG_World);
			PDI->DrawLine(
				Face->Location,
				Face->Location + Face->Normal * 50.0f,
				FLinearColor::White,
				SDPG_World
			);
		}

		for (const auto Poly : Brush->GetPolys())
		{
			for (int i = 1; i < Poly.Verts.Num(); ++i)
			{
				FPoly::FVert Vert0 = Poly.Verts[i - 1];
				FPoly::FVert Vert1 = Poly.Verts[i];

				PDI->DrawPoint(Vert0.Location, FLinearColor::White, 16.0f, SDPG_World);
				PDI->DrawLine(
					Vert0.Location,
					Vert1.Location,
					FLinearColor::White,
					SDPG_World
				);
			}
		}
	}
}

void UDefaultTool::SetTarget(AUnrealBroomActor* NewTarget)
{
	Target = NewTarget;
}
