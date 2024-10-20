﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Observer.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS(Abstract)
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

	

    UPROPERTY(EditAnywhere)
    USceneComponent* PickupRoot;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* PickupMesh;

    UPROPERTY(EditAnywhere)
    UShapeComponent* PickupBox;


    // This is the function that will be triggered when the player overlaps the pickup, also this is a method that will be overidden by the child classes
    UFUNCTION()
     virtual  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


    
};
