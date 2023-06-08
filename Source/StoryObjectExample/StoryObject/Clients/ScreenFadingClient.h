// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StoryObjectExample/StoryObject/StoryObject.h"
#include "StoryObjectExample/StoryObject/StoryObjectClient.h"
#include "ScreenFadingClient.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STORYOBJECTEXAMPLE_API UScreenFadingClient : public UActorComponent, public IStoryObjectClient
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FadeTime;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeOutStart;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeInStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeOutFinish;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeInFinish;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool FadeOutStop;

protected:
	UPROPERTY()
	FClientDone m_ownerCallback;
	
	DECLARE_PHASE_RANGE(EStoryObjectPhase::PRE_START,
		EStoryObjectPhase::RUNNING,
		EStoryObjectPhase::PRE_STOP,
		EStoryObjectPhase::PRE_FINISH,
		EStoryObjectPhase::FINISHED)

	bool m_isInFadingOperation;
	
public:
	UScreenFadingClient();

	virtual UDependentStoryObjectClientTicket* GetPhaseTicket_Implementation(EStoryObjectPhase phase) override;
	virtual void Execute_Implementation(EStoryObjectPhase currentPhase, const FClientDone& phaseCallback) override;
	virtual bool IsClientDone_Implementation(EStoryObjectPhase currentPhase) override;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnFadeDone();
};
