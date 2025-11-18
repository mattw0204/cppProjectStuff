// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "MyUserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interactable.h"
#include "MyPlayerController.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


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
	WidgetPointer = nullptr;
	//widgetRef = (CreateDefaultSubobject<TSubclassOf<UMyUserWidget>>(TEXT("widget")));
	static ConstructorHelpers::FClassFinder<UMyUserWidget> PlayerWidgetClassFinder(TEXT("/Game/WB_HUD.WB_HUD_C"));
	widgetRef = PlayerWidgetClassFinder.Class;
	interactableRef = AInteractable::StaticClass();

	inventory.Init({}, 9);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocallyControlled() && widgetRef)
	{
		myController = (AMyPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
		check(myController);
		WidgetPointer = CreateWidget<UMyUserWidget>(myController, widgetRef);
		check(WidgetPointer);
		WidgetPointer->AddToPlayerScreen();
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Raycast();
}
void APlayerCharacter::Raycast() {
	interactable = nullptr;
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
			interactable = (AInteractable*)outHit.GetActor();
		}
	}
	shouldRaycast = false;
}

void APlayerCharacter::Interact()
{
	if (interactable == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Interacting"));

	inventory[0] = (interactable->item);

	if (inventory[0].image != nullptr) {
		WidgetPointer->tex = inventory[0].image;
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
	}

	//interactable->Destroy();
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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);

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
