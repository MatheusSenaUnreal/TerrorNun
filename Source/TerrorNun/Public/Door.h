#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/TimelineComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundWave.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Door.generated.h"

UCLASS()
class TERRORNUN_API ADoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundWave* ClosedDoor;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundWave* UnlockDoor;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* OpenDoorCue;

	FTimeline Timeline;

	UPROPERTY(EditAnywhere);
	UCurveFloat* CurveFloatOpen;

	UPROPERTY(EditAnywhere);
	UCurveFloat* CurveFloatClosed;

	bool bIsClosed = true;
	bool bSideDoor;

	UFUNCTION()
	void OpenDoor(float Value);

	void OpenDoorSide();
	

	void OpenDoorSideAI();

	bool GetTagKey(FName Tag) const;

	void PlaySoundWave(UWorld* World, USoundWave* SoundWave, const FVector& Location);
	void PlaySoundCue(UWorld* World, USoundCue* SoundCue, const FVector& Location);

	AMainChar* RefChar;
	class ANunCharacterAI* Nun;
	float angle;
public:	
	ADoor();
	UPROPERTY(EditAnywhere, Category = "IsClosed?")
	bool bKeyMissing{false};

protected:
	virtual void BeginPlay() override;
	

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(AMainChar* Character, const FHitResult& Hit) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
