// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObject.h"

#include "StoryObjectExample/MyCustomGameInstance.h"


AStoryObject::AStoryObject()
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
}

EStoryObjectPhase AStoryObject::GetCurrentPhase() const
{
	return m_currentPhase;
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
}


