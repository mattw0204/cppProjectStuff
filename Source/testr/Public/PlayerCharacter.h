// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "MyUserWidget.h"
#include "Interactable.h"
#include "Item.h"
#include "MyPlayerController.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TESTR_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	UPROPERTY()
	UCameraComponent* camera;
	UPROPERTY()
	AMyPlayerController* myController;
	UPROPERTY()
	UCharacterMovementComponent* movementComponent;
	UPROPERTY()
	TSubclassOf<UMyUserWidget> widgetRef;
	UPROPERTY()
	UMyUserWidget* WidgetPointer;
	UPROPERTY()
	bool shouldRaycast;
	UPROPERTY()
	float interactRange = 200;
	UPROPERTY()
	UClass* interactableRef;
	UPROPERTY()
	AInteractable* interactable;

	UPROPERTY()
	TArray<FItem> inventory;

	UFUNCTION()
	void Raycast();
	UFUNCTION()
	void Forward(float input);
	UFUNCTION()
	void Right(float input);
	UFUNCTION()
	void LookUp(float input);
	UFUNCTION()
	void LookRight(float input);
	UFUNCTION()
	void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
