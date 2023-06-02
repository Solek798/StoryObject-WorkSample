// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryObject.generated.h"

class AStoryObjectTrigger;
class UDependentStoryObjectClientTicket;


UENUM(BlueprintType)
enum class EStoryObjectPhase
{
	IDLE,
	PRE_START,
	STARTING,
	RUNNING,
	PRE_STOP,
	STOPPING,
	PRE_FINISH,
	FINISHING,
	FINISHED
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

	UPROPERTY(VisibleAnywhere)
	TArray<UDependentStoryObjectClientTicket*> m_remainingTickets;

	TMap<EStoryObjectPhase, EStoryObjectPhase> m_phaseOrder;
	
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

	void SetCurrentPhase(EStoryObjectPhase newPhase);

	void EvaluateTriggerState();

	void FetchTicketsForPhase(EStoryObjectPhase phase);

	UFUNCTION(BlueprintCallable)
	void ExecutePhase(EStoryObjectPhase phase);

	UFUNCTION()
	void OnClientDone(UActorComponent* client);

	void EvaluateTickets();

	void ProceedToNextPhase();
};
