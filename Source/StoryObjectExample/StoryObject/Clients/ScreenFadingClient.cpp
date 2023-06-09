// Fill out your copyright notice in the Description page of Project Settings.

#include "ScreenFadingClient.h"

#include "StoryObjectExample/MyCustomGameInstance.h"

UScreenFadingClient::UScreenFadingClient()
	: m_isInFadingOperation(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UScreenFadingClient::BeginPlay()
{
	Super::BeginPlay();

	DECLARE_PHASE_IMPLEMENTATION(PRE_START, &UScreenFadingClient::OnFadeOutStart)
	DECLARE_PHASE_IMPLEMENTATION(RUNNING, &UScreenFadingClient::OnFadeInStart)
	DECLARE_PHASE_IMPLEMENTATION(PRE_FINISH, &UScreenFadingClient::OnFadeOutFinish)
	DECLARE_PHASE_IMPLEMENTATION(FINISHED, &UScreenFadingClient::OnFadeInFinish)
	DECLARE_PHASE_IMPLEMENTATION(PRE_STOP, &UScreenFadingClient::OnFadeOutStop)
}

FStoryObjectClientPhaseTicketInfo UScreenFadingClient::OnFadeOutStart()
{
	if (FadeOutStart)
		Fade(true);

	return {};
}

FStoryObjectClientPhaseTicketInfo UScreenFadingClient::OnFadeInStart()
{
	if (FadeInStart)
		Fade(false);

	return {};
}

FStoryObjectClientPhaseTicketInfo UScreenFadingClient::OnFadeOutFinish()
{
	if (FadeOutFinish)
		Fade(true);
	
	return {};
}

FStoryObjectClientPhaseTicketInfo UScreenFadingClient::OnFadeInFinish()
{
	if (FadeInFinish)
		Fade(false);
	
	return {};
}

FStoryObjectClientPhaseTicketInfo UScreenFadingClient::OnFadeOutStop()
{
	if (FadeOutStop)
		Fade(true);
	
	return {};
}

void UScreenFadingClient::Fade(const bool toBlack)
{
	const UMyCustomGameInstance* gameInstance = GetOwner()->GetGameInstance<UMyCustomGameInstance>();
	if (gameInstance == nullptr)
		return;

	m_isInFadingOperation = true;

	FFadeComplete fadeCallback;
	fadeCallback.BindDynamic(this, &UScreenFadingClient::UScreenFadingClient::OnFadeDone);
	
	gameInstance->FadeScreen->Fade(toBlack, FadeTime, fadeCallback);
}

void UScreenFadingClient::OnFadeDone()
{
	m_isInFadingOperation = false;
	
	NotifyTaskIsDone();
}


