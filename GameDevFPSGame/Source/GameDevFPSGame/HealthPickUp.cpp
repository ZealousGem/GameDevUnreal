// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "MyCharacter.h"
#include "HUDDisplayClass.h"
#include "GameFramework/PlayerController.h"

#include "EnemyBaseCharacter.h"


// Sets default values
AHealthPickUp::AHealthPickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthAmount = 10;
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
		Destroy();

		//if (PlayerCharacter->Change)
		//{
			// Need to add code into other class (PlayerCharacter->ammo += AmmoAmount;)

			//if (HUD)
			//{

				// Need to change code for health (HUD->UpdateAmmo(PlayerCharacter->ammo);)

			//}

			

		//}

		//if (AEnemyBaseCharacter* enemy = Cast<AEnemyBaseCharacter>(OtherActor))
		//{
			//Need to add code
		//}
		//Destroy()



	}

}
//void AHealthPickUp::PickitUp()
//{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("health Picked Up")));

//}

