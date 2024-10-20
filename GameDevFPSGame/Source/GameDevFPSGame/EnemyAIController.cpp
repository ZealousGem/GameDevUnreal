#include "EnemyAIController.h"
#include "EnemyBaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyAIController::AEnemyAIController()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Behavoior = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavoior"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));

	PlayerKey = "Target";
	LocationKey = "LocationTo";

	AssignedPoint = 0;
}

void AEnemyAIController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	AEnemyBaseCharacter* AIChar = Cast<AEnemyBaseCharacter>(NewPawn);
	if (AIChar)
	{
		Blackboard->InitializeBlackboard(*(AIChar->BehaviourTree->BlackboardAsset));
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBaseCharacter::StaticClass(), PatrolPoints); // populates nodes

	Behavoior->StartTree(*AIChar->BehaviourTree); // runs tree
}

void AEnemyAIController::SetPlayerFound(APawn* InPawn)
{
	if (Blackboard)
	{
		Blackboard->SetValueAsObject(PlayerKey, InPawn);
	}
}

// Called when the game starts or when spawned
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}