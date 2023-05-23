// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObjectTrigger.h"

#include "StoryObject.h"
#include "Components/ShapeComponent.h"


AStoryObjectTrigger::AStoryObjectTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
}

AStoryObject* AStoryObjectTrigger::GetParentStoryObject() const
{
	return Cast<AStoryObject>(GetAttachParentActor());
}

void AStoryObjectTrigger::BeginPlay()
{
	Super::BeginPlay();

	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AStoryObjectTrigger::OnBeginOverlap);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &AStoryObjectTrigger::OnEndOverlap);
}

void AStoryObjectTrigger::OnBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	AStoryObject* parentStoryObject = GetParentStoryObject();

	if (parentStoryObject == nullptr)
		return;

	parentStoryObject->AddTriggerToken(this);
}

void AStoryObjectTrigger::OnEndOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	AStoryObject* parentStoryObject = GetParentStoryObject();

	if (parentStoryObject == nullptr)
		return;

	parentStoryObject->RemoveTriggerToken(this);
}

