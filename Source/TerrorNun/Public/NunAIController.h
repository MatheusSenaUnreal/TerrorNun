#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NunAIController.generated.h"

UCLASS()
class TERRORNUN_API ANunAIController : public AAIController
{
	GENERATED_BODY()

public:
    ANunAIController();

protected:
    virtual void OnPossess(APawn* InPawn) override;
private:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UBehaviorTree* BehaviorTree;

    void SetBP();
    FTimerHandle Time;

public:
    UPROPERTY(EditAnywhere, Category = "AI")
    UAIPerceptionComponent* AIPerception;

    // Configuração da Visão
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
  class  UAISenseConfig_Sight* SightConfig2;

    // Configuração da Audição
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    class UAISenseConfig_Hearing* HearingConfig2;

    UFUNCTION()
    virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    void SetHiddenForAI();
};
