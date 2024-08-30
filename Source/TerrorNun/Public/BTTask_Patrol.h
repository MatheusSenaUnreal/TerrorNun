#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Patrol.generated.h"

UCLASS()
class TERRORNUN_API UBTTask_Patrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
		
public:
	UBTTask_Patrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Chave do Blackboard para a variável que queremos modificar
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector VarKey;
};
