#include "Misc/AutomationTest.h"
#include "Model/UnrealBroomBrush.h"
#include "Model/UnrealBroomEntity.h"

DEFINE_SPEC(
	FUnrealBroomEntitySpec,
	"UnrealBroom.Entity",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask
)

void FUnrealBroomEntitySpec::Define()
{
	Describe(
		"IntersectsLine",
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
				}
			);
		}
	);
}
