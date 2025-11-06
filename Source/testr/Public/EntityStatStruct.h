
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EntityStatStruct.generated.h"

USTRUCT(BlueprintType)
struct FEntityStatStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;
};