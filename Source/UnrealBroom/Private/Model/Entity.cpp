// Copyright Arctic Beard Studios. All Rights Reserved.


#include "Model/Entity.h"

#include "DynamicMesh/DynamicMesh3.h"
#include "Model/Brush.h"
#include "Model/Poly.h"

UE::Geometry::FDynamicMesh3 FEntity::GetDynamicMesh()
{
	UE::Geometry::FDynamicMesh3 Result = UE::Geometry::FDynamicMesh3(true, false, false, false);

	for (int i = 0; i < Brushes.Num(); ++i)
	{
		TArray<FPoly> Polys = Brushes[i]->GetPolys();
		for (int j = 0; j < Polys.Num(); ++j)
		{
			FPoly Poly = Polys[j];

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
