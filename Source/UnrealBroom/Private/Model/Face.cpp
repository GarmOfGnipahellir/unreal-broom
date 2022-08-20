// Copyright Arctic Beard Studios. All Rights Reserved.


#include "Model/Face.h"

#include "MatrixTypes.h"

TOptional<FVector> FFace::IntersectPoint(const FFace Face0, const FFace Face1, const FFace Face2)
{
	FVector n1 = Face0.Normal;
	FVector x1 = Face0.Location;
	FVector x2 = Face1.Location;
	FVector n2 = Face1.Normal;
	FVector x3 = Face2.Location;
	FVector n3 = Face2.Normal;

	UE::Geometry::FMatrix3d Mat = UE::Geometry::FMatrix3d(n1, n2, n3, false);
	double Det = Mat.Determinant();

	if (Det == 0.0)
	{
		return TOptional<FVector>();
	}

	FVector v1 = x1.Dot(n1) * n2.Cross(n3);
	FVector v2 = x2.Dot(n2) * n3.Cross(n1);
	FVector v3 = x3.Dot(n3) * n1.Cross(n2);

	return TOptional(FMath::Pow(Det, -1.0) * (v1 + v2 + v3));
}
