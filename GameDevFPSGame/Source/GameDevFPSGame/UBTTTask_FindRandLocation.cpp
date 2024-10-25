// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTTTask_FindRandLocation.h"

#include "AmmoPickUp.h"
#include "MyCharacter.h"
#include "EnemyAIController.h"
#include "EnemyBaseCharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UUBTTTask_FindRandLocation::UUBTTTask_FindRandLocation(FObjectInitializer const& ObjectInitializer)
{
 NodeName = "Find a Rand Location In NavMesh";

	
}

EBTNodeResult::Type UUBTTTask_FindRandLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
 if(auto* const fock = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
 {
	 if(auto* const npc = fock->GetPawn()) // retirves the enemmy character
	 {
		 auto const Orgin = npc->GetActorLocation(); // grabs the ai's location

	 	if(auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld()))
	 	{

            FNavLocation Loc;

	 		if(Nav->GetRandomPointInNavigableRadius(Orgin, SearchRadius, Loc)) // will retieve navigation actor in game world
	 		{
	 			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location); // sets the node location in the blackboard component
	 		}

	 		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // will succeed node once it has reached location
	 		return  EBTNodeResult::Succeeded;
	 	}
	 }
 	return EBTNodeResult::Failed;
 }
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

UUBTTTask_PlayerFound::UUBTTTask_PlayerFound(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Player Found");
}

EBTNodeResult::Type UUBTTTask_PlayerFound::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// retieve player character
	
	if(AMyCharacter* const Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) // gets location of player character
	{
		
		auto const playerLoc = Player->GetActorLocation();

		
		// gets the location to use as a centre point
		if(RandomSearch)
		{
			FNavLocation Loc; // generates random location near player
			if(auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
			 if(Nav->GetRandomPointInNavigableRadius(playerLoc, SearchRadius, Loc)) // gets random location near the player
			 {
				 OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
			 	FRotator LookATPlayer = ((playerLoc - Loc.Location).Rotation());
			 	AEnemyAIController* Enemy = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()); // gets enemy ai controller
			 	if(Enemy)
			 	{
			 		APawn* Enem = Enemy->GetPawn();
			 		if(Enem)
			 		{
			 			Enem->SetActorRotation(LookATPlayer); // makes the enemy look at the player 
			 		}
			 	}
			 	
			 	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // will tell tree that this node is successful
			 	return  EBTNodeResult::Succeeded;
			 }
			}
		}

		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLoc);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return  EBTNodeResult::Succeeded;
		}
		
	}
	
	

	
	return EBTNodeResult::Failed;
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

UUBTTTask_NPCFound::UUBTTTask_NPCFound(FObjectInitializer const& ObjectInitializer)
{
	NodeName =TEXT("NPC Found");
}

EBTNodeResult::Type UUBTTTask_NPCFound::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TArray<AActor*> EnimiesFound;  // creates array to allow many actos to be sensed

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBaseCharacter::StaticClass(), EnimiesFound);

	for(AActor* FoundActor : EnimiesFound) // detetcing first enemies in range
	{
		AEnemyBaseCharacter* npc = Cast<AEnemyBaseCharacter>(FoundActor); // instantiate the sensed actor to an enemyactor only 
		if(npc)
		{
			auto const playerLoc = npc->GetActorLocation(); // gets it's location
			if(RandomSearch)
			{
				FNavLocation Loc; // generates random location near player
				if(auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld()))
				{
					if(Nav->GetRandomPointInNavigableRadius(playerLoc, SearchRadius, Loc)) // gets random location near the player
					{
						OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
						
						AEnemyAIController* Enemy = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()); // gets enemy ai controller
						if(Enemy)
						{
							APawn* Enem = Enemy->GetPawn();
							if(Enem)
							{
						

								
									//FRotator CurrentRotation = Enem->GetActorRotation();
									FRotator LookATPlayer = ((playerLoc - Loc.Location).Rotation());
								;
									Enem->SetActorRotation(LookATPlayer); // makes the enemy look at the player
									GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("rotating")));
									
								
								
								
							    
							}
						}
			 	
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // will tell tree that this node is successful
						return  EBTNodeResult::Succeeded;
					}
				}
			}

			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLoc);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return  EBTNodeResult::Succeeded;
			}
			
		}
	}

	return  EBTNodeResult::Failed;
}

UUBTTTask_ShootPlayer::UUBTTTask_ShootPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName=TEXT("Attack Player");
}

EBTNodeResult::Type UUBTTTask_ShootPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AMyCharacter* const Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) // gets location of player character
	{
		auto const playerLoc = Player->GetActorLocation(); // gets player location
		npc = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()); // instantiates npc class
		if(SearchRadius) // will activate if player is in search radius
		{
			FNavLocation Loc;
			if(auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld())) // will activate location once its found nav actor
			{
				if(Nav->GetRandomPointInNavigableRadius(playerLoc, SearchRadius, Loc))
				{
					APawn* setPawn = OwnerComp.GetAIOwner()->GetPawn();
					AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(setPawn);
					
					Enemy->RoateToEnemy(Player);;
				
					npc->fire(); // activates firing logic 
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		
		
		
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return  EBTNodeResult::Failed;
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

UUBTTTask_ShootNPC::UUBTTTask_ShootNPC(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Shoot NPC");
}

EBTNodeResult::Type UUBTTTask_ShootNPC::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TArray<AActor*> EnimiesFound;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBaseCharacter::StaticClass(), EnimiesFound);

	for(AActor* FoundActor : EnimiesFound) // detetcing first enemies in range
	{
		AEnemyBaseCharacter* npc = Cast<AEnemyBaseCharacter>(FoundActor);
		if(npc)
		{
			auto const playerLoc = npc->GetActorLocation(); // gets player location
			npcPlayer = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()); // instantiates npc class
			if(SearchRadius) // will activate if player is in search radius
			{
				FNavLocation Loc;
				if(auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld())) // will activate location once its found nav actor
				{
					if(Nav->GetRandomPointInNavigableRadius(playerLoc, SearchRadius, Loc))
					{
						APawn* setPawn = OwnerComp.GetAIOwner()->GetPawn(); // fill dind posssed actor(ai)
						AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(setPawn);
						FVector ForwardVector = Enemy->GetActorForwardVector();
						FVector enemLoc = (npc->GetActorLocation() - Enemy->GetActorLocation()); // will retrieve the location of the spotted enemy
						enemLoc.Normalize();
						float dot = FVector::DotProduct(ForwardVector, enemLoc);
						dot = FMath::Clamp(dot, -1.0f, 1.0f);
						float Angling = FMath::Acos((dot) * (180.f/PI));
						bool canSeeNPC = Angling <= 90.f; 

						
						
						
							Enemy->RoateToEnemy(npc); // will rotate towards enemy
							canSeeNPC = false;
						
						npcPlayer->fire(); // activates firing logic 
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
						return EBTNodeResult::Succeeded;
					}
				}
			}
		
			
		}
		
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return  EBTNodeResult::Failed;
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

UUBTTTask_FoundAmmo::UUBTTTask_FoundAmmo(FObjectInitializer const& ObjectInitializer)
{
	NodeName=TEXT("Getting Ammo");
}

EBTNodeResult::Type UUBTTTask_FoundAmmo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TArray<AActor*> AmmoFound;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBaseCharacter::StaticClass(), AmmoFound);

	
	for(AActor* FoundActor : AmmoFound) // detetcing first enemies in range
	{
		APickUp* Ammo = Cast<APickUp>(FoundActor);
		if(Ammo){
			auto const AmmoLoc = Ammo->GetActorLocation();

		
			// gets the location to use as a centre point
			if(RandomSearch)
			{
				FNavLocation Loc; // generates random location near player
				if(auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld()))
				{
					if(Nav->GetRandomPointInNavigableRadius(AmmoLoc, SearchRadius, Loc)) // gets random location near the player
					{
						OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
			 	
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // will tell tree that this node is successful
						return  EBTNodeResult::Succeeded;
					}
				}
			}

			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), AmmoLoc);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return  EBTNodeResult::Succeeded;
			}
		
		}
	}
	
	return EBTNodeResult::Failed;
}

UUBTTTask_SwitchWeapon::UUBTTTask_SwitchWeapon(FObjectInitializer const& ObjectInitializer)
{
	NodeName=TEXT("SwitchWeapon");
}

EBTNodeResult::Type UUBTTTask_SwitchWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* Npc = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()); 
if(Npc)
{
	Npc->SwitchWep();
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return  EBTNodeResult::Succeeded;
}	

	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return  EBTNodeResult::Failed;
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
