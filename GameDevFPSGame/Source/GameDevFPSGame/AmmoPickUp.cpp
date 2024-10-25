// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickUp.h"

#include "EnemyBaseCharacter.h"


// Sets default values
AAmmoPickUp::AAmmoPickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AmmoAmount = 10; // sets to added ammo amount to 10
	PickedUp = true;
}

// Called when the game starts or when spawned
void AAmmoPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmoPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PickitUp();
	// overides parents overlap function
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
if(PickedUp)
{
	if(AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OtherActor))
	{
		AHUDDisplayClass* HUD = Cast<AHUDDisplayClass>(GetWorld()->GetFirstPlayerController()->GetHUD());


		// If the cast succeeds and it's the player character, give ammo
		if(PlayerCharacter->Change)
		{
			PlayerCharacter->ammo += AmmoAmount;
			if(HUD)
			{
				HUD->UpdateAmmo(PlayerCharacter->ammo); // updates the ammo widget hud
			}

		}
	}

	if(AEnemyBaseCharacter* enemy = Cast<AEnemyBaseCharacter>(OtherActor))
	{
		// will add later
		enemy->ammo += AmmoAmount;
	}
	
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AAmmoPickUp::Respawn, 10.0f, false);
	PickupMesh->SetVisibility(false);
	SetActorHiddenInGame(true);

}
	// Cast the overlapping actor to the player character class (AMyCharacter)

//Destroy(); // destorys pickup
}

void AAmmoPickUp::Respawn()
{
	PickedUp = true;
	//SetActorHiddenInGame(false);
	PickupMesh->SetVisibility(true);
	SetActorHiddenInGame(false);
}

void AAmmoPickUp::PickitUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Ammo Picked Up")));
}



