// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObjectClientPhaseTicket.h"

#include "StoryObjectExample/StoryObject/StoryObject.h"


UStoryObjectClientPhaseTicket::UStoryObjectClientPhaseTicket()
	: m_client(nullptr)
	, m_endPhase(EStoryObjectPhase::IDLE)
{ }

UActorComponent* UStoryObjectClientPhaseTicket::GetClient() const
{
	return m_client;
}

EStoryObjectPhase UStoryObjectClientPhaseTicket::GetEndPhase() const
{
	return m_endPhase;
}

TArray<UActorComponent*> UStoryObjectClientPhaseTicket::GetDependencies() const
{
	return m_dependencies;
}

FClientFinishedPhase UStoryObjectClientPhaseTicket::RegisterClient(UActorComponent* client, const EStoryObjectPhase endPhase,
																   const TArray<UActorComponent*> dependencies)
{
	m_client = client;
	m_endPhase = endPhase;
	m_dependencies = dependencies;

	FClientFinishedPhase onClientFinishedPhaseEvent;
	onClientFinishedPhaseEvent.BindDynamic(this, &UStoryObjectClientPhaseTicket::OnClientFinishedPhase);

	return onClientFinishedPhaseEvent;
}

void UStoryObjectClientPhaseTicket::FulfillDependency(UActorComponent* dependency)
{
	m_dependencies.Remove(dependency);

	if (m_dependencies.Num() <= 0 && OnClientDependenciesFulfilledEvent.IsBound())
		OnClientDependenciesFulfilledEvent.Execute(this);
}

void UStoryObjectClientPhaseTicket::OnClientFinishedPhase()
{
	if (OnClientFinishedPhaseEvent.IsBound())
		OnClientFinishedPhaseEvent.Execute(this);
}
