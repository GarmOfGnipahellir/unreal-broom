// Copyright Arctic Beard Studios. All Rights Reserved.


#include "Model/Poly.h"

#include "DynamicMesh/DynamicMesh3.h"
#include "Model/Face.h"

void FPoly::CreateVert(const FVector Location, const FFace Face)
{
	FVert Vert;
	Vert.Location = Location;
	Vert.Normal = Face.Normal;
	Verts.Add(Vert);
}

void FPoly::OrderVerts()
{
	if (Verts.Num() < 3)
	{
		return;
	}

	FVector Center = FVector::ZeroVector;
	for (const auto Vert : Verts)
	{
		Center += Vert.Location;
	}
	Center /= Verts.Num();

	for (int n = 0; n < Verts.Num() - 2; ++n)
	{
		FVector a = Verts[n].Location - Center;
		a.Normalize();
		FVector p = Normal.Cross(a);

		double SmallestAngle = -1.0;
		int Smallest = -1;

		for (int m = n + 1; m < Verts.Num(); ++m)
		{
			FVector b = Verts[m].Location - Center;
			b.Normalize();

			if (p.Dot(b) > 0.0)
			{
				const double Angle = a.Dot(b);
				if (Angle > SmallestAngle)
				{
					SmallestAngle = Angle;
					Smallest = m;
				}
			}
		}

		Verts.Swap(n + 1, Smallest);
	}
}
