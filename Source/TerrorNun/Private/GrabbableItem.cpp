#include "GrabbableItem.h"
#include "Components/StaticMeshComponent.h"
#include <MainChar.h>
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Hearing.h"

AGrabbableItem::AGrabbableItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMesh"));
	
}

void AGrabbableItem::BeginPlay()
{
	Super::BeginPlay();
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ItemMesh->SetCollisionProfileName(TEXT("BlockAll")); // Certifique-se de que o perfil está configurado corretamente
	ItemMesh->SetUseCCD(true); // Ativa a Detecção Contínua de Colisão
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	ItemMesh->OnComponentHit.AddDynamic(this, &AGrabbableItem::OnHit);
}

void AGrabbableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrabbableItem::Interact(AMainChar* Character, const FHitResult& Hit)
{
	if (Character != nullptr)
	{
		if (Character->bItemInHand)
		{
			FVector SpawnLocation = Character->GetActorLocation();
			FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnParams;
			GetWorld()->SpawnActor<AActor>(Character->RefItemInHand->GetClass(), SpawnLocation, SpawnRotation, SpawnParams);
			
			if (ItemMesh)
			{
				// Define a malha estática no ItemMesh
				Character->ItemMeshChar->SetStaticMesh(ItemMesh->GetStaticMesh());
				Character->RefItemInHand = this;
			}
		}
		else
		{
			if (ItemMesh)
			{
				Character->ItemMeshChar->SetStaticMesh(ItemMesh->GetStaticMesh());
				Character->RefItemInHand = this;
				Character->bItemInHand = true;
			}
		}
		Destroy();
	}
}

void AGrabbableItem::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bHit)
	{
		bHit = false;
		if (Noise)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Noise, GetActorLocation());
			UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 700.f, this, -1.f, TEXT("noise"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Noise"));
		}
	}
}
