﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StoryObjectExample/StoryObject/StoryObjectClient.h"
#include "LevelSequenceActor.h"
#include "SequencePlayer.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STORYOBJECTEXAMPLE_API USequencePlayer : public UActorComponent, public IStoryObjectClient
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ALevelSequenceActor* Sequence;

protected:
	FTimerHandle m_handle;

	UPROPERTY()
	FClientDone m_ownerCallback;

	bool m_timerCallbackWasCalled;

public:
	USequencePlayer();

	virtual UDependentStoryObjectClientTicket* GetPhaseTicket_Implementation(EStoryObjectPhase phase) override;
	virtual void Execute_Implementation(EStoryObjectPhase currentPhase, const FClientDone& phaseCallback) override;
	virtual bool IsClientDone_Implementation(EStoryObjectPhase currentPhase) override;

protected:
	UFUNCTION()
	void OnCloseToSequenceEnd();
};
