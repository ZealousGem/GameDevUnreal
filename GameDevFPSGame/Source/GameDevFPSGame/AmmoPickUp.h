// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "PickUp.h"
#include "AmmoPickUp.generated.h"

UCLASS()
class GAMEDEVFPSGAME_API AAmmoPickUp : public APickUp
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAmmoPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int AmmoPickUp(); // a function we will use for project 2

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	   class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties") // ammo given to the player once picked up
	int32 AmmoAmount;
};
