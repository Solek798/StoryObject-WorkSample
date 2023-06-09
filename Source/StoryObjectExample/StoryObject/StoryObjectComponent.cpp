// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObjectComponent.h"
#include "StoryObjectClient.h"
#include "StoryObjectClientPhaseTicket.h"


UStoryObjectComponent::UStoryObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UStoryObjectClientPhaseTicket* UStoryObjectComponent::ExecutePhase_Implementation(const EStoryObjectPhase currentPhase)
{
	if (!m_phaseImplementations.Contains(currentPhase))
		return nullptr;

	UStoryObjectClientPhaseTicket* ticket = NewObject<UStoryObjectClientPhaseTicket>();
	FStoryObjectClientPhaseTicketInfo info {currentPhase, {}};

	m_onClientFinishedPhaseEvent = ticket->RegisterClient(this);

	if (m_phaseImplementations[currentPhase].IsBound())
	{
		const FStoryObjectClientPhaseTicketInfo implementationInfo = m_phaseImplementations[currentPhase].Execute();

		if (implementationInfo.EndPhase != EStoryObjectPhase::NONE)
			info = implementationInfo;
		else
			info.Dependencies = implementationInfo.Dependencies;
	}

	ticket->SetTicketInfo(info);

	return ticket;
}

void UStoryObjectComponent::NotifyTaskIsDone() const
{
	if (m_onClientFinishedPhaseEvent.IsBound())
		m_onClientFinishedPhaseEvent.Execute();
}


