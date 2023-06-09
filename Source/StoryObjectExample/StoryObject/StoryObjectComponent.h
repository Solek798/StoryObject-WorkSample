// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryObjectClient.h"
#include "StoryObjectClientPhaseTicket.h"
#include "Components/ActorComponent.h"
#include "StoryObjectComponent.generated.h"

#define DECLARE_PHASE_IMPLEMENTATION(phase, function)\
FPhaseImplementation phaseImplementation##phase;\
phaseImplementation##phase.BindDynamic(this, function);\
m_phaseImplementations.Add(EStoryObjectPhase::phase, phaseImplementation##phase);

UCLASS(Abstract, Blueprintable, BlueprintType)
class STORYOBJECTEXAMPLE_API UStoryObjectComponent : public UActorComponent, public IStoryObjectClient
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<EStoryObjectPhase, FPhaseImplementation> m_phaseImplementations;

	UPROPERTY()
	FClientFinishedPhase m_onClientFinishedPhaseEvent;
	
public:
	UStoryObjectComponent();

	virtual UStoryObjectClientPhaseTicket* ExecutePhase_Implementation(EStoryObjectPhase currentPhase) override;

	UFUNCTION(BlueprintCallable)
	void NotifyTaskIsDone() const;
};
