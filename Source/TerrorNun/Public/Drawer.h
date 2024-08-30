#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/TimelineComponent.h"
#include "Sound/SoundWave.h"
#include "Drawer.generated.h"

class UStaticMeshComponent;

UCLASS()
class TERRORNUN_API ADrawer : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	ADrawer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* DrawerUnit;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Drawer1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Drawer2;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Drawer3;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Drawer4;

	UStaticMeshComponent* Drawer;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundWave* OpenDrawerSound;

	UPROPERTY(EditAnywhere);
	UCurveFloat* CurveFloat;

	FTimeline Timeline;

	bool bIsClosed = true;

private:
	virtual void Interact(AMainChar* Character, const FHitResult& Hit) override;
	void PlaySoundWave(UWorld* World, USoundWave* SoundWave, const FVector& Location);

	UFUNCTION()
	void OpenDrawer(float Value);

	void DrawerNum(UStaticMeshComponent* Dr, UStaticMeshComponent* Dr2);
};
