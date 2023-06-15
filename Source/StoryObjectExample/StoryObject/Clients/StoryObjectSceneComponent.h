// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryObjectExample/StoryObject/StoryObjectClient.h"
#include "StoryObjectSceneComponent.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType)
class STORYOBJECTEXAMPLE_API UStoryObjectSceneComponent : public USceneComponent, public IStoryObjectClient
{
	GENERATED_BODY()

	GENERATE_CLIENT_DECLARATION_BODY()
	
	UStoryObjectSceneComponent();
};
