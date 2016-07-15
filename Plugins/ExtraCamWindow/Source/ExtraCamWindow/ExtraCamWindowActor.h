
#pragma once

#include "ExtraCamWindowActor.generated.h"

UCLASS()
class AExtraCamWindowActor : public ACameraActor
{
	GENERATED_BODY()

public:

	AExtraCamWindowActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ExtraCamWindowEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LockToPlayerCam = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LockMouseFocusToExtraWindow = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EMouseCursor::Type> CursorInWindow = EMouseCursor::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WindowTitle = FText::FromString(TEXT("Extra Cam Window"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D InitialWindowRes = FVector2D(1280, 720);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LockResToMainWindow = false;

private:

	void BeginDestroy() override;

	void BeginPlay();

	void Tick(float delta) override;

	TSharedPtr<FSceneViewport> SceneViewport = nullptr;
	TSharedPtr<SWindow> ExtraWindow = nullptr;

	FMinimalViewInfo POVtemp;

	APlayerCameraManager* CamManager;

	bool StandaloneGame = false;
	
};
