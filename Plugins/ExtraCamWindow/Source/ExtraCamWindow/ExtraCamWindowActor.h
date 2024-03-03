
#pragma once
#include "Engine/SceneCapture2D.h"
#include "RenderWidget.h"
#include "ExtraCamWindowActor.generated.h"

UCLASS()
class AExtraCamWindowActor : public ASceneCapture2D
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URenderWidget* RenderTargetWidget = nullptr;

	UFUNCTION(BlueprintCallable, Category = "ExtraCamWindow")
	bool AddWidgetToExtraCam(UUserWidget* inWidget, int32 zOrder = -1);

	UFUNCTION(BlueprintCallable, Category = "ExtraCamWindow")
	bool RemoveWidgetFromExtraCam(UUserWidget* inWidget);

private:

	void BeginDestroy() override;

	void BeginPlay() override;

	void Tick(float delta) override;

	TSharedPtr<FSceneViewport> SceneViewport = nullptr;
	TSharedPtr<SWindow> ExtraWindow = nullptr;
	TSharedPtr<SOverlay> ViewportOverlayWidget = nullptr;
	
	bool StandaloneGame = false;
	
};
