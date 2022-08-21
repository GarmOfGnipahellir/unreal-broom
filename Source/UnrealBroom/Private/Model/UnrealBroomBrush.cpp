// Copyright Arctic Beard Studios. All Rights Reserved.


#include "Model/UnrealBroomBrush.h"

#include "DynamicMesh/DynamicMesh3.h"
#include "Model/UnrealBroomFace.h"
#include "Model/UnrealBroomPoly.h"

UUnrealBroomBrush* UUnrealBroomBrush::CreateBox(const FVector Location, const FVector Extent)
{
	UUnrealBroomBrush* Result = NewObject<UUnrealBroomBrush>();
	Result->Faces.Add(UUnrealBroomFace::Create(Location + FVector::XAxisVector * Extent.X, FVector::XAxisVector));
	Result->Faces.Add(UUnrealBroomFace::Create(Location - FVector::XAxisVector * Extent.X, -FVector::XAxisVector));
	Result->Faces.Add(UUnrealBroomFace::Create(Location + FVector::YAxisVector * Extent.Y, FVector::YAxisVector));
	Result->Faces.Add(UUnrealBroomFace::Create(Location - FVector::YAxisVector * Extent.Y, -FVector::YAxisVector));
	Result->Faces.Add(UUnrealBroomFace::Create(Location + FVector::ZAxisVector * Extent.Z, FVector::ZAxisVector));
	Result->Faces.Add(UUnrealBroomFace::Create(Location - FVector::ZAxisVector * Extent.Z, -FVector::ZAxisVector));
	return Result;
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

bool UUnrealBroomBrush::IntersectsLine(FVector Start, FVector End) const
{
	for (const auto Face : Faces)
	{
		if (FVector Point; Face->IntersectsLine(Start, End, Point) && ContainsPoint(Point))
		{
			return true;
		}
	}
	return false;
}
