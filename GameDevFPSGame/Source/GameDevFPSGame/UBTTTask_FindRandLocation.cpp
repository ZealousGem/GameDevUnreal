// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTTTask_FindRandLocation.h"

#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UUBTTTask_FindRandLocation::UUBTTTask_FindRandLocation(FObjectInitializer const& ObjectInitializer)
{
 NodeName = "Find a Rand Location In NavMesh";

	
}

EBTNodeResult::Type UUBTTTask_FindRandLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
 if(auto* const fock = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
 {
	 if(auto* const npc = fock->GetPawn())
	 {
		 auto const Orgin = npc->GetActorLocation();

	 	if(auto* const Nav = UNavigationSystemV1::GetCurrent(GetWorld()))
	 	{

            FNavLocation Loc;

	 		if(Nav->GetRandomPointInNavigableRadius(Orgin, SearchRadius, Loc))
	 		{
	 			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
	 		}

	 		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	 		return  EBTNodeResult::Succeeded;
	 	}
	 }
 	return EBTNodeResult::Failed;
 }
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
