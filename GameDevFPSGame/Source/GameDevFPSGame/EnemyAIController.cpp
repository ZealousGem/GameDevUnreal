#include "EnemyAIController.h"

#include "AmmoPickUp.h"
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

	
	
	AssignedPoint = 0;
}

void AEnemyAIController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	Wep = NewObject<UWeaponHandling>(this);
	npc = Cast<AEnemyBaseCharacter>(NewPawn);
	
	Wep->ActivateNPC(npc);
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
	//
	
	
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Enemy is Shooting")));
	Wep->NPCFire();
	
	
}

void AEnemyAIController::SwitchWep()
{
	
		if(npc->ammo <=0)
		{
			Wep->NPCSwitchPrimary();
		}

	    
	    else
	    {
		    Wep->NPCSwitchSecondary();
	    }
	
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
		SightConfig->SightRadius = 700.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 720.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::PlayerDetected); // will sense any of the actors in this function
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AEnemyAIController::PlayerDetected(AActor* actor, FAIStimulus const Stimulus) // will be able to retrieve key in blackboard to create sequence condition
{
	if(AMyCharacter* ca = Cast<AMyCharacter>(actor))
	{
		GetBlackboardComponent()->SetValueAsBool("SeesPlayer", Stimulus.WasSuccessfullySensed());
	}

	else if(AAmmoPickUp* ar = Cast<AAmmoPickUp>(actor))
	{
		GetBlackboardComponent()->SetValueAsBool("SeesAmmo", Stimulus.WasSuccessfullySensed());
	}

	else if(AEnemyBaseCharacter* help = Cast<AEnemyBaseCharacter>(actor)) 
	{
		GetBlackboardComponent()->SetValueAsBool("SeesNPC", Stimulus.WasSuccessfullySensed());
	}
}

// Called every frame
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool PlayerIsVisible = GetBlackboardComponent()->GetValueAsBool("SeesPlayer"); // will override the node to make enemies attack players if they stuck hitting each other

	if(PlayerIsVisible)
	{
		 GetBlackboardComponent()->SetValueAsBool("SeesNPC", false);
		
	}

	
}