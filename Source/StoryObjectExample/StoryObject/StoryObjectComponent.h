// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryObjectClient.h"
#include "StoryObjectClientPhaseTicket.h"
#include "Components/ActorComponent.h"
#include "StoryObjectComponent.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType)
class STORYOBJECTEXAMPLE_API UStoryObjectComponent : public UActorComponent, public IStoryObjectClient
{
	GENERATED_BODY()

    GENERATE_CLIENT_DECLARATION_BODY()

	UStoryObjectComponent();
};
