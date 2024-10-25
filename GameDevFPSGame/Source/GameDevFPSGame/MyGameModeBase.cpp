// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

// sets the gamemode, will use this for part 2
void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	gameManager = NewObject<UGameManager>();

	AAmmoPickUp* AmmoPickUp = GetWorld()->SpawnActor<AAmmoPickUp>(); // retrives the pickup classes
	AWeaponpPickUp* WeaponPickUp = GetWorld()->SpawnActor<AWeaponpPickUp>();
	AMyCharacter* Character = GetWorld()->SpawnActor<AMyCharacter>();
	// generates observers

	if(gameManager)
	{
		gameManager->AssignObserver(AmmoPickUp); // assigns the pickup class as an oberverer
		gameManager->AssignObserver(WeaponPickUp); // assigns weapon pickup as an oberbser
		gameManager->AssignObserverWeapon(WeaponPickUp); 
		gameManager->AssignObserverHP(Character); // assings character to both the wepon and hp observer
		gameManager->AssignObserverWeapon(Character);
	}

	if(gameManager)
	{
		gameManager->notifyChange(); // check any changes from the assigned obervers 
	}
}
