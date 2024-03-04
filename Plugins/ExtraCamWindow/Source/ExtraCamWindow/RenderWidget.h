// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "RenderWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXTRACAMWINDOW_API URenderWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderWidget")
	UCanvasPanel* CanvasPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenderWidget")
	UImage* TextureTarget;

	//virtual TSharedRef<SWidget> RebuildWidget();
};
