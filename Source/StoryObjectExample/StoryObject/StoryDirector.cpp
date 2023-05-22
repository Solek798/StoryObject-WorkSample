// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryDirector.h"

#include "StoryObjectExample/MyCustomGameInstance.h"


AStoryDirector::AStoryDirector()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AStoryDirector::EnqueueStoryObject(const FStoryObjectStartCall startCall)
{
	// TODO(FK): Add actual Enqueue logic
	// starting object directly for now
	if (startCall.IsBound())
		startCall.Execute();
}

void AStoryDirector::BeginPlay()
{
	Super::BeginPlay();

	UMyCustomGameInstance* gameInstance = GetGameInstance<UMyCustomGameInstance>();
	if (gameInstance == nullptr)
		return;

	gameInstance->StoryDirector = this;
}

