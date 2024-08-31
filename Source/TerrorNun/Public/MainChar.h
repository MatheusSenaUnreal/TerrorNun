#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sound/SoundWave.h"
#include "MainChar.generated.h"

UCLASS()
class TERRORNUN_API AMainChar : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ItemMeshChar;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Sensi", meta = (AllowPrivateAccess = "true", ClampMin = 0, Units = "X"))
	float SensiY{ 45.f };

	UPROPERTY(EditDefaultsOnly, Category = "Sensi", meta = (AllowPrivateAccess = "true", ClampMin = 0, Units = "X"))
	float SensiX{ 45.f };

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpotLightComponent* Flashlight;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundWave* Noise;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundWave* JumpScare;

	FTimerHandle Timer;

	UPROPERTY(EditDefaultsOnly, Category = "Main Hud")
	TSubclassOf<class UUserWidget> MainHud;

	UPROPERTY()
	class UUserWidget* CurrentWidget;
public:
	AActor* RefItemInHand;
	bool bItemInHand{false};

public:
	AMainChar();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class ALocker* Locker;
	UPROPERTY(BlueprintReadWrite)
	bool bIsHidden{ false };
private:
	void InteractActor();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);
	void DropItem();
	void CrouchPressed()	;
	/*void Hidden();*/
public:
	UFUNCTION(BlueprintCallable)
	void RestartCurrentLevel();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};