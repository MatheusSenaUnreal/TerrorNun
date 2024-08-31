#include "MainChar.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "InteractInterface.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MainHud.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Components/CapsuleComponent.h"
#include "NunCharacterAI.h"
#include "Locker.h"
#include "NunAIController.h"
#include "NunCharacterAI.h"

AMainChar::AMainChar()
{
	PrimaryActorTick.bCanEverTick = true;

	RefItemInHand = nullptr;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(RootComponent);

	Flashlight = CreateDefaultSubobject<USpotLightComponent>(FName("Flashlight"));
	Flashlight->SetupAttachment(Camera);

	ItemMeshChar = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMesh"));
	ItemMeshChar->SetupAttachment(Camera);
}

void AMainChar::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (MainHud)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainHud);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainChar::OnOverlapBegin);
		}
	}
}

void AMainChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetComponentRotation().Vector() * 1000.f);
	FHitResult Res;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Res, Start, End, ECollisionChannel::ECC_Visibility, Params);

	if (bHit)
	{
	//	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f, 0, 3.f);

		if (IInteractInterface* Interface = Cast<IInteractInterface>(Res.GetActor()))
		{
				UMainHud* H = Cast<UMainHud>(CurrentWidget);
			if (MainHud)
			{
				if (H)
				{
					H->UpdateCrosshairInteract();
				}
			}
		}
		else
		{
			UMainHud* H = Cast<UMainHud>(CurrentWidget);
			if (MainHud)
			{
				if (H)
				{
					H->UpdateCrosshair();
				}
			}
		}
	}
}

void AMainChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainChar::InteractActor);
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainChar::DropItem);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainChar::CrouchPressed);


	PlayerInputComponent->BindAxis("MoveForward", this, &AMainChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainChar::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &AMainChar::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainChar::LookUp);

}


void AMainChar::InteractActor()
{
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetComponentRotation().Vector() * 200.f);
	FHitResult Res;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Res, Start, End, ECollisionChannel::ECC_Visibility, Params);

	if (bHit)
	{
		//DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, 2.f, 0, 3.f);

		if (IInteractInterface* Interface = Cast<IInteractInterface>(Res.GetActor()))
		{
			Interface->Interact(this, Res);
		}
	}
}

void AMainChar::MoveForward(float Value)
{
	if (Value != 0.f)
	{
	AddMovementInput(this->GetActorForwardVector(), Value);
	}
}

void AMainChar::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		AddMovementInput(this->GetActorRightVector(), Value);
	}
}

void AMainChar::LookUp(float Value)
{
	AddControllerPitchInput(Value * SensiY * GetWorld()->GetDeltaSeconds());
}

void AMainChar::LookRight(float Value)
{
	AddControllerYawInput(Value * SensiX * GetWorld()->GetDeltaSeconds());
}

void AMainChar::DropItem()
{
	if (bItemInHand)
	{
		// Obter a rotação da câmera do jogador
		FVector LaunchDirection = GetControlRotation().Vector(); // Direção para onde a câmera está olhando

		// Calcular o impulso
		FVector Impulse = LaunchDirection * 9900.f;

		// Calcular a posição de spawn à frente da câmera
		FVector SpawnLocation = GetActorLocation() + LaunchDirection * 10.0f; // Ajuste a distância conforme necessário

		// Definir a rotação de spawn para coincidir com a rotação da câmera
		FRotator SpawnRotation = GetControlRotation();

		FActorSpawnParameters SpawnParams;
		AActor* Ref = GetWorld()->SpawnActor<AActor>(RefItemInHand->GetClass(), SpawnLocation, SpawnRotation, SpawnParams);

		if (Ref)
		{
			UStaticMeshComponent* RefMesh = Ref->FindComponentByClass<UStaticMeshComponent>();
			if (RefMesh)
			{
				RefMesh->AddImpulse(Impulse); // Aplicar o impulso na direção da câmera
			}
		}

		RefItemInHand = nullptr;

		ItemMeshChar->SetStaticMesh(nullptr);
		bItemInHand = false;
	}


	}

void AMainChar::CrouchPressed()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}
//
//void AMainChar::Hidden()
//{
//	// Array para armazenar os atores sobrepostos
//	TArray<AActor*> OverlappingActors;
//
//	// Pega todos os atores que estão sobrepostos com a cápsula
//	GetCapsuleComponent()->GetOverlappingActors(OverlappingActors);
//
//	// Loop para iterar sobre cada ator sobreposto
//	for (AActor* Actor : OverlappingActors)
//	{
//		// Verifica se o ator implementa a interface desejada
//
//
//		if (IInteractInterface* Interface = Cast<IInteractInterface>(Actor))
//		{
//			Interface->InteractIdle(this);
//		}
//
//
//	}
//}


void AMainChar::RestartCurrentLevel()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName(*World->GetName()), true);
	}
}

void AMainChar::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ALocker::StaticClass()))
	{
		Locker = Cast<ALocker>(OtherActor);
		if (Locker)
		{
			UE_LOG(LogTemp, Warning, TEXT("ola"));
		}
	}
	if (OtherActor != nullptr && OtherActor != this)
	{

		ANunCharacterAI* NunChar = Cast<ANunCharacterAI>(OtherActor);
			if (NunChar)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpScare, GetActorLocation());

				GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMainChar::RestartCurrentLevel, 0.5f, false);

			}

	}
}
