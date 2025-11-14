
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemTypes.h"
#include "Engine/StaticMesh.h"
#include "Item.generated.h"

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_BODY()
public:
	FText name;
	UPROPERTY(EditAnywhere)
	EItemTypes itemType;
	UStaticMesh* mesh;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> image;
};