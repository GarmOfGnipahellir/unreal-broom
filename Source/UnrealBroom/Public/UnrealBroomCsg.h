#pragma once


namespace UnrealBroom::Csg
{
	struct FPolygon;
	struct FNode;

	struct FBrush
	{
		TArray<FPolygon> Polygons;

		explicit FBrush() {}
		explicit FBrush(const TArray<FPolygon>& InPolygons): Polygons(InPolygons) {}

		FBrush Union(const FBrush& InOther) const;
		// FBrush Subtract(const FBrush& InOther) const;
		// FBrush Intersect(const FBrush& InOther) const;
	};

	struct FVertex
	{
		FVector Position;
		FVector Normal;

		explicit FVertex(const FVector& InPosition, const FVector& InNormal) : Position(InPosition), Normal(InNormal) {}

		FVertex Interpolate(const FVertex& InOther, double InAlpha) const;

		void Flip();
	};

	enum EPolygonType : uint8
	{
		CoPlanar = 0,
		Front = 1,
		Back = 2,
		Spanning = 3,
	};

	struct FPolygon
	{
		TArray<FVertex> Vertices;
		FPlane Plane;

		explicit FPolygon(const TArray<FVertex>& InVertices);

		void Split(
			const FPlane& InPlane,
			TArray<FPolygon>& OutCoplanarFront,
			TArray<FPolygon>& OutCoplanarBack,
			TArray<FPolygon>& OutFront,
			TArray<FPolygon>& OutBack
		) const;

		void Flip();
	};

	struct FNode
	{
		TOptional<FPlane> Plane;
		TSharedPtr<FNode> Front;
		TSharedPtr<FNode> Back;
		TArray<FPolygon> Polygons;

		explicit FNode() {}
		explicit FNode(const TArray<FPolygon>& InPolygons);

		TArray<FPolygon> AllPolygons() const;

		void Invert();
		TArray<FPolygon> ClipPolygons(const TArray<FPolygon>& InPolygons);
		void ClipTo(FNode& InBsp);
		void Build(const TArray<FPolygon>& InPolygons);
	};
}
