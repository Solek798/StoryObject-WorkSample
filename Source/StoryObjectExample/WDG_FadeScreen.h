// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WDG_FadeScreen.generated.h"


DECLARE_DYNAMIC_DELEGATE(FFadeComplete);

/**
 * 
 */
UCLASS()
class STORYOBJECTEXAMPLE_API UWDG_FadeScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FFadeComplete m_currentOperationCallback;
	
public:
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="callback"))
	void Fade(bool toBlack, float fadeTime, const FFadeComplete& callback);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool IsFading() const;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnFadeRequested(bool toBlack, float fadeTime);

	UFUNCTION(BlueprintCallable)
	void FireCallback();
};
