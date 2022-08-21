// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"
#include "UnrealBroomActor.h"
#include "UnrealBroomSelection.h"

/**
 * 
 */
class UNREALBROOM_API FUnrealBroomEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_UnrealBroom;

	TObjectPtr<AUnrealBroomActor> WorldData;
	TObjectPtr<UUnrealBroomSelection> Selection;

	// Begin FEdMode interface

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	virtual bool HandleClick(
		FEditorViewportClient* InViewportClient,
		HHitProxy* HitProxy,
		const FViewportClick& Click) override;
	virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;
	virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;
	virtual bool InputKey(
		FEditorViewportClient* ViewportClient,
		FViewport* Viewport,
		FKey Key,
		EInputEvent Event) override;

	/// Disables camera mouse movement if it returns true.
	virtual bool DisallowMouseDeltaTracking() const override;

	// End FEdMode interface

	template <typename T>
	bool MouseTrace(FEditorViewportClient* ViewportClient, T*& OutTarget);
};
