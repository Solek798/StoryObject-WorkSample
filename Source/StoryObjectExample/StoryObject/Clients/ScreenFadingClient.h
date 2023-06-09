// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryObjectExample/StoryObject/StoryObjectComponent.h"
#include "ScreenFadingClient.generated.h"


UCLASS()
class STORYOBJECTEXAMPLE_API UScreenFadingClient : public UStoryObjectComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FadeTime;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeOutStart;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeInStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeOutFinish;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeInFinish;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeOutStop;

protected:
	bool m_isInFadingOperation;
	
public:
	UScreenFadingClient();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	FStoryObjectClientPhaseTicketInfo OnFadeOutStart();
	UFUNCTION()
	FStoryObjectClientPhaseTicketInfo OnFadeInStart();

	UFUNCTION()
	FStoryObjectClientPhaseTicketInfo OnFadeOutFinish();
	UFUNCTION()
	FStoryObjectClientPhaseTicketInfo OnFadeInFinish();

	UFUNCTION()
	FStoryObjectClientPhaseTicketInfo OnFadeOutStop();

	void Fade(bool toBlack);
	
	UFUNCTION()
	void OnFadeDone();
};
