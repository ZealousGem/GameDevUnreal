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

    // Set default ammo amount
    AmmoAmount = 10;  // You can modify this value in the editor


    // Create the collision component and set it as the root component
    //CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    //CollisionComponent->InitSphereRadius(50.0f);
    //RootComponent = CollisionComponent;

    // Create the static mesh for the pickup object
    //PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    //PickupMesh->SetupAttachment(RootComponent);

    // Enable overlap events
    //CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    //CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

    // Bind the overlap event
    //CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);

    // Initialize default values
    //PickupType = "Health"; // Default to health
    //PickupValue = 25.0f;   // Default health value or ammo


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
    if (OtherActor)
    {
        // Cast the overlapping actor to the player character class (AMyCharacter)
        AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OtherActor);
        AHUDDisplayClass* HUD = Cast<AHUDDisplayClass>(GetWorld()->GetFirstPlayerController()->GetHUD());

        if (PlayerCharacter)
        {
            if(!PlayerCharacter->Change)
            {
                PlayerCharacter->Change = true;
                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Shot Gun Picked Up")));
            }
           
            if(PlayerCharacter->Change)
            {
                PlayerCharacter->ammo += AmmoAmount;
                if(HUD)
                {
                    HUD->UpdateAmmo(PlayerCharacter->ammo);
                }

            }
            // If the cast succeeds and it's the player character, give ammo
            
            // Optional: Debug message
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Visible"))); // debug to check if it working

            // Destroy the pickup after it's collected
            Destroy();
        }
    }
}

