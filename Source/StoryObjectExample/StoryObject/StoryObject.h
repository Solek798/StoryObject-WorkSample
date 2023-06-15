// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryObjectClientPhaseTicket.h"
#include "StoryObject.generated.h"

class UStoryObjectClientPhaseTicket;
class AStoryObjectTrigger;
class UDependentStoryObjectClientTicket;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPhaseChanged, EStoryObjectPhase, newPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStoryObjectFinished);

/*
 * 
 */
UCLASS(Abstract)
class STORYOBJECTEXAMPLE_API AStoryObject : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	// calls every time object changes it's phase before executing it
	FPhaseChanged OnPhaseChanged;
	
	UPROPERTY(BlueprintAssignable)
	// calls once object reaches FINISHED phase before executing it
	FStoryObjectFinished OnStoryObjectFinished;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// if set to true object will return to IDLE state after all FINISHED operations are done and allows to be re-triggered
	bool Repeatable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// if set to true object will be stopped when player leaves trigger
	bool IsSpatialObject;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// Object that gets activated when this object reaches FINISHED phase
	AStoryObject* FollowUpObject;
	
protected:
	UPROPERTY(VisibleAnywhere)
	EStoryObjectPhase m_currentPhase;

	UPROPERTY(VisibleAnywhere)
	TArray<AStoryObjectTrigger*> m_triggerTokens;

	UPROPERTY(VisibleAnywhere)
	// map where all tickets get sorted by end-phase
	TMap<EStoryObjectPhase, FStoryObjectClientPhaseTicketCollection> m_ticketRegister;

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
	
protected:
	UFUNCTION()
	void Start();

	void Finish();

	void SetCurrentPhase(EStoryObjectPhase newPhase);

	void EvaluateTriggerState();

	// filters all components and attached actors
	TArray<UObject*> FetchAllClients() const;

	UFUNCTION(BlueprintCallable)
	void ExecutePhase(EStoryObjectPhase phase);
	void ExecutePhaseOnClient(EStoryObjectPhase phase, UObject* client);

	UFUNCTION()
	void OnClientFinishedPhase(UStoryObjectClientPhaseTicket* clientTicket);
	UFUNCTION()
	void OnClientDependenciesFulfilled(UStoryObjectClientPhaseTicket* clientTicket);
	
	void AdvancePhase();

	void CheckIfObjectIsReadyToAdvancePhase();
};
