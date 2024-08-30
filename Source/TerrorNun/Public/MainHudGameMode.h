#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainHudGameMode.generated.h"

UCLASS()
class TERRORNUN_API AMainHudGameMode : public AGameMode
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Main Hud")
	TSubclassOf<class UUserWidget> MainHud;

	UPROPERTY()
	class UUserWidget* CurrentWidget;
};
