// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "MyCharacter.h"
#include "HUDDisplayClass.h"
#include "GameFramework/PlayerController.h"
#include "EnemyBaseCharacter.h"
#include "Engine/World.h" 
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
	

	if (bIsActive)
	{
		Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

		if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OtherActor))
		{
			// Check if the players current health is less than maximum health
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

			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AHealthPickUp::Respawn, 10.0f, false);
            PickupMesh->SetVisibility(false);
			SetActorHiddenInGame(true);
			



		}
		else if (AEnemyBaseCharacter* EnemyCharacter = Cast<AEnemyBaseCharacter>(OtherActor))
		{
			
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
				GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AHealthPickUp::Respawn, 10.0f, false);
				
				PickupMesh->SetVisibility(false);
				
				SetActorHiddenInGame(true);
			}
		}


	}

}

//used to respawn the health pickup
void AHealthPickUp::Respawn()
{
	bIsActive = true;
	PickupMesh->SetVisibility(true);
	SetActorHiddenInGame(false);
}
	


