// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraCamViewport.h"
#include "InputCoreTypes.h"

FReply SExtraCamViewport::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) {
	if (KeyEvent.GetKey() == FKey(EKeys::LeftAlt.GetFName()) || KeyEvent.GetKey() == FKey(EKeys::RightAlt.GetFName())) {
		bIsAltDown = true;
	}
	if (bIsAltDown && KeyEvent.GetKey() == EKeys::Enter) {
		OnWindowModeChanged.Broadcast();
	}
	return SViewport::OnKeyDown(MyGeometry, KeyEvent);
}
