#include "NunAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionTypes.h"
#include "MainChar.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense.h"

ANunAIController::ANunAIController()
{
    AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerception"));
    
    // Configuração de Visão (AISightConfig)
    SightConfig2 = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig2->SightRadius = 3000.0f; // Alcance da visão
    SightConfig2->LoseSightRadius = 3500.0f; // Alcance onde a visão "perde" o alvo
    SightConfig2->PeripheralVisionAngleDegrees = 90.0f; // Ângulo de visão periférica
    SightConfig2->SetMaxAge(5.0f); // Quanto tempo a IA "lembra" de algo que viu
    SightConfig2->AutoSuccessRangeFromLastSeenLocation = 900.f;
    SightConfig2->DetectionByAffiliation.bDetectEnemies = true; // Detectar inimigos
    SightConfig2->DetectionByAffiliation.bDetectFriendlies = true; // Detectar aliados
    SightConfig2->DetectionByAffiliation.bDetectNeutrals = true; // Detectar neutros
    SightConfig2->AutoSuccessRangeFromLastSeenLocation = -1.f;
    SightConfig2->PointOfViewBackwardOffset = 0.f;
    SightConfig2->NearClippingRadius = 0.f;


    // Configuração de Audição (AIHearingConfig)
    HearingConfig2 = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
    HearingConfig2->HearingRange = 600.0f; // Alcance da audição
    HearingConfig2->SetMaxAge(3.0f); // Quanto tempo a IA "lembra" do som
    HearingConfig2->DetectionByAffiliation.bDetectEnemies = true; // Detectar inimigos
    HearingConfig2->DetectionByAffiliation.bDetectFriendlies = true; // Detectar aliados
    HearingConfig2->DetectionByAffiliation.bDetectNeutrals = true; // Detectar neutros

    // Adicionar as configurações ao componente de percepção
    AIPerception->ConfigureSense(*HearingConfig2);
    AIPerception->ConfigureSense(*SightConfig2);
    // Definir qual tipo de percepção será dominante (opcional)
    AIPerception->SetDominantSense(SightConfig2->GetSenseImplementation());

   /* AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ANunAIController::OnTargetPerceptionUpdated);*/

    AIPerception->ConfigureSense(*SightConfig2);

    
}

void ANunAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
    }
}

void ANunAIController::SetBP()
{
    UBlackboardComponent* BP = GetBlackboardComponent();
    if (BP)
    {
       
        BP->SetValueAsBool("bCanSeePlayer", false);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Perdeu"));
    }
}

void ANunAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (Stimulus.WasSuccessfullySensed())
    {

        if (Stimulus.Type == UAISense_Sight::StaticClass()->GetDefaultObject<UAISense>()->GetSenseID())
        {
            UBlackboardComponent* BP = GetBlackboardComponent();
            if (BP)
            {
                AMainChar* MainChar = Cast<AMainChar>(Actor);
                if (MainChar)
                {
                    if (MainChar->bIsHidden == false)
                    {
                       GetWorld()->GetTimerManager().ClearTimer(Time);
                       BP->SetValueAsBool("bCanSeePlayer", true);
                    }
                }
            }
        }
        else if (Stimulus.Type == UAISense_Hearing::StaticClass()->GetDefaultObject<UAISense>()->GetSenseID())
        {
            UBlackboardComponent* BP = GetBlackboardComponent();
            if (BP)
            {
                if (Stimulus.Tag == "noise")
                {
                    BP->SetValueAsBool("bHeardNoise", true);
                    BP->SetValueAsVector("InvestigateLocation", Stimulus.StimulusLocation);
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Escutou"));
                }
            }
        }
    }
    else
    {
        GetWorld()->GetTimerManager().SetTimer(Time, this, &ANunAIController::SetBP, 3.f, false);
    }
}

void ANunAIController::SetHiddenForAI()
{
    UBlackboardComponent* BP = GetBlackboardComponent();
    if (BP)
    {
            GetWorld()->GetTimerManager().ClearTimer(Time);
            BP->SetValueAsBool("bCanSeePlayer", false);
        
    }
}
