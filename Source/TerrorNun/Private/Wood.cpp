#include "Wood.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"

AWood::AWood()
{
	PrimaryActorTick.bCanEverTick = true;

	Wood = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wood"));
	Wood->SetupAttachment(RootComponent);

	Nail1 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Nail1"));
	Nail1->SetupAttachment(Wood);

	Nail2 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Nail2"));
	Nail2->SetupAttachment(Wood);

	Nail3 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Nail3"));
	Nail3->SetupAttachment(Wood);

	Nail4 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Nail4"));
	Nail4->SetupAttachment(Wood);
}

void AWood::BeginPlay()
{
	Super::BeginPlay();

}

void AWood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWood::Interact(AMainChar* Character, const FHitResult& Hit)
{

	if (Hit.Component.IsValid())
	{
		UStaticMeshComponent* HitComp = Cast<UStaticMeshComponent>(Hit.Component);

		if (HitComp)
		{
			if (Character && Character->RefItemInHand)
			{
				if (Character->RefItemInHand->ActorHasTag("Crowbar"))
				{
					RemoveNail(HitComp, Nail1);
					RemoveNail(HitComp, Nail2);
					RemoveNail(HitComp, Nail3);
					RemoveNail(HitComp, Nail4);
				}
			}
		}
	}
}

void AWood::RemoveNail(UStaticMeshComponent* HitNail, UStaticMeshComponent* Nail)
{

	if (HitNail == Nail)
	{
		if (NailNum != 1)
		{

		NailNum--;
		HitNail->SetSimulatePhysics(true);
		HitNail->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, [HitNail]() {
			if (HitNail && !HitNail->IsPendingKill())
			{
				HitNail->DestroyComponent();
			}
			}, 1.f, false);
		}
		else 
		{
			Wood->SetSimulatePhysics(true);
			SetLifeSpan(1.f);
		}
	}
}


