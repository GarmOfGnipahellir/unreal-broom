#include "Misc/AutomationTest.h"
#include "Model/UnrealBroomFace.h"

DEFINE_SPEC(
	FUnrealBroomFaceSpec,
	"UnrealBroom.Face",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask
)

void FUnrealBroomFaceSpec::Define()
{
	Describe(
		"IntersectsLine",
		[this]
		{
			It(
				"should return SET optional when line is NOT parallel to face",
				[this]
				{
					UUnrealBroomFace* Face = UUnrealBroomFace::Create(FVector::ZeroVector, FVector::XAxisVector);
					FUnrealBroomHitResult Result;
					TestTrue(
						"IntersectsLine",
						Face->IntersectsLine(FVector(-100.0, 0.0, 0.0), FVector(100.0, 0.0, 0.0), Result).IsSet()
					);
				}
			);

			It(
				"should return UNSET optional when line is parallel to face",
				[this]
				{
					UUnrealBroomFace* Face = UUnrealBroomFace::Create(FVector::ZeroVector, FVector::XAxisVector);
					FUnrealBroomHitResult Result;
					TestFalse(
						"IntersectsLine",
						Face->IntersectsLine(FVector(-100.0, 0.0, -100.0), FVector(-100.0, 0.0, 100.0), Result).IsSet()
					);
				}
			);
		}
	);
}
