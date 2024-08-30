#include "Locker.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MainChar.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "NunAIController.h"
#include "NunCharacterAI.h"

ALocker::ALocker()
{
	PrimaryActorTick.bCanEverTick = true;

	Locker = CreateDefaultSubobject<UStaticMeshComponent>(FName("Locker"));
	Locker->SetupAttachment(RootComponent);

	LockerDoor = CreateDefaultSubobject<UStaticMeshComponent>(FName("LockerDoor"));
	LockerDoor->SetupAttachment(Locker);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(Locker);

	PlayerLocationWhenExit = CreateDefaultSubobject<USceneComponent>(FName("LocationExit"));
	PlayerLocationWhenExit->SetupAttachment(Locker);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(Locker);


	
}

void ALocker::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALocker::OnOverlapBegin);

	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ALocker::OnOverlapEnd);
}

void ALocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
}

void ALocker::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AMainChar::StaticClass()))
	{
		bIsOverlap = true;
	}
}

void ALocker::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(AMainChar::StaticClass()))
	{
		bIsOverlap = false;
	}
}

void ALocker::InteractIdle(AMainChar* Character)
{
	OpenLocker(Character);
}

void ALocker::OpenLocker(AMainChar* Char)
{
	Ch = Char;

		PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PC)
		{
			if (Char->bIsHidden == true)
			{
				Char->SetActorHiddenInGame(false);
				Char->SetActorEnableCollision(true);
				PC->SetIgnoreLookInput(false);
				PC->SetViewTargetWithBlend(Char, 0.8f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
				UE_LOG(LogTemp, Warning, TEXT("saiu"));

			}
			else
			{
				ANunCharacterAI* NunChar = Cast<ANunCharacterAI>(UGameplayStatics::GetActorOfClass(GetWorld(), ANunCharacterAI::StaticClass()));

				if (NunChar)
				{
					ANunAIController* NunC = Cast<ANunAIController>(NunChar->GetController());
					if (NunC)
					{
						NunC->SetHiddenForAI();
						Char->bIsHidden = true;
					}
				}
				Char->SetActorHiddenInGame(true);
				Char->SetActorEnableCollision(false);
				Char->SetActorLocation(PlayerLocationWhenExit->GetComponentLocation());
				PC->SetIgnoreLookInput(true);
				PC->SetViewTargetWithBlend(this, 0.8f, EViewTargetBlendFunction::VTBlend_Linear, 0.0f, false);
				Char->bIsHidden = true;

				UE_LOG(LogTemp, Warning, TEXT("entrou"));

				/*FTimerHandle Timer;
				GetWorld()->GetTimerManager().SetTimer(Timer, this, &ALocker::SetInputDisable, 1.f, false);*/
			}
		}
	}



void ALocker::SetInputDisable()
{
	Ch->EnableInput(PC);
}

