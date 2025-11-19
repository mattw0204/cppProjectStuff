
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
	UPROPERTY()
	FText name;
	UPROPERTY(EditAnywhere)
	EItemTypes itemType;
	UPROPERTY()
	UStaticMesh* mesh;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* image;

	
};