// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StoryObjectClientPhaseTicket.generated.h"

class UStoryObjectClientPhaseTicket;


DECLARE_DYNAMIC_DELEGATE(FClientFinishedPhase);
DECLARE_DYNAMIC_DELEGATE_OneParam(FTicketStateChanged, UStoryObjectClientPhaseTicket*, ticket);

/**
 * 
 */
UCLASS(BlueprintType)
class STORYOBJECTEXAMPLE_API UStoryObjectClientPhaseTicket : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FTicketStateChanged OnClientDependenciesFulfilledEvent;

	UPROPERTY(BlueprintReadWrite)
	FTicketStateChanged OnClientFinishedPhaseEvent;
	
protected:
	UPROPERTY()
	UActorComponent* m_client;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EStoryObjectPhase m_endPhase;

	UPROPERTY()
	TArray<UActorComponent*> m_dependencies;

public:
	UStoryObjectClientPhaseTicket();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UActorComponent* GetClient() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EStoryObjectPhase GetEndPhase() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UActorComponent*> GetDependencies() const;

	UFUNCTION(BlueprintCallable)
	FClientFinishedPhase RegisterClient(UActorComponent* client, EStoryObjectPhase endPhase, TArray<UActorComponent*> dependencies);
	
	UFUNCTION(BlueprintCallable)
	void FulfillDependency(UActorComponent* dependency);

protected:
	UFUNCTION()
	void OnClientFinishedPhase();
};

