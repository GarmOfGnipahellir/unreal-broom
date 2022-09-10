#include "Misc/AutomationTest.h"
#include "Model/UnrealBroomBrush.h"
#include "Model/UnrealBroomEntity.h"

DEFINE_SPEC(
	FUnrealBroomHitResultSpec,
	"UnrealBroom.HitResult",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask
)

void FUnrealBroomHitResultSpec::Define()
{
	Describe(
		"GetFirst",
		[this]
		{
			It(
				"should return closest brush when hitting multiple brushes",
				[this]
				{
					UUnrealBroomBrush* Brush1 = UUnrealBroomBrush::CreateBox(
						FVector::ZeroVector,
						FVector::OneVector * 50.0
					);
					UUnrealBroomBrush* Brush2 = UUnrealBroomBrush::CreateBox(
						FVector::XAxisVector * 150.0,
						FVector::OneVector * 50.0
					);
					UUnrealBroomEntity* Entity = NewObject<UUnrealBroomEntity>();
					Entity->Brushes.Add(Brush1);
					Entity->Brushes.Add(Brush2);

					FUnrealBroomHitResult Result;
					Entity->IntersectsLine(
						FVector::XAxisVector * -100.0,
						FVector::XAxisVector * 500.0,
						Result
					);

					TestTrue("Hits a brush", Result.GetFirstBrush().IsSet());
					TestEqual("The first brush is actually first", Result.GetFirstBrush()->Target, Brush1);
				}
			);
		}
	);
}
