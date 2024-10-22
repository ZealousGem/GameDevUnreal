// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Kismet/GameplayStatics.h"
#include"MyCharacter.h"


// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	FindRespawnPoints();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawner::FindRespawnPoints()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("RespawnPoint"), RespawnPoints);
}


// i dont know if it reaches here
void ASpawner::RespawnCharacter(ACharacter* CharacterToRespawn)
{
    if (CharacterToRespawn && RespawnPoints.Num() > 0)
    {
        // Get a random respawn point
        int32 RandomIndex = FMath::RandRange(0, RespawnPoints.Num() - 1);
        AActor* RespawnPoint = RespawnPoints[RandomIndex];

        // Set the character's location to the respawn point
        CharacterToRespawn->SetActorLocation(RespawnPoint->GetActorLocation());

        // Optionally reset character's health and state here
        if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(CharacterToRespawn))
        {
            MyCharacter->CurrentHealth = MyCharacter->MaxHealth; // Reset health
        }
    }
}

