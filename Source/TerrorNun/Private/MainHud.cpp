#include "MainHud.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UMainHud::NativeConstruct()
{
	Super::NativeConstruct();

	CrosshairInteract = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/TerrorNun/Image/TX_InteractCrosshair.TX_InteractCrosshair'"));

	CrosshairNormal = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/TerrorNun/Image/TX_Crooshair.TX_Crooshair'"));

}

void UMainHud::UpdateCrosshair()
{

	if (CrosshairInteract)
	{
		if (Crosshair)
		{
			Crosshair->SetBrushFromTexture(CrosshairNormal);
			Crosshair->SetBrushSize(FVector2D(45.f, 45.f));
		}
	}

}

void UMainHud::UpdateCrosshairInteract()
{
	if (CrosshairInteract)
	{
		if (Crosshair)
		{
			Crosshair->SetBrushFromTexture(CrosshairInteract);
			Crosshair->SetBrushSize(FVector2D(100.f, 100.f));
		}
	}
}
