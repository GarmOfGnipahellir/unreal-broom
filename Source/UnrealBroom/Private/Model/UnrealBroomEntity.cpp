// Copyright Arctic Beard Studios. All Rights Reserved.


#include "Model/UnrealBroomEntity.h"

#include "DynamicMesh/DynamicMesh3.h"
#include "Model/UnrealBroomBrush.h"
#include "Model/UnrealBroomPoly.h"

void UUnrealBroomEntity::AddBrush(UUnrealBroomBrush* Brush)
{
	Brush->Entity = this;
	Brushes.Add(Brush);
}

UE::Geometry::FDynamicMesh3 UUnrealBroomEntity::GetDynamicMesh()
{
	UE::Geometry::FDynamicMesh3 Result = UE::Geometry::FDynamicMesh3(true, false, false, false);

	for (int i = 0; i < Brushes.Num(); ++i)
	{
		TArray<FUnrealBroomPoly> Polys = Brushes[i]->GetPolys();
		for (int j = 0; j < Polys.Num(); ++j)
		{
			FUnrealBroomPoly Poly = Polys[j];

			TArray<int> VertIDs;
			VertIDs.Reserve(Poly.Verts.Num());
			for (auto Vert : Poly.Verts)
			{
				VertIDs.Add(Result.AppendVertex(UE::Geometry::FVertexInfo(Vert.Location, FVector3f(Vert.Normal))));
			}

			for (int k = 2; k < VertIDs.Num(); ++k)
			{
				Result.AppendTriangle(VertIDs[k], VertIDs[k - 1], VertIDs[0]);
			}
		}
	}

	return Result;
}

TOptional<FUnrealBroomHitEntity> UUnrealBroomEntity::IntersectsLine(
	FVector Start,
	FVector End,
	FUnrealBroomHitResult& Result)
{
	TArray<FUnrealBroomHitEntity> HitsEntity;
	for (const auto Brush : Brushes)
	{
		if (TOptional<FUnrealBroomHitFace> HitBrush = Brush->IntersectsLine(Start, End, Result))
		{
			HitsEntity.Add(FUnrealBroomHitEntity(*HitBrush, this));
		}
	}

	if (!HitsEntity.IsEmpty())
	{
		HitsEntity.Sort();
		Result.HitEntities.Add(HitsEntity[0]);
		return HitsEntity[0];
	}

	return TOptional<FUnrealBroomHitEntity>();
}
