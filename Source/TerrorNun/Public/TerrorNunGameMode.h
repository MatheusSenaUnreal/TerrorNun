#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TerrorNunGameMode.generated.h"

UCLASS()
class TERRORNUN_API ATerrorNunGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, Category = "Main Hud")
	//TSubclassOf<class UUserWidget> MainHud;

	//UPROPERTY()
	//class UUserWidget* CurrentWidget;
};
