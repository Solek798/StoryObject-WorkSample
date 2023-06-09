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

UCLASS(Abstract)
class STORYOBJECTEXAMPLE_API AStoryObject : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FPhaseChanged OnPhaseChanged;
	
	UPROPERTY(BlueprintAssignable)
	FStoryObjectFinished OnStoryObjectFinished;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Repeatable;
	
protected:
	UPROPERTY(VisibleAnywhere)
	EStoryObjectPhase m_currentPhase;

	UPROPERTY(VisibleAnywhere)
	TArray<AStoryObjectTrigger*> m_triggerTokens;

	UPROPERTY(VisibleAnywhere)
	TMap<EStoryObjectPhase, FStoryObjectClientPhaseTicketCollection> m_remainingTickets;

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

	void Finish();

	void SetCurrentPhase(EStoryObjectPhase newPhase);

	void EvaluateTriggerState();

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
