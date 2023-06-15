// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StoryObjectExample/StoryObject/StoryObjectClient.h"
#include "StoryObjectComponent.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType)
class STORYOBJECTEXAMPLE_API UStoryObjectComponent : public UActorComponent, public IStoryObjectClient
{
	GENERATED_BODY()

    GENERATE_CLIENT_DECLARATION_BODY()

	UStoryObjectComponent();
};
