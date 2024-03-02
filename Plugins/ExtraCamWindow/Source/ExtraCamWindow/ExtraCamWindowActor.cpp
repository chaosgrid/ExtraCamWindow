
#include "IExtraCamWindowPlugin.h"

#include "ExtraCamWindowActor.h"
AExtraCamWindowActor::AExtraCamWindowActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ExtraCamComponent = CreateDefaultSubobject<UExtraCamWindowComponent>(TEXT("ExtraCamWindowComponent"));
	RootComponent = ExtraCamComponent;
}

