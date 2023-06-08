// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenFadingClient.h"

#include "StoryObjectExample/MyCustomGameInstance.h"
#include "StoryObjectExample/WDG_FadeScreen.h"
#include "StoryObjectExample/StoryObject/StoryObject.h"


UScreenFadingClient::UScreenFadingClient()
	: m_isInFadingOperation(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}

UDependentStoryObjectClientTicket* UScreenFadingClient::GetPhaseTicket_Implementation(const EStoryObjectPhase phase)
{
	CHECK_PHASE_VALID(phase, nullptr)
	
	CREATE_TICKET()

	ASSIGN_SAME_PHASE_NO_DEP_if(phase, phase == EStoryObjectPhase::PRE_START && FadeOutStart)
	ASSIGN_SAME_PHASE_NO_DEP_if(phase, phase == EStoryObjectPhase::RUNNING && FadeInStart)
	ASSIGN_SAME_PHASE_NO_DEP_if(phase, phase == EStoryObjectPhase::PRE_STOP && FadeOutStop)
	ASSIGN_SAME_PHASE_NO_DEP_if(phase, phase == EStoryObjectPhase::PRE_FINISH && FadeOutFinish)
	ASSIGN_SAME_PHASE_NO_DEP_if(phase, phase == EStoryObjectPhase::FINISHED && FadeInFinish)
	
	return ticket;
}

void UScreenFadingClient::Execute_Implementation(const EStoryObjectPhase currentPhase, const FClientDone& phaseCallback)
{
	CHECK_PHASE_VALID(currentPhase)

	m_ownerCallback = phaseCallback;

	const UMyCustomGameInstance* gameInstance = GetOwner()->GetGameInstance<UMyCustomGameInstance>();
	if (gameInstance == nullptr)
		return;

	m_isInFadingOperation = true;

	const bool fadeToBlack = currentPhase == EStoryObjectPhase::PRE_START || currentPhase == EStoryObjectPhase::PRE_STOP ||
											 currentPhase == EStoryObjectPhase::PRE_FINISH;

	FFadeComplete fadeCallback;
	fadeCallback.BindDynamic(this, &UScreenFadingClient::UScreenFadingClient::OnFadeDone);
	
	gameInstance->FadeScreen->Fade(fadeToBlack, FadeTime, fadeCallback);
}

bool UScreenFadingClient::IsClientDone_Implementation(EStoryObjectPhase currentPhase)
{
	return !m_isInFadingOperation;
}


void UScreenFadingClient::BeginPlay()
{
	Super::BeginPlay();
	
}

void UScreenFadingClient::OnFadeDone()
{
	m_isInFadingOperation = false;
	
	if (m_ownerCallback.IsBound())
		m_ownerCallback.Execute(this);
}


