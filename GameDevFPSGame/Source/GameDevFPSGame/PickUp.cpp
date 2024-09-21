// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyCharacter.h" // Assuming this is the player's character class
#include "GameFramework/Actor.h"

// Sets default values
APickUp::APickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create the collision component and set it as the root component
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->InitSphereRadius(50.0f);
    RootComponent = CollisionComponent;

    // Create the static mesh for the pickup object
    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    PickupMesh->SetupAttachment(RootComponent);

    // Enable overlap events
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

    // Bind the overlap event
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);

    // Initialize default values
    PickupType = "Health"; // Default to health
    PickupValue = 25.0f;   // Default health value or ammo


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
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the overlapping actor is the player
    AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OtherActor);

    if (PlayerCharacter)
    {
        // If the pickup type is health
        if (PickupType == "Health")
        {
            PlayerCharacter->CurrentHealth += PickupValue;

            // Ensure health doesn't exceed max health
            if (PlayerCharacter->CurrentHealth > PlayerCharacter->MaxHealth)
            {
                PlayerCharacter->CurrentHealth = PlayerCharacter->MaxHealth;
            }

            // Update UI or display a message (optional)
        }

        // If the pickup type is ammo
        else if (PickupType == "Ammo")
        {
            PlayerCharacter->ammo += PickupValue; // Update player's ammo
        }

        // Destroy the pickup after it has been collected
        Destroy();
    }
}

