#include "EnemyAIController.h"
#include "EnemyBaseCharacter.h"
#include "MyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AEnemyAIController::AEnemyAIController()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Behavoior = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavoior"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));

	SetUpPerceptionSystem(); // sets the ai vision perimter 
	PlayerKey = "Target";
	LocationKey = "LocationTo";

	Wep = NewObject<UWeaponHandling>();
	npc = Cast<AEnemyBaseCharacter>(GetCharacter());
	
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

void AEnemyAIController::fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Enemy is Shooting")));
	//Wep->ActivateNPC(npc); causes crash
}

// Called when the game starts or when spawned
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::SetUpPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));
	if(SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"))); // creates AI Vision radius
		SightConfig->SightRadius = 500.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::PlayerDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AEnemyAIController::PlayerDetected(AActor* actor, FAIStimulus const Stimulus)
{
	if(auto* const car = Cast<AMyCharacter>(actor))
	{
		GetBlackboardComponent()->SetValueAsBool("SeesPlayer", Stimulus.WasSuccessfullySensed());
	}
}

// Called every frame
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}