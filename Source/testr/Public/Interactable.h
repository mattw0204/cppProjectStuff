// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Interactable.generated.h"

UCLASS()
class TESTR_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh;
	UPROPERTY()
	USceneCaptureComponent2D* sceneCaptureComponent;
	UPROPERTY()
	bool hasImage = false;
	UPROPERTY()
	UTextureRenderTarget2D* rt;
	UPROPERTY()
	UTexture2D* image; 
	UFUNCTION()
	void GenerateImage();
	UFUNCTION()
	void CreateTexture();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
