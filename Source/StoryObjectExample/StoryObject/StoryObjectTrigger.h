// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "StoryObjectTrigger.generated.h"

class AStoryObject;

UCLASS(Abstract)
class STORYOBJECTEXAMPLE_API AStoryObjectTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	AStoryObjectTrigger();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AStoryObject* GetParentStoryObject() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp,
		int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp,
		int32 otherBodyIndex);
};
