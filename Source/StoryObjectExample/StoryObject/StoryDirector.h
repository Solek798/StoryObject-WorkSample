// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryDirector.generated.h"


DECLARE_DYNAMIC_DELEGATE(FStoryObjectStartCall);

UCLASS(Abstract)
class STORYOBJECTEXAMPLE_API AStoryDirector : public AActor
{
	GENERATED_BODY()

public:
	AStoryDirector();

	UFUNCTION(BlueprintCallable)
	void EnqueueStoryObject(FStoryObjectStartCall startCall);
	
protected:
	virtual void BeginPlay() override;
};
