#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHudUserWidget.generated.h"

UCLASS()
class TERRORNUN_API UMainHudUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canvas;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* WSizeBox;

	UPROPERTY(meta = (BindWidget))
	class UBorder* WBorder;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TerrorNunText;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* WVerticalBox;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	class UButton* ButtonStart;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StartText;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonOptions;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OptionsText;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonQuit;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitText;


	virtual void NativeConstruct()  override;

	UFUNCTION()
	void OnButtonClickStart();

	UFUNCTION()
	void OnButtonClickOptions();

	UFUNCTION()
	void OnButtonClickQuit();
};
