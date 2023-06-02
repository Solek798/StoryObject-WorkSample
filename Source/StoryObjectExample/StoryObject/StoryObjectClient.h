// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StoryObjectClient.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FClientDone, UActorComponent*, client);

UCLASS(BlueprintType)
class UDependentStoryObjectClientTicket : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UActorComponent* m_client;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EStoryObjectPhase m_startPhase;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EStoryObjectPhase m_endPhase;

	UPROPERTY()
	TArray<UActorComponent*> m_dependencies;

public:
	UDependentStoryObjectClientTicket();
	UDependentStoryObjectClientTicket(UActorComponent* client, EStoryObjectPhase startPhase, EStoryObjectPhase endPhase, TArray<UActorComponent*> dependencies);
	
	UFUNCTION(BlueprintCallable)
	void FulfillDependency(UActorComponent* dependency);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsTicketFulfilled() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool ShouldTicketBeFulfilledThisPhase(EStoryObjectPhase currentPhase) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UActorComponent* GetClient() const;
};


UINTERFACE(BlueprintType, Blueprintable)
class UStoryObjectClient : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STORYOBJECTEXAMPLE_API IStoryObjectClient
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	UDependentStoryObjectClientTicket* GetPhaseTicket(EStoryObjectPhase phase) const;

	UFUNCTION(BlueprintNativeEvent)
	void Execute(EStoryObjectPhase currentPhase, const FClientDone& phaseCallback);
};
