// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseCharacter.h"
#include "AIController.h"
#include "WeaponHandling.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

UCLASS()
class GAMEDEVFPSGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	UBehaviorTreeComponent* Behavoior;

	UBlackboardComponent* Blackboard;

	//keys
	

	TArray<AActor*> PatrolPoints;
	virtual void OnPossess(APawn* NewPawn) override;

	int32 AssignedPoint;
public:
	// Sets default values for this actor's properties
	AEnemyAIController();

	void SetPlayerFound(APawn* InPawn); // useless function

	FORCEINLINE UBlackboardComponent* getBlackBaordComp() const { return Blackboard; }

	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return  PatrolPoints; }

	void fire();

	void SwitchWep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UAISenseConfig_Sight* SightConfig;

	void SetUpPerceptionSystem();

	UFUNCTION()
	void PlayerDetected(AActor* actor, FAIStimulus const Stimulus);

private :
	AEnemyBaseCharacter* npc = nullptr;

	UPROPERTY()
	UWeaponHandling* Wep = nullptr;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
