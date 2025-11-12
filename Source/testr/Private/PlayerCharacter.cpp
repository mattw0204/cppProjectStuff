// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "interactable.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	camera->SetupAttachment(GetCapsuleComponent());
	
	camera->bUsePawnControlRotation = true;
	movementComponent = GetCharacterMovement();
	movementComponent->MaxWalkSpeed = 300;

	interactableRef = AInteractable::StaticClass();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (myWidget != nullptr)
	{
		//myWidget = (UMyUserWidget*)CreateWidget(GetWorld(), widgetRef);
		myWidget->AddToViewport();
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Raycast();
}
void APlayerCharacter::Raycast() {
	if (shouldRaycast) {
		FVector start = camera->GetComponentLocation();
		FVector forward = camera->GetForwardVector();
		FVector end = (start + (forward * interactRange));
		FHitResult outHit;
		TArray<AActor*> ignore;
		ignore.Add(GetOwner());
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1, false, ignore, EDrawDebugTrace::ForOneFrame, OUT outHit, true);
		if (outHit.GetActor() == nullptr)
		{
			return;
		}
		if (outHit.GetActor()->IsA(interactableRef))
		{
			UE_LOG(LogTemp, Warning, TEXT("Activated!"));
		}
	}
	shouldRaycast = false;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::Forward);

	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::Right);

	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);

}
void APlayerCharacter::Forward(float input)
{
	AddMovementInput(GetActorForwardVector(), input);
}
void APlayerCharacter::Right(float input)
{
	AddMovementInput(GetActorRightVector(), input);
}

void APlayerCharacter::LookUp(float input)
{
	AddControllerPitchInput(-input);
	shouldRaycast = true;
}
void APlayerCharacter::LookRight(float input)
{
	AddControllerYawInput(-input);
	shouldRaycast = true;
}
