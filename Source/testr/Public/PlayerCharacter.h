// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
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
	UCharacterMovementComponent* movementComponent;

	UFUNCTION()
	void Forward(float input);
	UFUNCTION()
	void Right(float input);
	UFUNCTION()
	void LookUp(float input);
	UFUNCTION()
	void LookRight(float input);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
