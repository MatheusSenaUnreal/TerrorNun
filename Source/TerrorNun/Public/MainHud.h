#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHud.generated.h"

UCLASS()
class TERRORNUN_API UMainHud : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Crosshair;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canva;

	UTexture2D* CrosshairInteract;
	UTexture2D* CrosshairNormal;

	virtual void NativeConstruct() override;
public:
	void UpdateCrosshair();
	void UpdateCrosshairInteract();
};
