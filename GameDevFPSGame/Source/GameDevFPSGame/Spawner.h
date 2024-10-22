// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"MyCharacter.h"
#include "Spawner.generated.h"

UCLASS()
class GAMEDEVFPSGAME_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawner();

	void RespawnCharacter(ACharacter* CharacterToRespawn);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	TArray<AActor*> RespawnPoints;

	// Function to gather all spawn points in the level
	void FindRespawnPoints();

};
