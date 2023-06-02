// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObject.h"
#include "StoryObjectClient.h"
#include "StoryObjectExample/MyCustomGameInstance.h"



AStoryObject::AStoryObject()
	: m_currentPhase(EStoryObjectPhase::IDLE)
{
	PrimaryActorTick.bCanEverTick = false;

	// TODO(FK): Maybe make that const somehow?
	m_phaseOrder = {
		{EStoryObjectPhase::IDLE, EStoryObjectPhase::PRE_START},
		{EStoryObjectPhase::PRE_START, EStoryObjectPhase::STARTING},
		{EStoryObjectPhase::STARTING, EStoryObjectPhase::RUNNING},
		{EStoryObjectPhase::RUNNING, EStoryObjectPhase::PRE_FINISH},
		{EStoryObjectPhase::PRE_FINISH, EStoryObjectPhase::FINISHING},
		{EStoryObjectPhase::FINISHING, EStoryObjectPhase::FINISHED},
		{EStoryObjectPhase::PRE_STOP, EStoryObjectPhase::STOPPING},
		{EStoryObjectPhase::STOPPING, EStoryObjectPhase::FINISHING},
	};
}

void AStoryObject::Activate()
{
	const UMyCustomGameInstance* gameInstance = GetGameInstance<UMyCustomGameInstance>();
	if (gameInstance == nullptr || gameInstance->StoryDirector == nullptr)
		return;
	
	FStoryObjectStartCall startCall;
	startCall.BindDynamic(this, &AStoryObject::Start);

	gameInstance->StoryDirector->EnqueueStoryObject(startCall);
}

void AStoryObject::Stop()
{
	UE_LOG(LogTemp, Error, TEXT("Stop it allready!"))
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
	ProceedToNextPhase();
}

void AStoryObject::Finish()
{
	UE_LOG(LogTemp, Error, TEXT("IT IS FINISHING!"))
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

void AStoryObject::FetchTicketsForPhase(const EStoryObjectPhase phase)
{
	// Get all ClientComponents of this StoryObject
	TArray<UActorComponent*> clientComponents = GetComponentsByInterface(UStoryObjectClient::StaticClass());

	// Go through all clients and Get their ticket for the currentPhase
	for (const UActorComponent* clientComponent : clientComponents)
		m_remainingTickets.Add(IStoryObjectClient::Execute_GetPhaseTicket(clientComponent, phase));
}

void AStoryObject::ExecutePhase(const EStoryObjectPhase phase)
{
	FetchTicketsForPhase(phase);
	
	for (const UDependentStoryObjectClientTicket* ticket : m_remainingTickets)
	{
		if (ticket->IsTicketFulfilled())
		{
			UActorComponent* client = ticket->GetClient();

			FClientDone callback;
			callback.BindDynamic(this, &AStoryObject::OnClientDone);
			
			IStoryObjectClient::Execute_Execute(client, phase, callback);
		}
	}

	EvaluateTickets();
}

void AStoryObject::OnClientDone(UActorComponent* client)
{
	for (UDependentStoryObjectClientTicket* ticket : m_remainingTickets)
		ticket->FulfillDependency(client);

	EvaluateTickets();
}

void AStoryObject::EvaluateTickets()
{
	const bool areUnfulfilledTicketsLeft = m_remainingTickets.ContainsByPredicate([this](
		const UDependentStoryObjectClientTicket* ticket)
	{
		return !ticket->IsTicketFulfilled() && ticket->ShouldTicketBeFulfilledThisPhase(GetCurrentPhase());
	});

	// if there are no tickets left unfulfilled go to next regular phase
	if (!areUnfulfilledTicketsLeft)
		ProceedToNextPhase();
}

void AStoryObject::ProceedToNextPhase()
{
	// remove all tickets except the ones for long term operations
	m_remainingTickets.RemoveAll([this](
		const UDependentStoryObjectClientTicket* ticket)
	{
		return ticket->ShouldTicketBeFulfilledThisPhase(GetCurrentPhase());
	});
	
	SetCurrentPhase(m_phaseOrder[GetCurrentPhase()]);

	ExecutePhase(GetCurrentPhase());
}


