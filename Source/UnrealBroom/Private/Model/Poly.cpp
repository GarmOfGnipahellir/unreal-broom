// Copyright Arctic Beard Studios. All Rights Reserved.


#include "Model/Poly.h"

#include "Model/Face.h"

void FPoly::CreateVert(const FVector Location, const FFace Face)
{
	FVert Vert;
	Vert.Location = Location;
	Verts.Add(Vert);
}

TOptional<TArray<FPoly::FVert>> FPoly::GetOrderedVerts() const
{
	if (Verts.Num() < 3)
	{
		return TOptional<TArray<FVert>>();
	}

	FVector Center = FVector::ZeroVector;
	for (const auto Vert : Verts)
	{
		Center += Vert.Location;
	}
	Center /= Verts.Num();

	TArray<FVert> Result = Verts;
	for (int n = 0; n < Result.Num() - 2; ++n)
	{
		FVector a = Result[n].Location - Center;
		a.Normalize();
		FVector p = Normal.Cross(a);

		double SmallestAngle = -1.0;
		int Smallest = -1;

		for (int m = n + 1; m < Result.Num(); ++m)
		{
			FVector b = Result[m].Location - Center;
			b.Normalize();

			if (p.Dot(b) > 0.0)
			{
				double Angle = a.Dot(b);
				if (Angle > SmallestAngle)
				{
					SmallestAngle = Angle;
					Smallest = m;
				}
			}
		}

		Result.Swap(n + 1, Smallest);
	}

	return TOptional(Result);
}
