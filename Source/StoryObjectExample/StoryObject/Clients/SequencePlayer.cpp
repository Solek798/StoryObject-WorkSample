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

UDependentStoryObjectClientTicket* USequencePlayer::GetPhaseTicket_Implementation(EStoryObjectPhase phase)
{
	if (phase != EStoryObjectPhase::RUNNING)
		return nullptr;
	
	CREATE_TICKET()

	ASSIGN_SAME_PHASE_NO_DEP(phase);
	
	return ticket;
}

void USequencePlayer::Execute_Implementation(EStoryObjectPhase currentPhase, const FClientDone& phaseCallback)
{
	m_timerCallbackWasCalled = false;
	m_ownerCallback = phaseCallback;

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
}

bool USequencePlayer::IsClientDone_Implementation(const EStoryObjectPhase currentPhase)
{
	if (currentPhase != EStoryObjectPhase::RUNNING)
		return true;
	
	return m_timerCallbackWasCalled;
}

void USequencePlayer::OnCloseToSequenceEnd()
{
	m_timerCallbackWasCalled = true;
	
	if (m_ownerCallback.IsBound())
		m_ownerCallback.Execute(this);
}




