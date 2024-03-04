// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SViewport.h"


DECLARE_MULTICAST_DELEGATE(FOnWindowModeChangedSignature);
/**
 * 
 */
class EXTRACAMWINDOW_API SExtraCamViewport : public SViewport
{

public:
	FOnWindowModeChangedSignature OnWindowModeChanged;
private:
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;

	bool bIsAltDown = false;
};
