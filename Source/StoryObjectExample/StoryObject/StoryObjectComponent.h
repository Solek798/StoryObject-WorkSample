// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryObjectClient.h"
#include "Components/ActorComponent.h"
#include "StoryObjectComponent.generated.h"


UCLASS(Abstract, meta=(BlueprintSpawnableComponent))
class STORYOBJECTEXAMPLE_API UStoryObjectComponent : public UActorComponent, public IStoryObjectClient
{
	GENERATED_BODY()

public:
	UStoryObjectComponent();

protected:
	virtual void BeginPlay() override;
	
};
