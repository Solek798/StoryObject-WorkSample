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

#define DECLARE_PHASE_IMPLEMENTATION(phase, function)\
FPhaseImplementation phaseImplementation##phase;\
phaseImplementation##phase.BindDynamic(this, function);\
m_phaseImplementations.Add(EStoryObjectPhase::phase, phaseImplementation##phase);

#define GENERATE_CLIENT_DECLARATION_BODY() \
protected:\
UPROPERTY(BlueprintReadOnly, VisibleAnywhere)\
TMap<EStoryObjectPhase, FPhaseImplementation> m_phaseImplementations;\
UPROPERTY()\
FClientFinishedPhase m_onClientFinishedPhaseEvent;\
public:\
const FStoryObjectClientPhaseTicketInfo INVALID_INFO {EStoryObjectPhase::NONE, {}};\
virtual UStoryObjectClientPhaseTicket* ExecutePhase_Implementation(EStoryObjectPhase currentPhase) override;\
UFUNCTION(BlueprintCallable)\
void NotifyTaskIsDone() const;

#define GENERATE_CLIENT_IMPLEMENTATION_BODY(class) \
UStoryObjectClientPhaseTicket* class::ExecutePhase_Implementation(const EStoryObjectPhase currentPhase)\
{\
	if (!m_phaseImplementations.Contains(currentPhase))\
		return nullptr;\
	UStoryObjectClientPhaseTicket* ticket = NewObject<UStoryObjectClientPhaseTicket>();\
	FStoryObjectClientPhaseTicketInfo info {currentPhase, {}};\
	m_onClientFinishedPhaseEvent = ticket->RegisterClient(this);\
	if (m_phaseImplementations[currentPhase].IsBound())\
	{\
		const FStoryObjectClientPhaseTicketInfo implementationInfo = m_phaseImplementations[currentPhase].Execute();\
		if (implementationInfo.EndPhase == EStoryObjectPhase::NONE)\
			return nullptr;\
		info = implementationInfo;\
	}\
	ticket->SetTicketInfo(info);\
	return ticket;\
}\
void class::NotifyTaskIsDone() const\
{\
	if (m_onClientFinishedPhaseEvent.IsBound())\
		m_onClientFinishedPhaseEvent.Execute();\
}


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
