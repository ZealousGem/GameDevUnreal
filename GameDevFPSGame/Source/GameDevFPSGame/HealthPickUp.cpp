﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "MyCharacter.h"
#include "HUDDisplayClass.h"
#include "GameFramework/PlayerController.h"

#include "EnemyBaseCharacter.h"
#include "Engine/World.h" // Include the header for GetWorld()
#include "TimerManager.h"



// Sets default values
AHealthPickUp::AHealthPickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthAmount = 25;
	bIsActive = true;
}

// Called when the game starts or when spawned
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AHealthPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//PickitUp();

	if (bIsActive)
	{
		Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

		if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OtherActor))
		{
			if (PlayerCharacter->CurrentHealth < PlayerCharacter->MaxHealth)
			{
				PlayerCharacter->Heal(HealthAmount);
			}

			AHUDDisplayClass* HUD = Cast<AHUDDisplayClass>(GetWorld()->GetFirstPlayerController()->GetHUD());

			if (HUD)
			{
				float HealthPercentage = PlayerCharacter->CurrentHealth / PlayerCharacter->MaxHealth;
				HUD->UpdateHealthBar(HealthPercentage);
			}

			bIsActive = false;

			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AHealthPickUp::Respawn, 5.0f, false);
            PickupMesh->SetVisibility(false);
			SetActorHiddenInGame(true);
			



		}
		else if (AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(OtherActor))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Player Healed"));
			// Check if the enemy's current health is less than maximum health
			if (EnemyCharacter->CurrentHealth < EnemyCharacter->MaxHealth)
			{
				
				EnemyCharacter->CurrentHealth += HealthAmount; // Add health to the enemy

				// Ensure enemy health doesn't exceed max health
				if (EnemyCharacter->CurrentHealth > EnemyCharacter->MaxHealth)
				{
					EnemyCharacter->CurrentHealth = EnemyCharacter->MaxHealth;
				}

				// Deactivate the pickup
				bIsActive = false;
				// Start respawn timer
				GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AHealthPickUp::Respawn, 5.0f, false);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Player Healed"));
				PickupMesh->SetVisibility(false);
				// Optionally, make it invisible
				SetActorHiddenInGame(true);
			}
		}


	}

}

void AHealthPickUp::Respawn()
{
	bIsActive = true;
	PickupMesh->SetVisibility(true);
	SetActorHiddenInGame(false);
}
	
//void AHealthPickUp::PickitUp()
//{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("health Picked Up")));

//}

