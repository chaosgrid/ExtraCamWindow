
#pragma once
#include "ExtraCamWindowComponent.h"
#include "Camera/CameraComponent.h"
#include "ExtraCamWindowActor.generated.h"

UCLASS(hidecategories = (Collision, Material, Attachment, Actor), Blueprintable, ClassGroup = "ExtraCamWindow")
class EXTRACAMWINDOW_API AExtraCamWindowActor : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UExtraCamWindowComponent> ExtraCamComponent;
private:
	
};
