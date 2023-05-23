// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObject.h"

#include "StoryObjectExample/MyCustomGameInstance.h"


AStoryObject::AStoryObject()
	: m_currentPhase(EStoryObjectPhase::IDLE)
{
	PrimaryActorTick.bCanEverTick = false;
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
	UE_LOG(LogTemp, Error, TEXT("IT IS STARTING!"))
}

void AStoryObject::Finish()
{
	UE_LOG(LogTemp, Error, TEXT("IT IS FINISHING!"))
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


