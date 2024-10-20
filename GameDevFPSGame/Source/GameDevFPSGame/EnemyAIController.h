// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyAIController.generated.h"

UCLASS()
class GAMEDEVFPSGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	UBehaviorTreeComponent* Behavoior;

	UBlackboardComponent* Blackboard;

	//keys

	UPROPERTY(EditDefaultsOnly, Category= AI)
	FName LocationKey;

	UPROPERTY(EditDefaultsOnly, Category= AI)
	FName PlayerKey;

	TArray<AActor*> PatrolPoints;
	virtual void OnPossess(APawn* NewPawn) override;

	int32 AssignedPoint;
public:
	// Sets default values for this actor's properties
	AEnemyAIController();

	void SetPlayerFound(APawn* InPawn);

	FORCEINLINE UBlackboardComponent* getBlackBaordComp() const { return Blackboard; }

	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return  PatrolPoints; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
