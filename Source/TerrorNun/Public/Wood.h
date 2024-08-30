#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Wood.generated.h"

UCLASS()
class TERRORNUN_API AWood : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Wood;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Nail1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Nail2;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Nail3;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* Nail4;

	int32 NailNum{ 4 };

	bool bHit{ true };

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundWave* Noise;
public:	
	AWood();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	virtual void Interact(AMainChar* Character, const FHitResult& Hit) override;

	void RemoveNail(UStaticMeshComponent* Nail, UStaticMeshComponent* Nail2);

};
