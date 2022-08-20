// Copyright Arctic Beard Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FBrush;

class FEntity
{
public:
	TArray<TSharedRef<FBrush>> Brushes;
};
