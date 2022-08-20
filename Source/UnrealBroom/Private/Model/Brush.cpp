// Copyright Arctic Beard Studios. All Rights Reserved.


#include "Model/Brush.h"

#include "UnrealBroomModule.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "Model/Face.h"
#include "Model/Poly.h"

FBrush* FBrush::CreateBox(const FVector Location, const FVector Extent)
{
	FBrush* Result = new FBrush;
	Result->Faces.Add(MakeShareable(new FFace(Location + FVector::XAxisVector * Extent.X, FVector::XAxisVector)));
	Result->Faces.Add(MakeShareable(new FFace(Location - FVector::XAxisVector * Extent.X, -FVector::XAxisVector)));
	Result->Faces.Add(MakeShareable(new FFace(Location + FVector::YAxisVector * Extent.Y, FVector::YAxisVector)));
	Result->Faces.Add(MakeShareable(new FFace(Location - FVector::YAxisVector * Extent.Y, -FVector::YAxisVector)));
	Result->Faces.Add(MakeShareable(new FFace(Location + FVector::ZAxisVector * Extent.Z, FVector::ZAxisVector)));
	Result->Faces.Add(MakeShareable(new FFace(Location - FVector::ZAxisVector * Extent.Z, -FVector::ZAxisVector)));
	return Result;
}

TArray<FPoly> FBrush::GetPolys()
{
	TArray<FPoly> Result;
	Result.Reserve(Faces.Num());
	for (const auto Face : Faces)
	{
		Result.Add(FPoly(Face->Normal, 0));
	}

	for (int i = 0; i < Result.Num(); ++i)
	{
		for (int j = 0; j < Result.Num(); ++j)
		{
			for (int k = 0; k < Result.Num(); ++k)
			{
				TOptional<FVector> Point = FFace::IntersectPoint(*Faces[i], *Faces[j], *Faces[k]);
				if (!Point) continue;

				// All verts must lie on a face's plane or behind it
				bool bContained = true;
				for (const auto Face : Faces)
				{
					if (Face->Normal.Dot(*Point - Face->Location) > 0.0)
					{
						bContained = false;
					}
				}
				if (!bContained) continue;

				Result[i].CreateVert(*Point, *Faces[i]);
				Result[j].CreateVert(*Point, *Faces[j]);
				Result[k].CreateVert(*Point, *Faces[k]);
			}
		}
	}

	for (int i = 0; i < Result.Num(); ++i)
	{
		Result[i].OrderVerts();
	}

	return Result;
}
