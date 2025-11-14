// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"


// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->SetSimulatePhysics(true);

	item.mesh = mesh->GetStaticMesh();
	item.name = FText::FromString(mesh->GetName());
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable::GenerateImage()
{
	sceneCaptureComponent = Cast<USceneCaptureComponent2D>(AddComponentByClass(USceneCaptureComponent2D::StaticClass(), false, GetTransform(), false));
	sceneCaptureComponent->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::SnapToTargetIncludingScale);
	float bounds = mesh->GetStaticMesh()->GetBounds().SphereRadius;
	sceneCaptureComponent->OrthoWidth = (bounds*2);
	//sceneCaptureComponent->ShowOnlyComponent(mesh);
	FVector pos = (sceneCaptureComponent->GetRelativeLocation()) + FVector(bounds,0,0);
	rt = UKismetRenderingLibrary::CreateRenderTarget2D(this, 512, 512, RTF_R8);
	//sceneCaptureComponent->DestroyComponent();
	
	//UTexture2D* tex;
	
	//tex = UKismetRenderingLibrary::RenderTargetCreateStaticTexture2DEditorOnly(rt, mesh->GetStaticMesh()->GetName());
	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(this, FName("CreateTexture"));
	GetWorldTimerManager().SetTimerForNextTick(timerDelegate);
	
	
}

void AInteractable::CreateTexture()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
	//image = UKismetRenderingLibrary::RenderTargetCreateStaticTexture2DEditorOnly(rt, mesh->GetStaticMesh()->GetName());
	image = rt->ConstructTexture2D(this, mesh->GetStaticMesh()->GetName(), EObjectFlags::RF_NoFlags, CTF_Default);
}