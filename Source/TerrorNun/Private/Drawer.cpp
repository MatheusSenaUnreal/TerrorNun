#include "Drawer.h"
#include "Kismet/GameplayStatics.h"

ADrawer::ADrawer()
{
	PrimaryActorTick.bCanEverTick = true;

	DrawerUnit = CreateDefaultSubobject<UStaticMeshComponent>(FName("DrawerUnit"));
	DrawerUnit->SetupAttachment(RootComponent);

	Drawer1 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Drawer1"));
	Drawer1->SetupAttachment(DrawerUnit);

	Drawer2 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Drawer2"));
	Drawer2->SetupAttachment(DrawerUnit);

	Drawer3 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Drawer3"));
	Drawer3->SetupAttachment(DrawerUnit);

	Drawer4 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Drawer4"));
	Drawer4->SetupAttachment(DrawerUnit);


}

void ADrawer::BeginPlay()
{
	Super::BeginPlay();
	
	if (CurveFloat)
	{
		FOnTimelineFloat Timeb;
		Timeb.BindDynamic(this, &ADrawer::OpenDrawer);
		Timeline.AddInterpFloat(CurveFloat, Timeb);
	}

}

void ADrawer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);

}

void ADrawer::Interact(AMainChar* Character, const FHitResult& Hit)
{
	if (Hit.Component.IsValid())
	{
		UStaticMeshComponent* HitComp = Cast<UStaticMeshComponent>(Hit.Component);

		if (HitComp)
		{
			DrawerNum(HitComp, Drawer1);
			DrawerNum(HitComp, Drawer2);
			DrawerNum(HitComp, Drawer3);
			DrawerNum(HitComp, Drawer4);
		}
	}
}

void ADrawer::PlaySoundWave(UWorld* World, USoundWave* SoundWave, const FVector& Location)
{
	if (World && SoundWave)
	{
		UGameplayStatics::PlaySoundAtLocation(World, SoundWave, Location);
	}
}

void ADrawer::OpenDrawer(float Value)
{
	FVector Loc = FVector(90 * Value, 0.f, 0.f);
	Drawer->SetRelativeLocation(Loc);
}

void ADrawer::DrawerNum(UStaticMeshComponent* Dr, UStaticMeshComponent* Dr2)
{
	if (Dr == Dr2)
	{
		if (bIsClosed)
		{
			Drawer = Dr;
			Timeline.Play();
			PlaySoundWave(GetWorld(), OpenDrawerSound, GetActorLocation());
		}
		else
		{
			Timeline.Reverse();
			PlaySoundWave(GetWorld(), OpenDrawerSound, GetActorLocation());
		}
		bIsClosed = !bIsClosed;

	}
}

	
		