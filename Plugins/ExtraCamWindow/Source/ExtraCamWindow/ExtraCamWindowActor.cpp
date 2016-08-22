
#include "IExtraCamWindowPlugin.h"

#include "ExtraCamWindowActor.h"

AExtraCamWindowActor::AExtraCamWindowActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AExtraCamWindowActor::BeginPlay()
{
	if (!ExtraCamWindowEnabled)
		return;

	CamManager = nullptr;

	UWorld* World = this->GetWorld();

	if (World)
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = *Iterator;
			if (PlayerController && PlayerController->PlayerCameraManager)
				CamManager = PlayerController->PlayerCameraManager;
			
		}
	}

	if (CamManager == nullptr && LockToPlayerCam == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("ExtraCamWindow Error: No Player Camera Manager found!")));
		ExtraCamWindowEnabled = false;
		return;
	}

	if(LockToPlayerCam == false)
		GetCameraComponent()->bLockToHmd = false;
	

	auto renderer = FSlateApplication::Get().GetRenderer();

	if(LockResToMainWindow)
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
	.UseScissor(false)
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

		if (mainViewportSize.X != newViewportSize.X || mainViewportSize.Y != newViewportSize.Y)
			SceneViewport->ResizeFrame(mainViewportSize.X, mainViewportSize.Y, EWindowMode::Windowed, 0, 0);
	}));


	if (this->GetWorld()->WorldType == EWorldType::Game)
		StandaloneGame = true;
	else
		StandaloneGame = false;

	// initialize everything before we call base class so that in blueprint beginplay everything is ready

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

	if (LockToPlayerCam)
	{
		SceneViewport->Draw();
		return;
	}

	// adjust camera
	AActor* oldTarget = nullptr;
	oldTarget = CamManager->GetViewTarget();

	CamManager->SetViewTarget(this);

	CamManager->UpdateCamera(0.0f);
		
	SceneViewport->Draw();

	// reset camera
	CamManager->SetViewTarget(oldTarget);
	

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
