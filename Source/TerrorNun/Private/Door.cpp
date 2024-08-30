#include "Door.h"
#include "Components/StaticMeshComponent.h"
#include "MainChar.h"
#include "Kismet/GameplayStatics.h"
#include "NunCharacterAI.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("DoorFrame"));
	DoorFrame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door"));
	Door->SetupAttachment(DoorFrame);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(DoorFrame);
	BoxCollision->SetCollisionProfileName(TEXT("Trigger"));
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);

	DoorFrame->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	DoorFrame->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Block);

	Door->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	Door->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Block);
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);

}

void ADoor::Interact(AMainChar* Character, const FHitResult& Hit)
{
	RefChar = Character;

	if(GetTagKey("RedDoor"))
	{
		bKeyMissing = false;
	}
	
	if (bKeyMissing == true)
	{
		if (CurveFloatClosed)
		{
			FOnTimelineFloat Timeb;
			Timeb.BindDynamic(this, &ADoor::OpenDoor);
			Timeline.AddInterpFloat(CurveFloatClosed, Timeb);
		}
		Timeline.PlayFromStart();
		OpenDoorSide();
		PlaySoundWave(GetWorld(), ClosedDoor, GetActorLocation());
		return;
	}
	else 
	{
		if (CurveFloatOpen)
		{
			FOnTimelineFloat Timep;
			Timep.BindDynamic(this, &ADoor::OpenDoor);
			Timeline.AddInterpFloat(CurveFloatOpen, Timep);

		if (bIsClosed)
		{
			Timeline.Play();
			OpenDoorSide();
			PlaySoundCue(GetWorld(), OpenDoorCue, GetActorLocation());
			bIsClosed = !bIsClosed;

		}
		else
		{
		
			Timeline.Reverse();
			PlaySoundWave(GetWorld(), ClosedDoor, GetActorLocation());
			bIsClosed = !bIsClosed;

		}
		}
	}
}

void ADoor::OpenDoor(float Value)
{

	 angle = bSideDoor ? 90 : -90;
	FRotator Rot = FRotator(0.f, angle * Value, 0.f);
	Door->SetRelativeRotation(Rot);
}

void ADoor::OpenDoorSide()
{
	if (RefChar)
	{
	FVector CharFWD = RefChar->GetActorForwardVector();
	FVector DoorFWD = GetActorForwardVector();
	bSideDoor = FVector::DotProduct(CharFWD, DoorFWD) >= 0;
	}
	// true frente a frente a porta 90
	// false atras da porta -90
}


void ADoor::OpenDoorSideAI()
{

	if (Nun)
	{
		FVector CharFWD = Nun->GetActorForwardVector();
		FVector DoorFWD = GetActorForwardVector();
		bSideDoor = FVector::DotProduct(CharFWD, DoorFWD) >= 0;
	}
	// true frente a frente a porta 90
	// false atras da porta -90
}
bool ADoor::GetTagKey(FName Tag) const
{
	if (RefChar && RefChar->RefItemInHand)
	{
		return RefChar->RefItemInHand->ActorHasTag(Tag);
	}
	return false;
}

void ADoor::PlaySoundWave(UWorld* World, USoundWave* SoundWave, const FVector& Location)
{
	if (World && SoundWave)
	{
		UGameplayStatics::PlaySoundAtLocation(World, SoundWave, Location);
	}
}

void ADoor::PlaySoundCue(UWorld* World, USoundCue* SoundCue, const FVector& Location)
{
	if (World && SoundCue)
	{
		UGameplayStatics::PlaySoundAtLocation(World, SoundCue, Location);
	}
}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ANunCharacterAI::StaticClass()))
	{
		Nun = Cast<ANunCharacterAI>(OtherActor);

		if (Nun)
		{
			if (CurveFloatOpen)
			{
				FOnTimelineFloat Timep;
				Timep.BindDynamic(this, &ADoor::OpenDoor);
				Timeline.AddInterpFloat(CurveFloatOpen, Timep);

				if (bIsClosed)
				{
					Timeline.Play();
					OpenDoorSideAI();
					PlaySoundCue(GetWorld(), OpenDoorCue, GetActorLocation());
					bIsClosed = !bIsClosed;

				}
			}
		}
	}
}

void ADoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ANunCharacterAI::StaticClass()))
	{
		if (Nun)
		{
			UE_LOG(LogTemp, Warning, TEXT("assd"));
			if (bIsClosed == false)
			{
				Timeline.Reverse();
				PlaySoundWave(GetWorld(), ClosedDoor, GetActorLocation());
				bIsClosed = !bIsClosed;
			}
		}
	}
}
