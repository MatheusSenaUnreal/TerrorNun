#include "MainHudUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainHudUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonQuit && ButtonStart && ButtonOptions)
	{
		ButtonStart->OnClicked.AddDynamic(this, &UMainHudUserWidget::OnButtonClickStart);
		ButtonOptions->OnClicked.AddDynamic(this, &UMainHudUserWidget::OnButtonClickOptions);
		ButtonQuit->OnClicked.AddDynamic(this, &UMainHudUserWidget::OnButtonClickQuit);
	}
}


void UMainHudUserWidget::OnButtonClickStart()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName("HouseMap"), true);
	}
}

void UMainHudUserWidget::OnButtonClickOptions()
{
}

void UMainHudUserWidget::OnButtonClickQuit()
{
	UWorld* World = GetWorld();
	if ( World)
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, 0);
		}
	}
}
