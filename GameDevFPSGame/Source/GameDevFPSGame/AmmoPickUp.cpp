// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickUp.h"


// Sets default values
AAmmoPickUp::AAmmoPickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AmmoAmount = 10; // sets to added ammo amount to 10
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
	// overides parents overlap function
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// Cast the overlapping actor to the player character class (AMyCharacter)
	AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OtherActor);
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

	Destroy(); // destorys pickup
}

