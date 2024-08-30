#include "MainHudGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"

void AMainHudGameMode::BeginPlay()
{
	Super::BeginPlay();

	APawn* RefPlayer = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	if (MainHud)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainHud);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			if (RefPlayer)
			{
				RefPlayer->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
				if (PC)
				{
					PC->bShowMouseCursor = true;

				}
			}
		}
	}
}
