#include "NunCharacterAI.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"
#include "MainChar.h"
#include "Components/CapsuleComponent.h"

ANunCharacterAI::ANunCharacterAI()
{
	PrimaryActorTick.bCanEverTick = true;



}

void ANunCharacterAI::BeginPlay()
{
	Super::BeginPlay();
	


}

void ANunCharacterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANunCharacterAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


