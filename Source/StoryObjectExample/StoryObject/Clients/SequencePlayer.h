// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "StoryObjectExample/StoryObject/StoryObjectComponent.h"
#include "SequencePlayer.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STORYOBJECTEXAMPLE_API USequencePlayer : public UStoryObjectComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ALevelSequenceActor* Sequence;

protected:
	FTimerHandle m_handle;

	bool m_timerCallbackWasCalled;

public:
	USequencePlayer();

	UFUNCTION()
	FStoryObjectClientPhaseTicketInfo PlaySequence();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnCloseToSequenceEnd();
};

