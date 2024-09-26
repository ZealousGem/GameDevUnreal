// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyCharacter.h" // Assuming this is the player's character class
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>

// Sets default values
APickUp::APickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    PickupRoot= CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
    RootComponent = PickupRoot;

    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    PickupMesh->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

    PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
    PickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
    PickupBox->SetGenerateOverlapEvents(true);
    PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);
    PickupBox->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
    
	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// This function is triggered when something overlaps the pickup
void APickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){}

