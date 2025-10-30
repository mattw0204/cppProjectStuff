// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));

}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATree::OnConstruction(const FTransform &Transform)
{
	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
	switch (treeType)
	{
	case ETreeType::Conicle:
		//mesh->SetStaticMesh(static ConstructorHelpers::FObjectFinder<UStaticMesh> MyMesh(TEXT("StaticMesh'/Game/ThirdPerson/Meshes/CubeMesh.CubeMesh'"));)
		break;
	case ETreeType::Branched:
		break;
	case ETreeType::Columnar:
		break;
	}
}

