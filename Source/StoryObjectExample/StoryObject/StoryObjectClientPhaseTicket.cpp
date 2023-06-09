// Fill out your copyright notice in the Description page of Project Settings.

#include "StoryObjectClientPhaseTicket.h"
#include "StoryObjectEnums.h"


FStoryObjectClientPhaseTicketInfo::FStoryObjectClientPhaseTicketInfo()
	: EndPhase(EStoryObjectPhase::NONE)
{ }

FStoryObjectClientPhaseTicketInfo::FStoryObjectClientPhaseTicketInfo(const EStoryObjectPhase endPhase,
                                                                     const TArray<UActorComponent*> dependencies)
	: EndPhase(endPhase)
	, Dependencies(dependencies)
{ }

UStoryObjectClientPhaseTicket::UStoryObjectClientPhaseTicket()
	: m_client(nullptr)
	, m_clientFinishedPhase(false)
	, m_neverHadAnyDependencies(true)
{ }

UActorComponent* UStoryObjectClientPhaseTicket::GetClient() const
{
	return m_client;
}

EStoryObjectPhase UStoryObjectClientPhaseTicket::GetEndPhase() const
{
	return m_info.EndPhase;
}

TArray<UActorComponent*> UStoryObjectClientPhaseTicket::GetDependencies() const
{
	return m_info.Dependencies;
}

bool UStoryObjectClientPhaseTicket::HasClientFinishedPhase() const
{
	return m_clientFinishedPhase;
}

FClientFinishedPhase UStoryObjectClientPhaseTicket::RegisterClient(UActorComponent* client)
{
	m_client = client;

	FClientFinishedPhase onClientFinishedPhaseEvent;
	onClientFinishedPhaseEvent.BindDynamic(this, &UStoryObjectClientPhaseTicket::OnClientFinishedPhase);

	return onClientFinishedPhaseEvent;
}

void UStoryObjectClientPhaseTicket::SetTicketInfo(const FStoryObjectClientPhaseTicketInfo info)
{
	m_info = info;

	m_neverHadAnyDependencies = m_info.Dependencies.Num() <= 0;
}

void UStoryObjectClientPhaseTicket::FulfillDependency(UActorComponent* dependency)
{
	if (m_neverHadAnyDependencies)
    		return;
	
	m_info.Dependencies.Remove(dependency);

	if (m_info.Dependencies.Num() <= 0 && OnClientDependenciesFulfilledEvent.IsBound())
		OnClientDependenciesFulfilledEvent.Execute(this);
}

void UStoryObjectClientPhaseTicket::OnClientFinishedPhase()
{
	m_clientFinishedPhase = true;
	
	if (OnClientFinishedPhaseEvent.IsBound())
		OnClientFinishedPhaseEvent.Execute(this);
}
