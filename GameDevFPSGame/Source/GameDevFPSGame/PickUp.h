// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"
// made this pickup class for the pickup blueprint, Max use this class to create the pickup functions
UCLASS()
class GAMEDEVFPSGAME_API APickUp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUp();

    
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int AmmoPickUp();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // This is the function that will be triggered when the player overlaps the pickup
    UFUNCTION()
     virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // Collision component for detecting overlaps
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
    class USphereComponent* CollisionComponent;

    // The mesh for the pickup item (e.g., a health pack)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
    UStaticMeshComponent* PickupMesh;

    // Determines what type of pickup it is (ammo, health, etc.)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    FString PickupType;

    // Amount of health or ammo to add
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float PickupValue;
};
