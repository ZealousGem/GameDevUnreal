// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h" // Assuming this is the player's character class
#include "PickUp.h"
#include "WeaponpPickUp.generated.h"

UCLASS()
class GAMEDEVFPSGAME_API AWeaponpPickUp : public APickUp, public IObserver
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponpPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	   class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void PickitUp() override;
	
};
