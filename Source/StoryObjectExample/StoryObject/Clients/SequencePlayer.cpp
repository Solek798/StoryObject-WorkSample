// Fill out your copyright notice in the Description page of Project Settings.


#include "SequencePlayer.h"

#include "LevelSequencePlayer.h"
#include "ScreenFadingClient.h"
#include "MovieSceneSequencePlayer.h"
#include "StoryObjectExample/StoryObject/StoryObject.h"


USequencePlayer::USequencePlayer()
	: m_timerCallbackWasCalled(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}

FStoryObjectClientPhaseTicketInfo USequencePlayer::PlaySequence()
{
	m_timerCallbackWasCalled = false;

	const UScreenFadingClient* screenFader = Cast<UScreenFadingClient>(GetOwner()->GetComponentByClass(UScreenFadingClient::StaticClass()));
	float callbackTimeDeduction = 0.0f;

	if (screenFader != nullptr)
		callbackTimeDeduction = screenFader->FadeTime - 0.05f;
	
	FTimerDelegate callback;
	callback.BindUObject(this, &USequencePlayer::OnCloseToSequenceEnd);

	const float sequenceLength = Sequence->GetSequencePlayer()->GetDuration().AsSeconds();
	const float callbackTime = sequenceLength - callbackTimeDeduction;

	GetOwner()->GetWorldTimerManager().SetTimer(m_handle, callback, callbackTime, false);

	Sequence->GetSequencePlayer()->Play();

	return {EStoryObjectPhase::RUNNING, {}};
}

void USequencePlayer::BeginPlay()
{
	Super::BeginPlay();

	DECLARE_PHASE_IMPLEMENTATION(RUNNING, &USequencePlayer::PlaySequence)
}

void USequencePlayer::OnCloseToSequenceEnd()
{
	m_timerCallbackWasCalled = true;
	
	NotifyTaskIsDone();
}




