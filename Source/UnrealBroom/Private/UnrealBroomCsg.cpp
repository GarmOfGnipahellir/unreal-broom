#include "UnrealBroomCsg.h"

namespace UnrealBroom::Csg
{
	FBrush FBrush::Union(const FBrush& InOther) const
	{
		FNode A(Polygons);
		FNode B(InOther.Polygons);

		A.ClipTo(B);
		B.ClipTo(A);
		B.Invert();
		B.ClipTo(A);
		B.Invert();
		A.Build(B.Polygons);

		return FBrush(A.Polygons);
	}
}

namespace UnrealBroom::Csg
{
	FVertex FVertex::Interpolate(const FVertex& InOther, const double InAlpha) const
	{
		return FVertex(
			FMath::Lerp(Position, InOther.Position, InAlpha),
			FMath::Lerp(Normal, InOther.Normal, InAlpha).GetSafeNormal()
		);
	}

	void FVertex::Flip()
	{
		Normal = -Normal;
	}
}

namespace UnrealBroom::Csg
{
	FPolygon::FPolygon(const TArray<FVertex>& InVertices) : Vertices(InVertices)
	{
		Plane = FPlane(InVertices[0].Position, InVertices[1].Position, InVertices[2].Position);
	}

	void FPolygon::Split(
		const FPlane& InPlane,
		TArray<FPolygon>& OutCoplanarFront,
		TArray<FPolygon>& OutCoplanarBack,
		TArray<FPolygon>& OutFront,
		TArray<FPolygon>& OutBack
	) const
	{
		EPolygonType FinalType = CoPlanar;

		TArray<EPolygonType> Types;
		for (const auto& Vertex : Vertices)
		{
			const auto T = InPlane.GetNormal() | Vertex.Position - InPlane.W;
			EPolygonType Type = (T < -KINDA_SMALL_NUMBER) ? Back : (T > KINDA_SMALL_NUMBER) ? Front : CoPlanar;
			FinalType = static_cast<EPolygonType>(static_cast<uint8>(FinalType) | static_cast<uint8>(Type));
			Types.Add(Type);
		}

		switch (FinalType)
		{
		case CoPlanar:
			((InPlane.GetNormal() | Plane.GetNormal()) > 0 ? OutCoplanarFront : OutCoplanarBack).Add(*this);
			break;
		case Front:
			OutFront.Add(*this);
			break;
		case Back:
			OutBack.Add(*this);
			break;
		case Spanning:
			TArray<FVertex> FrontVerts, BackVerts;
			for (int i = 0; i < Vertices.Num(); ++i)
			{
				const int j = (i + 1) % Vertices.Num();
				const auto ti = Types[i];
				const auto tj = Types[j];
				auto& vi = Vertices[i];
				auto& vj = Vertices[j];

				if (ti != Back) FrontVerts.Add(vi);
				if (ti != Front) BackVerts.Add(vi);

				if (static_cast<EPolygonType>(static_cast<uint8>(ti) | static_cast<uint8>(tj)) == Spanning)
				{
					const auto Alpha = (InPlane.W - (InPlane.GetNormal() | vi.Position)) /
						(InPlane.GetNormal() | (vj.Position - vi.Position));
					const auto Vert = vi.Interpolate(vj, Alpha);
					FrontVerts.Add(Vert);
					BackVerts.Add(Vert);
				}
			}
			if (FrontVerts.Num() >= 3) OutFront.Add(FPolygon(FrontVerts));
			if (BackVerts.Num() >= 3) OutBack.Add(FPolygon(BackVerts));
			break;
		}
	}

	void FPolygon::Flip()
	{
		for (auto& Vertex : Vertices)
		{
			Vertex.Flip();
		}
		Plane = Plane.Flip();
	}
}

namespace UnrealBroom::Csg
{
	FNode::FNode(const TArray<FPolygon>& InPolygons)
	{
		Build(InPolygons);
	}

	TArray<FPolygon> FNode::AllPolygons() const
	{
		TArray<FPolygon> Result;
		Result.Append(Polygons);
		if (Front) Result.Append(Front->AllPolygons());
		if (Back) Result.Append(Back->AllPolygons());
		return Result;
	}

	void FNode::Invert()
	{
		for (auto& Polygon : Polygons)
		{
			Polygon.Flip();
		}
		Plane = Plane->Flip();
		if (Front) Front->Invert();
		if (Back) Back->Invert();
		const auto Temp = Front;
		Front = Back;
		Back = Temp;
	}

	TArray<FPolygon> FNode::ClipPolygons(const TArray<FPolygon>& InPolygons)
	{
		if (!Plane) return InPolygons;

		TArray<FPolygon> FrontPolys, BackPolys;
		for (auto& Polygon : InPolygons)
		{
			Polygon.Split(*Plane, FrontPolys, BackPolys, FrontPolys, BackPolys);
		}

		if (Front) FrontPolys = Front->ClipPolygons(FrontPolys);

		if (Back) BackPolys = Back->ClipPolygons(BackPolys);
		else BackPolys.Empty();

		FrontPolys.Append(BackPolys);
		return FrontPolys;
	}

	void FNode::ClipTo(FNode& InBsp)
	{
		Polygons = InBsp.ClipPolygons(Polygons);
		if (Front) Front->ClipTo(InBsp);
		if (Back) Back->ClipTo(InBsp);
	}

	void FNode::Build(const TArray<FPolygon>& InPolygons)
	{
		if (InPolygons.IsEmpty()) return;

		if (!Plane) Plane = Polygons[0].Plane;

		TArray<FPolygon> FrontPolys, BackPolys;
		for (auto& Polygon : InPolygons)
		{
			Polygon.Split(*Plane, Polygons, Polygons, FrontPolys, BackPolys);
		}

		if (!FrontPolys.IsEmpty())
		{
			if (!Front) Front = MakeShared<FNode>();
			Front->Build(FrontPolys);
		}

		if (!BackPolys.IsEmpty())
		{
			if (!Back) Back = MakeShared<FNode>();
			Back->Build(BackPolys);
		}
	}
}
