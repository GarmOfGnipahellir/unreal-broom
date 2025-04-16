// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolBuilder.h"
#include "BaseBehaviors/BehaviorTargetInterfaces.h"
#include "SelectionTool.generated.h"

class AUnrealBroomActor;
/**
 * 
 */
UCLASS()
class UNREALBROOMEDITOR_API USelectionToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};

UCLASS(Transient)
class USelectionToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()
};

UCLASS()
class USelectionTool : public UInteractiveTool, public IClickDragBehaviorTarget
{
	GENERATED_BODY()

public:
	void SetUnrealBroomActor(AUnrealBroomActor* InUnrealBroomActor);
	
	virtual void Setup() override;
	virtual void Render(IToolsContextRenderAPI* RenderAPI) override;

	virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;
	virtual void OnClickPress(const FInputDeviceRay& PressPos) override;
	virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;
	virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;
	virtual void OnTerminateDragSequence() override;

protected:
	UPROPERTY()
	TObjectPtr<USelectionToolProperties> Properties;

	UPROPERTY()
	TObjectPtr<AUnrealBroomActor> UnrealBroomActor;

	double DefaultHeight;
	FVector PressLocation;
	FBox Box;
};
