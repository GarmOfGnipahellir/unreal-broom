#include "Misc/AutomationTest.h"
#include "Model/UnrealBroomBrush.h"

DEFINE_SPEC(
	FUnrealBroomBrushSpec,
	"UnrealBroom.Brush",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask
)

void FUnrealBroomBrushSpec::Define()
{
	Describe(
		"IntersectsLine",
		[this]
		{
			It(
				"should return SET optional when line goes through brush",
				[this]
				{
					UUnrealBroomBrush* Brush = UUnrealBroomBrush::CreateBox(
						FVector::ZeroVector,
						FVector::OneVector * 50.0
					);
					FUnrealBroomHitResult Result;
					TestTrue(
						"IntersectsLine",
						Brush->IntersectsLine(FVector(-100.0, 0.0, 0.0), FVector(100.0, 0.0, 0.0), Result).IsSet()
					);
				}
			);

			It(
				"should return UNSET optional when line goes outside brush",
				[this]
				{
					UUnrealBroomBrush* Brush = UUnrealBroomBrush::CreateBox(
						FVector::ZeroVector,
						FVector::OneVector * 50.0
					);
					FUnrealBroomHitResult Result;
					TestFalse(
						"IntersectsLine",
						Brush->IntersectsLine(FVector(-100.0, 0.0, 100.0), FVector(100.0, 0.0, 100.0), Result).IsSet()
					);
				}
			);
		}
	);
}
