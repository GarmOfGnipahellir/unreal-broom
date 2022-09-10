// Copyright Arctic Beard Studios. All Rights Reserved.


#include "Model/UnrealBroomBrush.h"

#include "DynamicMesh/DynamicMesh3.h"
#include "Model/UnrealBroomFace.h"
#include "Model/UnrealBroomPoly.h"

UUnrealBroomBrush* UUnrealBroomBrush::CreateBox(const FVector Location, const FVector Extent)
{
	UUnrealBroomBrush* Result = NewObject<UUnrealBroomBrush>();
	Result->AddFace(Location + FVector::XAxisVector * Extent.X, FVector::XAxisVector);
	Result->AddFace(Location - FVector::XAxisVector * Extent.X, -FVector::XAxisVector);
	Result->AddFace(Location + FVector::YAxisVector * Extent.Y, FVector::YAxisVector);
	Result->AddFace(Location - FVector::YAxisVector * Extent.Y, -FVector::YAxisVector);
	Result->AddFace(Location + FVector::ZAxisVector * Extent.Z, FVector::ZAxisVector);
	Result->AddFace(Location - FVector::ZAxisVector * Extent.Z, -FVector::ZAxisVector);
	return Result;
}

void UUnrealBroomBrush::AddFace(const FVector Location, const FVector Normal)
{
	UUnrealBroomFace* NewFace = NewObject<UUnrealBroomFace>(this);
	NewFace->Brush = this;
	NewFace->Location = Location;
	NewFace->Normal = Normal;
	Faces.Add(NewFace);
}

TArray<FUnrealBroomPoly> UUnrealBroomBrush::GetPolys()
{
	TArray<FUnrealBroomPoly> Result;
	Result.Reserve(Faces.Num());
	for (const auto Face : Faces)
	{
		Result.Add(FUnrealBroomPoly(Face->Normal, 0));
	}

	for (int i = 0; i < Result.Num(); ++i)
	{
		for (int j = 0; j < Result.Num(); ++j)
		{
			for (int k = 0; k < Result.Num(); ++k)
			{
				TOptional<FVector> Point = UUnrealBroomFace::IntersectPoint(Faces[i], Faces[j], Faces[k]);
				if (!Point) continue;

				// All verts must lie on a face's plane or behind it
				if (!ContainsPoint(*Point)) continue;

				Result[i].CreateVert(*Point, Faces[i]);
				Result[j].CreateVert(*Point, Faces[j]);
				Result[k].CreateVert(*Point, Faces[k]);
			}
		}
	}

	for (int i = 0; i < Result.Num(); ++i)
	{
		Result[i].OrderVerts();
	}

	return Result;
}

bool UUnrealBroomBrush::ContainsPoint(FVector Point) const
{
	for (const auto Face : Faces)
	{
		if (Face->Normal.Dot(Point - Face->Location) > 0.0)
		{
			return false;
		}
	}
	return true;
}

TOptional<FUnrealBroomHitBrush> UUnrealBroomBrush::IntersectsLine(
	FVector Start,
	FVector End,
	FUnrealBroomHitResult& Result)
{
	TArray<FUnrealBroomHitBrush> HitsBrush;
	for (const auto Face : Faces)
	{
		TOptional<FUnrealBroomHitFace> HitFace = Face->IntersectsLine(Start, End, Result);
		if (HitFace && ContainsPoint(HitFace->Point))
		{
			HitsBrush.Add(FUnrealBroomHitBrush(*HitFace, this));
		}
	}

	if (!HitsBrush.IsEmpty())
	{
		HitsBrush.Sort();
		Result.HitBrushes.Add(HitsBrush[0]);
		return HitsBrush[0];
	}

	return TOptional<FUnrealBroomHitBrush>();
}
