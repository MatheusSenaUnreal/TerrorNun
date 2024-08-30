#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/TimelineComponent.h"
#include "Locker.generated.h"

UCLASS()
class TERRORNUN_API ALocker : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	ALocker();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* Locker;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* LockerDoor;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* BoxCollision;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	USceneComponent* PlayerLocationWhenExit;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere);
	UCurveFloat* CurveFloat;
	
	FTimeline Timeline;
private:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void InteractIdle(AMainChar* Character) override;

public:
	void OpenLocker(AMainChar* Char);

	APlayerController* PC;
	AMainChar* Ch;
	bool bIsOverlap{ false };

	void SetInputDisable();
};
