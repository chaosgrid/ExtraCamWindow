
#pragma once
#include "Engine/SceneCapture2D.h"
#include "RenderWidget.h"
#include "Camera/CameraComponent.h"
#include "ExtraCamWindowActor.generated.h"

UCLASS(meta = (PrioritizeCategories = "ExtraCamWindow"))
class AExtraCamWindowActor : public ASceneCapture2D
{
	GENERATED_BODY()

public:

	AExtraCamWindowActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtraCamWindow")
	bool ExtraCamWindowEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtraCamWindow")
	bool LockToPlayerCam = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtraCamWindow")
	bool LockMouseFocusToExtraWindow = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtraCamWindow")
	TEnumAsByte<EMouseCursor::Type> CursorInWindow = EMouseCursor::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtraCamWindow")
	FText WindowTitle = FText::FromString(TEXT("Extra Cam Window"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtraCamWindow")
	FVector2D InitialWindowRes = FVector2D(1280, 720);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtraCamWindow")
	bool LockResToMainWindow = false;

	/** If OnBeginPlay the Scene Capture Component should use the Editor Visualizer Camera Properties, such as Camera Settings and Post Process Settings*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtraCamWindow")
	bool bUseEditorVisualizerProperties = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtraCamWindow")
	TEnumAsByte<EWindowMode::Type> WindowMode = EWindowMode::Windowed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtraCamWindow")
	UCameraComponent* EditorVisualizer = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "ExtraCamWindow")
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
