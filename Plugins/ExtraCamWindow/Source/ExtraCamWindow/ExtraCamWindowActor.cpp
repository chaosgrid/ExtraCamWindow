
#include "IExtraCamWindowPlugin.h"

#include "ExtraCamWindowActor.h"
AExtraCamWindowActor::AExtraCamWindowActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ExtraCamComponent = CreateDefaultSubobject<UExtraCamWindowComponent>(TEXT("ExtraCamWindowComponent"));
	RootComponent = ExtraCamComponent;

	EditorVisualizer = CreateDefaultSubobject<UCameraComponent>(TEXT("EditorVisualizer"));
	EditorVisualizer->SetupAttachment(RootComponent);
	EditorVisualizer->bIsEditorOnly = true;
	EditorVisualizer->SetHiddenInGame(true);
}

void AExtraCamWindowActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	EditorVisualizer->SetProjectionMode(ExtraCamComponent->ProjectionType);
	EditorVisualizer->SetFieldOfView(ExtraCamComponent->FOVAngle);
	EditorVisualizer->SetOrthoWidth(ExtraCamComponent->OrthoWidth);
	EditorVisualizer->PostProcessBlendWeight = ExtraCamComponent->PostProcessBlendWeight;
	EditorVisualizer->PostProcessSettings = ExtraCamComponent->PostProcessSettings;


}
