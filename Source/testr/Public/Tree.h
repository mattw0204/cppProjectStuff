// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tree.generated.h"

UENUM(BlueprintType)
enum class ETreeType : uint8
{
	Conicle UMETA(DisplayName = "Conicle"),
	Branched UMETA(DisplayName = "Branched"),
	Columnar UMETA(DisplayName = "Columnar")
};

UCLASS()
class TESTR_API ATree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATree();

	UPROPERTY(EditAnywhere)
	ETreeType treeType;

	UPROPERTY()
	UStaticMeshComponent* mesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform &Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
