// Fill out your copyright notice in the Description page of Project Settings.


#include "WDG_FadeScreen.h"

void UWDG_FadeScreen::Fade(const bool toBlack, const float fadeTime, const FFadeComplete& callback)
{
	m_currentOperationCallback = callback;

	OnFadeRequested(toBlack, fadeTime);
}

void UWDG_FadeScreen::FireCallback()
{
	if (m_currentOperationCallback.IsBound())
		m_currentOperationCallback.ExecuteIfBound();
}
