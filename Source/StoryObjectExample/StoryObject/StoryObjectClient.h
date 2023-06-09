// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryObjectClientPhaseTicket.h"
#include "UObject/Interface.h"
#include "StoryObjectClient.generated.h"

class UStoryObjectClientPhaseTicket;

/*
 * Macro's to ease implementing StoryObjectClient code
 */

#define DECLARE_PHASE_RANGE(...) \
const TSet<EStoryObjectPhase> m_validPhases {__VA_ARGS__};\
UFUNCTION(BlueprintCallable, BlueprintPure)\
TSet<EStoryObjectPhase> GetValidPhases() const { return m_validPhases; }

#define IS_PHASE_VALID(phase) m_validPhases.Contains(phase)

#define CHECK_PHASE_VALID(phase, ...) \
if (!IS_PHASE_VALID(phase)) \
	return __VA_ARGS__;

#define CREATE_TICKET() \
UDependentStoryObjectClientTicket* ticket = NewObject<UDependentStoryObjectClientTicket>();

#define ASSIGN_SAME_PHASE_NO_DEP(phase) \
ticket->SetTicketData(this, phase, {});

#define ASSIGN_SAME_PHASE_NO_DEP_if(phase, condition) \
if (condition) \
	ASSIGN_SAME_PHASE_NO_DEP(phase)


DECLARE_DYNAMIC_DELEGATE_RetVal(FStoryObjectClientPhaseTicketInfo, FPhaseImplementation);

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
	UStoryObjectClientPhaseTicket* ExecutePhase(EStoryObjectPhase currentPhase);
};
