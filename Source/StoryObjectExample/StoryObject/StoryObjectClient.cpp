// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObjectClient.h"

#include "StoryObject.h"


// Add default functionality here for any IStoryObjectClient functions that are not pure virtual.

UDependentStoryObjectClientTicket::UDependentStoryObjectClientTicket()
	: m_client(nullptr)
	, m_startPhase(EStoryObjectPhase::IDLE)
	, m_endPhase(EStoryObjectPhase::IDLE)
{ /* if created with this constructor this object is basically invalid and will always be fulfilled when asked */ }

UDependentStoryObjectClientTicket::UDependentStoryObjectClientTicket(UActorComponent* client,
                                                                     const EStoryObjectPhase startPhase,
                                                                     const EStoryObjectPhase endPhase,
                                                                     const TArray<UActorComponent*> dependencies)
	: m_client(client)
	, m_startPhase(startPhase)
	, m_endPhase(endPhase)
	, m_dependencies(dependencies)
{ }

void UDependentStoryObjectClientTicket::FulfillDependency(UActorComponent* dependency)
{
	m_dependencies.Remove(dependency);
}

bool UDependentStoryObjectClientTicket::IsTicketFulfilled() const
{
	return m_dependencies.Num() <= 0 || m_client == nullptr;
}

bool UDependentStoryObjectClientTicket::ShouldTicketBeFulfilledThisPhase(const EStoryObjectPhase currentPhase) const
{
	return m_endPhase == currentPhase;
}

UActorComponent* UDependentStoryObjectClientTicket::GetClient() const
{
	return m_client;
}
