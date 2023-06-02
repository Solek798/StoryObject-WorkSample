// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoryObjectClient.h"
#include "StoryObjectSceneComponent.generated.h"


UCLASS(Abstract, meta=(BlueprintSpawnableComponent))
class STORYOBJECTEXAMPLE_API UStoryObjectSceneComponent : public USceneComponent, public IStoryObjectClient
{
	GENERATED_BODY()

public:
	UStoryObjectSceneComponent();

protected:
	virtual void BeginPlay() override;
};
