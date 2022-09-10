// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Model/UnrealBroomFace.h"
#include "Model/UnrealBroomBrush.h"
#include "Model/UnrealBroomEntity.h"

#define GET_FIRST_IMPL(Elem, Elems) \
	TOptional<FUnrealBroomHit##Elem> GetFirst##Elem() \
	{ \
		if (Hit##Elems.IsEmpty()) return TOptional<FUnrealBroomHit##Elem>(); \
		return Hit##Elems[0]; \
	}
#define GET_LAST_IMPL(Elem, Elems) \
	TOptional<FUnrealBroomHit##Elem> GetLast##Elem() \
	{ \
		if (Hit##Elems.IsEmpty()) return TOptional<FUnrealBroomHit##Elem>(); \
		return Hit##Elems[Hit##Elems.Num() - 1]; \
	}
#define SORT_IMPL(Elems) \
	void Sort##Elems() \
	{ \
		Hit##Elems.Sort(); \
	}

template <typename T>
struct TUnrealBroomHit
{
	double Time;
	FVector Point;
	T* Target;

	explicit TUnrealBroomHit(const double Time, const FVector Point, T* Target) : Time(Time), Point(Point),
		Target(Target)
	{
	}

	template <typename F>
	explicit TUnrealBroomHit(TUnrealBroomHit<F> Other, T* Target) : Time(Other.Time), Point(Other.Point),
	                                                                Target(Target)
	{
	}

	friend bool operator<(const TUnrealBroomHit<T>& Lhs, const TUnrealBroomHit<T>& Rhs)
	{
		return Lhs.Time < Rhs.Time;
	}

	T* operator->() { return &Target; }
	const T* operator->() const { return &Target; }

	T& operator*() { return Target; }
	const T& operator*() const { return Target; }
};

typedef TUnrealBroomHit<UUnrealBroomFace> FUnrealBroomHitFace;
typedef TUnrealBroomHit<UUnrealBroomBrush> FUnrealBroomHitBrush;
typedef TUnrealBroomHit<UUnrealBroomEntity> FUnrealBroomHitEntity;

// TODO: maybe make hits hierarchical Entity -> Brush -> Face

struct FUnrealBroomHitResult
{
	TArray<FUnrealBroomHitFace> HitFaces;
	TArray<FUnrealBroomHitBrush> HitBrushes;
	TArray<FUnrealBroomHitEntity> HitEntities;

	GET_FIRST_IMPL(Face, Faces)
	GET_FIRST_IMPL(Brush, Brushes)
	GET_FIRST_IMPL(Entity, Entities)

	GET_LAST_IMPL(Face, Faces)
	GET_LAST_IMPL(Brush, Brushes)
	GET_LAST_IMPL(Entity, Entities)

	SORT_IMPL(Faces);
	SORT_IMPL(Brushes);
	SORT_IMPL(Entities);
};
