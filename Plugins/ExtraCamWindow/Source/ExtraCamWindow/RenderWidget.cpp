// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"

bool URenderWidget::Initialize() {
	bool bSuperInitialized = Super::Initialize();
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	if (!HasAnyFlags(RF_ClassDefaultObject)) {
		CanvasPanel= WidgetTree->ConstructWidget<UCanvasPanel>();
		WidgetTree->RootWidget = CanvasPanel;
		TextureTarget = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("TextureTarget"));
		UCanvasPanelSlot* ImageSlot = CanvasPanel->AddChildToCanvas(TextureTarget);
		ImageSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
		ImageSlot->SetOffsets(FMargin(0.0f, 0.0f));
	}
	return bSuperInitialized;
}

void URenderWidget::NativeConstruct() {
	Super::NativeConstruct();

}
