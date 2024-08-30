#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <MainChar.h>
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class TERRORNUN_API IInteractInterface
{
	GENERATED_BODY()

public:
	virtual void Interact(AMainChar* Character, const FHitResult& Hit) {};
	virtual void InteractIdle(AMainChar* Character) {};

};
