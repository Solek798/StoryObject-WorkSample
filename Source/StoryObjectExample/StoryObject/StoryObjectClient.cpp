// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObjectClient.h"

#include "StoryObject.h"


// Add default functionality here for any IStoryObjectClient functions that are not pure virtual.

UDependentStoryObjectClientTicket::UDependentStoryObjectClientTicket()
	: m_client(nullptr)
	, m_endPhase(EStoryObjectPhase::IDLE)
{ }

void UDependentStoryObjectClientTicket::SetTicketData(UActorComponent* client, const EStoryObjectPhase endPhase,
													  const TArray<UActorComponent*> dependencies)
{
	m_client = client;
	m_endPhase = endPhase;
	m_dependencies = dependencies;
}

void UDependentStoryObjectClientTicket::FulfillDependency(UActorComponent* dependency)
{
	m_dependencies.Remove(dependency);
}

bool UDependentStoryObjectClientTicket::IsTicketFulfilled(const EStoryObjectPhase currentPhase) const
{
	const bool clientInvalid = !IsValid();
	const bool hasDep = HasAnyRemainingDependencies();
	const bool isDone = IStoryObjectClient::Execute_IsClientDone(m_client, currentPhase);
	const bool shouldFulfill = ShouldTicketBeFulfilledThisPhase(currentPhase);
	
	return clientInvalid || (!hasDep && isDone && shouldFulfill);
}

bool UDependentStoryObjectClientTicket::HasAnyRemainingDependencies() const
{
	return m_dependencies.Num() > 0;
}

bool UDependentStoryObjectClientTicket::ShouldTicketBeFulfilledThisPhase(const EStoryObjectPhase currentPhase) const
{
	return m_endPhase == currentPhase;
}

bool UDependentStoryObjectClientTicket::IsValid() const
{
	return m_client != nullptr;
}

UActorComponent* UDependentStoryObjectClientTicket::GetClient() const
{
	return m_client;
}
