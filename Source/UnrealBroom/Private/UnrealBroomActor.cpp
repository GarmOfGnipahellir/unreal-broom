// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealBroomActor.h"

#include "StaticMeshAttributes.h"
#include "PhysicsEngine/BodySetup.h"
#include "PhysicsEngine/ConvexElem.h"

FUnrealBroomFace::FUnrealBroomFace() : Plane() {}

FUnrealBroomFace::FUnrealBroomFace(const FPlane& InPlane) : Plane(InPlane) {}

FUnrealBroomBrush::FUnrealBroomBrush() {}

FUnrealBroomBrush::FUnrealBroomBrush(const FBox& InBox) : Faces(
	{
		FUnrealBroomFace(FPlane(FVector::UnitX(), InBox.Max.X)),
		FUnrealBroomFace(FPlane(-FVector::UnitX(), -InBox.Min.X)),
		FUnrealBroomFace(FPlane(FVector::UnitY(), InBox.Max.Y)),
		FUnrealBroomFace(FPlane(-FVector::UnitY(), -InBox.Min.Y)),
		FUnrealBroomFace(FPlane(FVector::UnitZ(), InBox.Max.Z)),
		FUnrealBroomFace(FPlane(-FVector::UnitZ(), -InBox.Min.Z)),
	}
) {}

void FUnrealBroomBrush::BuildMesh(FMeshDescription* Desc) const
{
	FStaticMeshAttributes Attributes(*Desc);
	const TVertexAttributesRef<FVector3f> VertexPositions = Attributes.GetVertexPositions();

	FPolygonGroupID PolyGroupID = Desc->CreatePolygonGroup();
	TArray<TArray<FVector>> FacesVertexPositions;
	FacesVertexPositions.SetNumZeroed(Faces.Num());
	for (int i = 0; i < Faces.Num(); ++i)
	{
		for (int j = i + 1; j < Faces.Num(); ++j)
		{
			for (int k = j + 1; k < Faces.Num(); ++k)
			{
				FVector IntersectPosition;
				if (!FMath::IntersectPlanes3(IntersectPosition, Faces[i].Plane, Faces[j].Plane, Faces[k].Plane))
				{
					continue;
				}

				bool bInHull = true;
				for (auto& Face : Faces)
				{
					if ((Face.Plane.GetNormal() | IntersectPosition) > Face.Plane.W + UE_KINDA_SMALL_NUMBER)
					{
						bInHull = false;
						break;
					}
				}
				if (!bInHull)
				{
					continue;
				}

				for (int Idx : {i, j, k})
				{
					TArray<FVector>& FaceVertexPositions = FacesVertexPositions[Idx];
					bool bIsUnique = true;
					for (auto& VertexPosition : FaceVertexPositions)
					{
						if ((VertexPosition - IntersectPosition).SquaredLength() <
							UE_KINDA_SMALL_NUMBER * UE_KINDA_SMALL_NUMBER)
						{
							bIsUnique = false;
							break;
						}
					}
					if (!bIsUnique)
					{
						continue;
					}
					FaceVertexPositions.Add(IntersectPosition);
				}
			}
		}
	}

	for (int Idx = 0; Idx < FacesVertexPositions.Num(); ++Idx)
	{
		TArray<FVector> Positions = FacesVertexPositions[Idx];

		if (Positions.Num() < 3)
		{
			continue;
		}

		struct FPredicate
		{
			const FUnrealBroomFace& Face;
			FVector Center;

			bool operator()(const FVector& A, const FVector& B) const
			{
				FVector DA = A - Center;
				FVector DB = B - Center;
				return ((Face.Plane.GetNormal() ^ DA) | DB) < 0;
			}
		};

		FVector Center;
		for (const auto& Position : Positions)
		{
			Center += Position;
		}
		Center /= Positions.Num();
		Positions.Sort(FPredicate(Faces[Idx], Center));

		TArray<FVertexInstanceID> VertexInstanceIds;
		VertexInstanceIds.Reserve(Positions.Num());
		for (const auto& Position : Positions)
		{
			const FVertexID VertexID = Desc->CreateVertex();
			VertexPositions[VertexID] = FVector3f(Position);
			const FVertexInstanceID VertexInstanceID = Desc->CreateVertexInstance(VertexID);
			// TODO: Add normal & UVs
			VertexInstanceIds.Add(VertexInstanceID);
		}

		Desc->CreatePolygon(PolyGroupID, VertexInstanceIds);
	}
}

AUnrealBroomActor::AUnrealBroomActor()
{
	MyRootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = MyRootComponent;
}

void AUnrealBroomActor::AddBrush(const FUnrealBroomBrush& InBrush)
{
	const int32 Index = Brushes.Add(InBrush);

	UStaticMeshComponent* NewMeshComponent = Cast<UStaticMeshComponent>(
		AddComponentByClass(UStaticMeshComponent::StaticClass(), false, FTransform::Identity, false)
	);
	AddInstanceComponent(NewMeshComponent);
	MeshComponents.Insert(NewMeshComponent, Index);

	UStaticMesh* Mesh = NewObject<UStaticMesh>(NewMeshComponent);
	Mesh->AddSourceModel();
	FMeshDescription* Desc = Mesh->CreateMeshDescription(0);
	InBrush.BuildMesh(Desc);
	Mesh->CommitMeshDescription(0);

	TArray<FPlane> Planes;
	Planes.Reserve(InBrush.Faces.Num());
	for (auto& Face : InBrush.Faces)
	{
		Planes.Add(Face.Plane);
	}
	FKConvexElem ConvexElem;
	ConvexElem.HullFromPlanes(Planes, {});
	Mesh->CreateBodySetup();
	Mesh->GetBodySetup()->AggGeom.ConvexElems.Add(ConvexElem);

	Mesh->Build(false);

	NewMeshComponent->SetStaticMesh(Mesh);
}
