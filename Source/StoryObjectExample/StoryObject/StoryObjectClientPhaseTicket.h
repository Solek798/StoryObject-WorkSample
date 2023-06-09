// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StoryObjectEnums.h"
#include "StoryObjectClientPhaseTicket.generated.h"

class UStoryObjectClientPhaseTicket;


DECLARE_DYNAMIC_DELEGATE(FClientFinishedPhase);
DECLARE_DYNAMIC_DELEGATE_OneParam(FTicketStateChanged, UStoryObjectClientPhaseTicket*, ticket);

USTRUCT(BlueprintType)
struct FStoryObjectClientPhaseTicketCollection
{
	GENERATED_BODY()

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UStoryObjectClientPhaseTicket*> Tickets;
};

USTRUCT(BlueprintType)
struct FStoryObjectClientPhaseTicketInfo
{
	GENERATED_BODY()

	FStoryObjectClientPhaseTicketInfo();
	FStoryObjectClientPhaseTicketInfo(EStoryObjectPhase endPhase, TArray<UActorComponent*> dependencies);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EStoryObjectPhase EndPhase;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UObject*> Dependencies;
};

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
	UObject* m_client;

	UPROPERTY()
	FStoryObjectClientPhaseTicketInfo m_info;

	bool m_clientFinishedPhase;
	bool m_neverHadAnyDependencies;

public:
	UStoryObjectClientPhaseTicket();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UObject* GetClient() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EStoryObjectPhase GetEndPhase() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UObject*> GetDependencies() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasClientFinishedPhase() const;

	UFUNCTION(BlueprintCallable)
	FClientFinishedPhase RegisterClient(UObject* client);
	UFUNCTION(BlueprintCallable)
	void SetTicketInfo(FStoryObjectClientPhaseTicketInfo info);
	
	UFUNCTION(BlueprintCallable)
	void FulfillDependency(UObject* dependency);

protected:
	UFUNCTION()
	void OnClientFinishedPhase();
};

