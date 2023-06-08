// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StoryObjectExample/StoryObject/StoryObjectClient.h"
//#include "LevelSequenceActor.h"
#include "SequencePlayer.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STORYOBJECTEXAMPLE_API USequencePlayer : public UActorComponent, public IStoryObjectClient
{
	GENERATED_BODY()

public:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//ALevelSequenceActor* Sequence;
	
	USequencePlayer();

	virtual UDependentStoryObjectClientTicket* GetPhaseTicket_Implementation(EStoryObjectPhase phase) override;
};
