// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryObject.generated.h"


class AStoryObjectTrigger;
UENUM(BlueprintType)
enum class EStoryObjectPhase
{
	IDLE,
	PRE_START,
	START,
	POST_START,
	RUNNING,
	PRE_STOP,
	STOP,
	POST_STOP,
	PRE_FINISH,
	FINISH,
	POST_FINISH
};

UCLASS(Abstract)
class STORYOBJECTEXAMPLE_API AStoryObject : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	EStoryObjectPhase m_currentPhase;

	UPROPERTY(VisibleAnywhere)
	TArray<AStoryObjectTrigger*> m_triggerTokens;
	
public:
	AStoryObject();

	UFUNCTION(BlueprintCallable)
	void Activate();

	UFUNCTION(BlueprintCallable)
	void Stop();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EStoryObjectPhase GetCurrentPhase() const;

	UFUNCTION(BlueprintCallable)
	void AddTriggerToken(AStoryObjectTrigger* trigger);
	UFUNCTION(BlueprintCallable)
	void RemoveTriggerToken(AStoryObjectTrigger* trigger);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsArealStoryObject() const;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Start();

	UFUNCTION()
	void Finish();

	void EvaluateTriggerState();
};
