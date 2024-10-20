﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTTTask_FindRandLocation.h"
#include "MyCharacter.h"
#include "EnemyAIController.h"
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
		 auto const Orgin = npc->GetActorLocation(); // generates a random location for ai to go to

	 	if(auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld()))
	 	{

            FNavLocation Loc;

	 		if(Nav->GetRandomPointInNavigableRadius(Orgin, SearchRadius, Loc))
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
			 			Enem->SetActorRotation(LookATPlayer);
			 		}
			 	}
			 	
			 	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
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
