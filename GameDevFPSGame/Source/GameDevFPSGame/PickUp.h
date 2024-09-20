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
};
