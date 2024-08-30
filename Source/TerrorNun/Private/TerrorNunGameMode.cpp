#include "TerrorNunGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MainChar.h"

void ATerrorNunGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	/*AMainChar* RefPlayer = Cast<AMainChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MainHud)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainHud);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}*/
}



