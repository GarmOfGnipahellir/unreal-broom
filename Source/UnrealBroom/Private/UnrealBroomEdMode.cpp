// Copyright Arctic Beard Studios. All Rights Reserved.


#include "UnrealBroomEdMode.h"

#include "EditorModeManager.h"
#include "UnrealBroomGlobals.h"
#include "UnrealBroomModule.h"
#include "UnrealBroomToolkit.h"
#include "Model/UnrealBroomBrush.h"
#include "Model/UnrealBroomFace.h"
#include "Model/UnrealBroomPoly.h"
#include "Toolkits/ToolkitManager.h"

const FEditorModeID FUnrealBroomEdMode::EM_UnrealBroom("EM_UnrealBroom");

void FUnrealBroomEdMode::Enter()
{
	FEdMode::Enter();

	WorldData = UUnrealBroomGlobals::GetOrCreateWorldData(GetWorld());
	Selection = NewObject<UUnrealBroomSelection>(GetTransientPackage(), "UnrealBroomSelection", RF_Transactional);

	if (!Toolkit.IsValid())
	{
		Toolkit = MakeShareable(new FUnrealBroomToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FUnrealBroomEdMode::Exit()
{
	FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
	Toolkit.Reset();

	FEdMode::Exit();
}

void FUnrealBroomEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	for (const auto Brush : WorldData->Entity->Brushes)
	{
		if (Selection->IsSelected(Brush))
		{
			for (const auto Poly : Brush->GetPolys())
			{
				for (int i = 1; i < Poly.Verts.Num(); ++i)
				{
					FUnrealBroomVert Vert0 = Poly.Verts[i - 1];
					FUnrealBroomVert Vert1 = Poly.Verts[i];

					PDI->DrawLine(
						Vert0.Location,
						Vert1.Location,
						FLinearColor::Red,
						SDPG_Foreground
					);
				}
			}
		}

		for (int i = 0; i < Brush->Faces.Num(); ++i)
		{
			if (Selection->IsSelected(Brush->Faces[i]))
			{
				FUnrealBroomPoly Poly = Brush->GetPolys()[i];
				for (int j = 1; j < Poly.Verts.Num(); ++j)
				{
					FUnrealBroomVert Vert0 = Poly.Verts[j - 1];
					FUnrealBroomVert Vert1 = Poly.Verts[j];

					PDI->DrawLine(
						Vert0.Location,
						Vert1.Location,
						FLinearColor::Yellow,
						SDPG_Foreground
					);
				}
			}
		}
	}
}

bool FUnrealBroomEdMode::HandleClick(
	FEditorViewportClient* InViewportClient,
	HHitProxy* HitProxy,
	const FViewportClick& Click)
{
	if (auto HitResult = MouseTrace(InViewportClient))
	{
		if (Click.IsShiftDown() && HitResult->GetFirstFace())
		{
			Selection->Select(HitResult->GetFirstFace()->Target);
			return true;
		}

		if (HitResult->GetFirstBrush())
		{
			Selection->Select(HitResult->GetFirstBrush()->Target);
			return true;
		}
	}
	
	Selection->DeselectAll();
	return true;
}

bool FUnrealBroomEdMode::StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport)
{
	UE_LOG(LogUnrealBroom, Warning, TEXT("StartTracking"));
	return true;
}

bool FUnrealBroomEdMode::EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport)
{
	UE_LOG(LogUnrealBroom, Warning, TEXT("EndTracking"));
	return true;
}

bool FUnrealBroomEdMode::InputKey(
	FEditorViewportClient* ViewportClient,
	FViewport* Viewport,
	FKey Key,
	EInputEvent Event)
{
	UE_LOG(LogUnrealBroom, Warning, TEXT("InputKey: %s"), *Key.ToString());
	return FEdMode::InputKey(ViewportClient, Viewport, Key, Event);
}

bool FUnrealBroomEdMode::DisallowMouseDeltaTracking() const
{
	return false;
}

TOptional<FUnrealBroomHitResult> FUnrealBroomEdMode::MouseTrace(FEditorViewportClient* ViewportClient)
{
	FSceneViewFamilyContext ViewFamily(
		FSceneViewFamilyContext::ConstructionValues(
			ViewportClient->Viewport,
			ViewportClient->GetScene(),
			ViewportClient->EngineShowFlags
		).SetRealtimeUpdate(ViewportClient->IsRealtime())
	);
	FSceneView* View = ViewportClient->CalcSceneView(&ViewFamily);
	FViewportCursorLocation MouseRay(
		View,
		ViewportClient,
		ViewportClient->Viewport->GetMouseX(),
		ViewportClient->Viewport->GetMouseY()
	);

	FVector Start = MouseRay.GetOrigin();
	FVector End = Start + MouseRay.GetDirection() * WORLD_MAX;
	if (ViewportClient->IsOrtho())
	{
		Start -= MouseRay.GetDirection() * WORLD_MAX;
	}

	FUnrealBroomHitResult Result;
	if (auto Hit = WorldData->Entity->IntersectsLine(Start, End, Result))
	{
		return Result;
	}

	return TOptional<FUnrealBroomHitResult>();
}
