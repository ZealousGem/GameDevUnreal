// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Kismet/GameplayStatics.h"
#include"MyCharacter.h"
#include"EnemyBaseCharacter.h"
#include "Engine/Engine.h"


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
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Found %d respawn points"), RespawnPoints.Num()));
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Periodically check if the player's health is zero and trigger respawn
    AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (PlayerCharacter && PlayerCharacter->CurrentHealth == 0)
    {
        RespawnCharacter(PlayerCharacter);
    }

    // Find all enemies in the world
    TArray<AActor*> EnemyCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBaseCharacter::StaticClass(), EnemyCharacters);

    // Check each enemy's health
    for (AActor* Actor : EnemyCharacters)
    {
        AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(Actor);
        if (EnemyCharacter && EnemyCharacter->CurrentHealth == 0)
        {
            // Respawn the enemy if health is zero
            RespawnCharacter(EnemyCharacter);
        }
    }
    //AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(UGameplayStatics::GetEnemyCharacter(GetWorld(), 0));

}

void ASpawner::FindRespawnPoints()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("SpawnPoint"), RespawnPoints);
}



void ASpawner::RespawnCharacter(ACharacter* CharacterToRespawn)
{
    //GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("In respawn character method")));
    if (CharacterToRespawn && RespawnPoints.Num() > 0)
    {
        // Get a random respawn point
        int32 RandomIndex = FMath::RandRange(0, RespawnPoints.Num() - 1);
        AActor* RespawnPoint = RespawnPoints[RandomIndex];

        //GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Gets respawn point")));

        // Set the character's location to the respawn point
        CharacterToRespawn->SetActorLocation(RespawnPoint->GetActorLocation());
        //GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("set character location to respawn point")));

        // Optionally reset character's health and state here
        if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(CharacterToRespawn))
        {
            MyCharacter->CurrentHealth = MyCharacter->MaxHealth; // Reset health
            MyCharacter->ammo = 12;
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("reset character health")));
            MyCharacter->ApplyDamage(0);
        }

        else if (AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(CharacterToRespawn))
        {
            EnemyCharacter->CurrentHealth = EnemyCharacter->MaxHealth;
             EnemyCharacter->ammo = 12;// Reset enemy health
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Enemy health reset to maximum."));
            // Reset any additional enemy state if necessary
        }
    }
}

