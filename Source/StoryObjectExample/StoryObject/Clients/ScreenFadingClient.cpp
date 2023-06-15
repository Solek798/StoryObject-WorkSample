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
	{
		Fade(true);
		return {EStoryObjectPhase::PRE_START, {}};
	}

	return INVALID_INFO;
}

FStoryObjectClientPhaseTicketInfo UScreenFadingClient::OnFadeInStart()
{
	if (FadeInStart)
	{
		Fade(false);
		return {EStoryObjectPhase::RUNNING, {}};
	}

	return INVALID_INFO;
}

FStoryObjectClientPhaseTicketInfo UScreenFadingClient::OnFadeOutFinish()
{
	if (FadeOutFinish)
	{
		Fade(true);
		return {EStoryObjectPhase::PRE_FINISH, {}};
	}
	
	return INVALID_INFO;
}

FStoryObjectClientPhaseTicketInfo UScreenFadingClient::OnFadeInFinish()
{
	if (FadeInFinish)
	{
		Fade(false);
		return {EStoryObjectPhase::FINISHED, {}};
	}
	
	return INVALID_INFO;
}

FStoryObjectClientPhaseTicketInfo UScreenFadingClient::OnFadeOutStop()
{
	if (FadeOutStop)
	{
		Fade(true);
		return {EStoryObjectPhase::PRE_STOP, {}};
	}
	
	return INVALID_INFO;
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


