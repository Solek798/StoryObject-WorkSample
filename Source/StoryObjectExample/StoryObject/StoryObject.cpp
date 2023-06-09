// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObject.h"
#include "StoryObjectClient.h"
#include "StoryObjectClientPhaseTicket.h"
#include "StoryObjectEnums.h"
#include "StoryObjectExample/MyCustomGameInstance.h"



AStoryObject::AStoryObject()
	: m_currentPhase(EStoryObjectPhase::IDLE)
{
	PrimaryActorTick.bCanEverTick = false;

	// TODO(FK): Maybe make that const somehow?
	m_phaseOrder = {
		{EStoryObjectPhase::IDLE, EStoryObjectPhase::QUEUED},
		{EStoryObjectPhase::QUEUED, EStoryObjectPhase::PRE_START},
		{EStoryObjectPhase::PRE_START, EStoryObjectPhase::STARTING},
		{EStoryObjectPhase::STARTING, EStoryObjectPhase::RUNNING},
		{EStoryObjectPhase::RUNNING, EStoryObjectPhase::PRE_FINISH},
		{EStoryObjectPhase::PRE_FINISH, EStoryObjectPhase::FINISHING},
		{EStoryObjectPhase::FINISHING, EStoryObjectPhase::FINISHED},
		{EStoryObjectPhase::FINISHED, EStoryObjectPhase::IDLE},
		{EStoryObjectPhase::PRE_STOP, EStoryObjectPhase::STOPPING},
		{EStoryObjectPhase::STOPPING, EStoryObjectPhase::FINISHING}
	};
}

void AStoryObject::Activate()
{
	const UMyCustomGameInstance* gameInstance = GetGameInstance<UMyCustomGameInstance>();
	if (gameInstance == nullptr || gameInstance->StoryDirector == nullptr)
		return;
	
	FStoryObjectStartCall startCall;
	startCall.BindDynamic(this, &AStoryObject::Start);

	AdvancePhase();

	gameInstance->StoryDirector->EnqueueStoryObject(startCall);
}

void AStoryObject::Stop()
{
	if (GetCurrentPhase() != EStoryObjectPhase::RUNNING)
		return;
	
	SetCurrentPhase(EStoryObjectPhase::PRE_STOP);

	ExecutePhase(GetCurrentPhase());
}

EStoryObjectPhase AStoryObject::GetCurrentPhase() const
{
	return m_currentPhase;
}

void AStoryObject::AddTriggerToken(AStoryObjectTrigger* trigger)
{
	m_triggerTokens.Add(trigger);

	EvaluateTriggerState();
}

void AStoryObject::RemoveTriggerToken(AStoryObjectTrigger* trigger)
{
	m_triggerTokens.Remove(trigger);

	EvaluateTriggerState();
}

bool AStoryObject::IsArealStoryObject() const
{
	// TODO(FK): NOT IMPLEMENTED!
	return false;
}

void AStoryObject::BeginPlay()
{
	Super::BeginPlay();
}

void AStoryObject::Start()
{
	AdvancePhase();
}

void AStoryObject::Finish()
{
	OnStoryObjectFinished.Broadcast();
}

void AStoryObject::SetCurrentPhase(const EStoryObjectPhase newPhase)
{
	m_currentPhase = newPhase;
}

void AStoryObject::EvaluateTriggerState()
{
	// If there is more than one trigger and Object is mot running attempt to start it
	if (m_triggerTokens.Num() > 0 && GetCurrentPhase() == EStoryObjectPhase::IDLE)
	{
		Activate();
		return;
	}

	// if this is an 'Areal-StoryObject', there is no trigger and the object is running stop it.
	if (IsArealStoryObject() && m_triggerTokens.Num() <= 0 && GetCurrentPhase() != EStoryObjectPhase::IDLE)
	{
		Stop();
		return;
	}
}

TArray<UObject*> AStoryObject::FetchAllClients() const
{
	TArray<UObject*> retVal;

	TArray<UActorComponent*> clientComponents = GetComponentsByInterface(UStoryObjectClient::StaticClass());
	for (UActorComponent* client : clientComponents)
		retVal.Add(client);

	TArray<AActor*> attachedActors;
	GetAttachedActors(attachedActors);
	for (AActor* attachedActor : attachedActors)
	{
		if (attachedActor->Implements<UStoryObjectClient>())
			retVal.Add(attachedActor);
	}

	return retVal;
}


void AStoryObject::ExecutePhase(const EStoryObjectPhase phase)
{
	TArray<UObject*> clients = FetchAllClients();

	for (UObject* client : clients)
		ExecutePhaseOnClient(phase, client);

	CheckIfObjectIsReadyToAdvancePhase();
}

void AStoryObject::ExecutePhaseOnClient(const EStoryObjectPhase phase, UObject* client)
{
	UStoryObjectClientPhaseTicket* ticket = IStoryObjectClient::Execute_ExecutePhase(client, phase);

	if (ticket != nullptr && !ticket->HasClientFinishedPhase())
	{
		ticket->OnClientFinishedPhaseEvent.BindDynamic(this, &AStoryObject::OnClientFinishedPhase);
		ticket->OnClientDependenciesFulfilledEvent.BindDynamic(this, &AStoryObject::OnClientDependenciesFulfilled);

		m_remainingTickets.FindOrAdd(ticket->GetEndPhase()).Tickets.Add(ticket);
	}
}

void AStoryObject::OnClientFinishedPhase(UStoryObjectClientPhaseTicket* clientTicket)
{
	const EStoryObjectPhase currentPhase = GetCurrentPhase();
	FStoryObjectClientPhaseTicketCollection test = m_remainingTickets.FindChecked(currentPhase);
	TArray<UStoryObjectClientPhaseTicket*> test2 = test.Tickets;
	
	for (UStoryObjectClientPhaseTicket* ticket : test2)
		ticket->FulfillDependency(clientTicket->GetClient());

	m_remainingTickets[currentPhase].Tickets.Remove(clientTicket);

	CheckIfObjectIsReadyToAdvancePhase();
}

void AStoryObject::OnClientDependenciesFulfilled(UStoryObjectClientPhaseTicket* clientTicket)
{
	ExecutePhaseOnClient(GetCurrentPhase(), clientTicket->GetClient());
}

void AStoryObject::AdvancePhase()
{
	const EStoryObjectPhase oldPhase = GetCurrentPhase();
	
	if (oldPhase == EStoryObjectPhase::FINISHED)
	{
		Finish();

		if (!Repeatable)
			return;
	}

	const EStoryObjectPhase newPhase = m_phaseOrder[oldPhase];
	SetCurrentPhase(newPhase);

	// if Object is 'back to waiting state' make sure it's not trying to further progress the phase-chain
	if (newPhase == EStoryObjectPhase::IDLE || newPhase == EStoryObjectPhase::QUEUED)
		return;

	ExecutePhase(newPhase);
}

void AStoryObject::CheckIfObjectIsReadyToAdvancePhase()
{
	const EStoryObjectPhase currentPhase = GetCurrentPhase();
	
	if (!m_remainingTickets.Contains(currentPhase) || m_remainingTickets[currentPhase].Tickets.Num() <= 0)
		AdvancePhase();
}


