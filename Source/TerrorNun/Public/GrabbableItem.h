#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "GrabbableItem.generated.h"

UCLASS()
class TERRORNUN_API AGrabbableItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* ItemMesh;

public:	
	AGrabbableItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AMainChar* Character, const FHitResult& Hit) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FVector ItemSizeinHand;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundWave* Noise;

	bool bHit{ true };

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,  FVector NormalImpulse, const FHitResult& Hit);
};
