
#include "IExtraCamWindowPlugin.h"

#include "ExtraCamWindowActor.h"
#include "IExtraCamWindowPlugin.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Brushes/SlateImageBrush.h"
#include "Camera/CameraComponent.h"


AExtraCamWindowActor::AExtraCamWindowActor()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCaptureComponent2D()->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	EditorVisualizer = CreateDefaultSubobject<UCameraComponent>(TEXT("EditorVisualizer"));
	EditorVisualizer->bIsEditorOnly = true;
	EditorVisualizer->SetupAttachment(GetCaptureComponent2D());
}


void AExtraCamWindowActor::BeginPlay()
{
	if (!ExtraCamWindowEnabled)
		return;
	// TODO: Add default Widget with Image for render target
	auto renderer = FSlateApplication::Get().GetRenderer();

	if (LockResToMainWindow)
		GEngine->GameViewport->GetViewportSize(InitialWindowRes);


	SAssignNew(ExtraWindow, SWindow)
		.ClientSize(InitialWindowRes)
		.SizingRule(LockResToMainWindow ? ESizingRule::FixedSize : ESizingRule::UserSized)
		.UseOSWindowBorder(true)
		.Title(WindowTitle)
		.FocusWhenFirstShown(LockMouseFocusToExtraWindow)
		.CreateTitleBar(true);

	FSlateApplication::Get().AddWindow(ExtraWindow.ToSharedRef(), true);

	ViewportOverlayWidget = SNew(SOverlay);

	TSharedRef<SGameLayerManager> LayerManagerRef = SNew(SGameLayerManager)
		.SceneViewport(GEngine->GameViewport->GetGameViewport())
		.Visibility(EVisibility::Visible)
		.Cursor(CursorInWindow)
		[
			ViewportOverlayWidget.ToSharedRef()
		];

	TSharedPtr<SViewport> Viewport = SNew(SViewport)
		.RenderDirectlyToWindow(false) // true crashes some stuff because HMDs need the rendertarget tex for distortion etc..
		.EnableGammaCorrection(false)
		.EnableStereoRendering(false) // not displaying on an HMD
		.Cursor(CursorInWindow)
		[
			LayerManagerRef
		];


	SceneViewport = MakeShareable(new FSceneViewport(GEngine->GameViewport, Viewport));


	Viewport->SetViewportInterface(SceneViewport.ToSharedRef());


	ExtraWindow->SetContent(Viewport.ToSharedRef());
	ExtraWindow->ShowWindow();

	SceneViewport->CaptureMouse(LockMouseFocusToExtraWindow);
	SceneViewport->SetUserFocus(LockMouseFocusToExtraWindow);
	SceneViewport->LockMouseToViewport(LockMouseFocusToExtraWindow);

	// the window and some stuff gets initialized by ticking slate, otherwise we get a thread-related crash in packaged builds..
	FSlateApplication::Get().Tick();

	SceneViewport->SetOnSceneViewportResizeDel(FOnSceneViewportResize::CreateLambda([this](FVector2D newViewportSize)
	{
		if (LockResToMainWindow == false)
			return;

		// deny any window resolution change in the child windows

		FVector2D mainViewportSize;
		GEngine->GameViewport->GetViewportSize(mainViewportSize);

		if (mainViewportSize.X != newViewportSize.X || mainViewportSize.Y != newViewportSize.Y) {
			SceneViewport->ResizeFrame(mainViewportSize.X, mainViewportSize.Y, EWindowMode::Windowed);
			GetCaptureComponent2D()->TextureTarget->ResizeTarget(mainViewportSize.X, mainViewportSize.Y);
		}

	}));


	if (this->GetWorld()->WorldType == EWorldType::Game)
		StandaloneGame = true;
	else
		StandaloneGame = false;

	GetCaptureComponent2D()->TextureTarget = UKismetRenderingLibrary::CreateRenderTarget2D(this, InitialWindowRes.X, InitialWindowRes.Y);
	RenderTargetWidget = CreateWidget<URenderWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), URenderWidget::StaticClass());
	RenderTargetWidget->TextureTarget->SetBrushResourceObject(GetCaptureComponent2D()->TextureTarget);
	AddWidgetToExtraCam(RenderTargetWidget);

	if (bUseEditorVisualizerProperties) {
		GetCaptureComponent2D()->ProjectionType = EditorVisualizer->ProjectionMode;
		GetCaptureComponent2D()->FOVAngle = EditorVisualizer->FieldOfView;
		GetCaptureComponent2D()->OrthoWidth = EditorVisualizer->OrthoWidth;
		GetCaptureComponent2D()->CustomNearClippingPlane = EditorVisualizer->OrthoNearClipPlane;
		GetCaptureComponent2D()->PostProcessSettings = EditorVisualizer->PostProcessSettings;
	}
	Super::BeginPlay();
}

bool AExtraCamWindowActor::AddWidgetToExtraCam(UUserWidget* inWidget, int32 zOrder /* = -1 */)
{
	if (ViewportOverlayWidget.IsValid() == false)
		return false;

	ViewportOverlayWidget->AddSlot(zOrder)
		[
			inWidget->TakeWidget()
		];

	return true;
}

bool AExtraCamWindowActor::RemoveWidgetFromExtraCam(UUserWidget* inWidget)
{
	if (ViewportOverlayWidget.IsValid() == false)
		return false;

	return ViewportOverlayWidget->RemoveSlot(inWidget->TakeWidget());
}

void AExtraCamWindowActor::Tick(float delta)
{
	Super::Tick(delta);

	if (!ExtraCamWindowEnabled)
		return;

	if (LockToPlayerCam) {
		APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
		if (playerController != nullptr)
		{
			FVector camLoc;
			FRotator camRot;
			playerController->GetPlayerViewPoint(camLoc, camRot);
			SetActorLocationAndRotation(camLoc, camRot);
		}
	}
}

void AExtraCamWindowActor::BeginDestroy()
{
	Super::BeginDestroy();

	if (!ExtraCamWindowEnabled)
		return;

	if (ExtraWindow.Get() != nullptr)
	{
		if (StandaloneGame == false)
			ExtraWindow->RequestDestroyWindow();
		else
			ExtraWindow->DestroyWindowImmediately();
	}


}
