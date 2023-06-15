// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryObjectExample/StoryObject/StoryObjectClient.h"
#include "StoryObjectClientActor.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class STORYOBJECTEXAMPLE_API AStoryObjectClientActor : public AActor, public IStoryObjectClient
{
	GENERATED_BODY()

	GENERATE_CLIENT_DECLARATION_BODY()
	
	AStoryObjectClientActor();
};
