#include "BTTask_Patrol.h"
#include "NunAIController.h"
#include "NunCharacterAI.h"
#include "MainChar.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h" 
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_Patrol::UBTTask_Patrol()
{
    NodeName = "AIPatrol";
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Obtém o controlador da IA
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController)
    {
        ANunAIController* NunController = Cast<ANunAIController>(AIController);
        if (NunController)
        {
            ANunCharacterAI* NunChar = Cast<ANunCharacterAI>(NunController->GetPawn());
            if (NunChar)
            {
                UBlackboardComponent* BP = NunController->GetBlackboardComponent();
                if (BP)
                {
                    int32 RandomIndex = FMath::RandRange(0, NunChar->RefPoints.Num() - 1);// Posição aleatoria para a IA ir

                    // Define o valor de uma variável no Blackboard
                    BP->SetValueAsVector(VarKey.SelectedKeyName, FVector(NunChar->RefPoints[RandomIndex]->GetActorLocation()));
                    
                    NunChar->GetCharacterMovement()->MaxWalkSpeed = 250.f;
                    // Se a tarefa foi executada com sucesso, retorna Succeeded
                    return EBTNodeResult::Succeeded;
                }
            }
        }
    }

    // Se qualquer verificação falhar, retorna Failed
    return EBTNodeResult::Failed;
}
