// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionTool.h"

#include "InteractiveToolManager.h"
#include "ToolBuilderUtil.h"
#include "UnrealBroomActor.h"
#include "BaseBehaviors/ClickDragBehavior.h"

bool USelectionToolBuilder::CanBuildTool(const FToolBuilderState& SceneState) const
{
	return true;
}

UInteractiveTool* USelectionToolBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	USelectionTool* NewTool = NewObject<USelectionTool>(SceneState.ToolManager);
	AUnrealBroomActor* UnrealBroomActor = ToolBuilderUtil::FindFirstActorOfType<AUnrealBroomActor>(SceneState);
	if (!UnrealBroomActor)
	{
		UnrealBroomActor = SceneState.World->SpawnActor<AUnrealBroomActor>();
		GEditor->SelectActor(UnrealBroomActor, true, true);
	}
	NewTool->SetUnrealBroomActor(UnrealBroomActor);
	return NewTool;
}

void USelectionTool::SetUnrealBroomActor(AUnrealBroomActor* InUnrealBroomActor)
{
	UnrealBroomActor = InUnrealBroomActor;
}

void USelectionTool::Setup()
{
	UClickDragInputBehavior* MouseBehavior = NewObject<UClickDragInputBehavior>();
	MouseBehavior->Initialize(this);
	AddInputBehavior(MouseBehavior);

	Properties = NewObject<USelectionToolProperties>(this, "Selection");
	AddToolPropertySource(Properties);

	DefaultHeight = 50;
}

void USelectionTool::Render(IToolsContextRenderAPI* RenderAPI)
{
	DrawWireBox(RenderAPI->GetPrimitiveDrawInterface(), Box, FLinearColor::White, SDPG_World);
}

FInputRayHit USelectionTool::CanBeginClickDragSequence(const FInputDeviceRay& PressPos)
{
	const FPlane DefaultPlane = FPlane(FVector::UnitZ(), 0.0);
	const double Distance = FMath::RayPlaneIntersectionParam(
		PressPos.WorldRay.Origin,
		PressPos.WorldRay.Direction,
		DefaultPlane
	);
	return FInputRayHit(Distance);
}

void USelectionTool::OnClickPress(const FInputDeviceRay& PressPos)
{
	const FPlane DefaultPlane = FPlane(FVector::UnitZ(), 0.0);
	PressLocation = FMath::RayPlaneIntersection(
		PressPos.WorldRay.Origin,
		PressPos.WorldRay.Direction,
		DefaultPlane
	);
}

void USelectionTool::OnClickDrag(const FInputDeviceRay& DragPos)
{
	const FPlane DefaultPlane = FPlane(FVector::UnitZ(), 0.0);
	FVector DragLocation = FMath::RayPlaneIntersection(
		DragPos.WorldRay.Origin,
		DragPos.WorldRay.Direction,
		DefaultPlane
	);
	DragLocation.Z = PressLocation.Z + DefaultHeight;
	const FVector MinLocation = FVector::Min(PressLocation, DragLocation);
	const FVector MaxLocation = FVector::Max(PressLocation, DragLocation);
	Box = FBox(MinLocation, MaxLocation);
}

void USelectionTool::OnClickRelease(const FInputDeviceRay& ReleasePos)
{
	UnrealBroomActor->AddBrush(FUnrealBroomBrush(Box));
	Box = FBox(FVector::Zero(), FVector::Zero());
}

void USelectionTool::OnTerminateDragSequence() {}
