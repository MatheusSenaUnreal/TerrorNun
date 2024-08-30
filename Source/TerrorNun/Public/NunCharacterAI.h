#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "NunCharacterAI.generated.h"

UCLASS()
class TERRORNUN_API ANunCharacterAI : public ACharacter
{
	GENERATED_BODY()

public:
	ANunCharacterAI();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = "LocationPatrol")
	 TArray<AActor*>RefPoints;

	

};
