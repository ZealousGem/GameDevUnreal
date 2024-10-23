// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "UBTTTask_FindRandLocation.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API UUBTTTask_FindRandLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UUBTTTask_FindRandLocation(FObjectInitializer const & ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI", meta=(AllowPrivateAccess= "true"))
	float SearchRadius = 1500.f;
};

UCLASS()
class GAMEDEVFPSGAME_API UUBTTTask_PlayerFound : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UUBTTTask_PlayerFound(FObjectInitializer const & ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Searching", meta=(AllowPrivateAccess= "true"))
	bool RandomSearch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI", meta=(AllowPrivateAccess= "true"))
	float SearchRadius = 150.f;
	
};

UCLASS()
class GAMEDEVFPSGAME_API UUBTTTask_ShootPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UUBTTTask_ShootPlayer(FObjectInitializer const & ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI", meta=(AllowPrivateAccess= "true"))
	float SearchRadius = 150.f;
	
	AEnemyAIController* npc;
};

UCLASS()
class GAMEDEVFPSGAME_API UUBTTTask_FoundAmmo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UUBTTTask_FoundAmmo(FObjectInitializer const & ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI", meta=(AllowPrivateAccess= "true"))
	float SearchRadius = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Searching", meta=(AllowPrivateAccess= "true"))
	bool RandomSearch = false;
	
	
};
