// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealBroomBrush.h"

using UnrealBroom::Csg::FPolygon;
using UnrealBroom::Csg::FVertex;

UUnrealBroomBrush* UUnrealBroomBrush::Cuboid(const FVector& Center, const FVector& Extent)
{
	TArray InfoArray = {
		TTuple<TArray<int>, FVector>(TArray{0, 4, 6, 2}, FVector(-1, 0, 0)),
		TTuple<TArray<int>, FVector>(TArray{1, 3, 7, 5}, FVector(1, 0, 0)),
		TTuple<TArray<int>, FVector>(TArray{0, 1, 5, 4}, FVector(0, -1, 0)),
		TTuple<TArray<int>, FVector>(TArray{2, 6, 7, 3}, FVector(0, 1, 0)),
		TTuple<TArray<int>, FVector>(TArray{0, 2, 3, 1}, FVector(0, 0, -1)),
		TTuple<TArray<int>, FVector>(TArray{4, 5, 7, 6}, FVector(0, 0, 1)),
	};

	TArray<FPolygon> Polygons;
	for (auto& [Indices, Normal] : InfoArray)
	{
		TArray<FVertex> Vertices;
		for (const auto Index : Indices)
		{
			FVector Position = Center + Extent * FVector(
				2 * ((Index & 1) > 0 ? 0 : 1) - 1,
				2 * ((Index & 2) > 0 ? 0 : 1) - 1,
				2 * ((Index & 4) > 0 ? 0 : 1) - 1
			);
			Vertices.Add(FVertex(Position, Normal));
		}
		Polygons.Add(FPolygon(Vertices));
	}

	UUnrealBroomBrush* Result = NewObject<UUnrealBroomBrush>();
	Result->Brush = FBrush(Polygons);
	return Result;
}

TArray<FUnrealBroomPolygon> UUnrealBroomBrush::GetPolygons() const
{
	TArray<FUnrealBroomPolygon> Result;
	for (auto& Polygon : Brush.Polygons)
	{
		TArray<FVector> Points;
		for (auto& [Position, Normal] : Polygon.Vertices)
		{
			Points.Add(Position);
		}
		Result.Add(FUnrealBroomPolygon{Points, Polygon.Plane});
	}
	return Result;
}
