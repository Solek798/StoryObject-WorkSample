// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WDG_FadeScreen.h"
#include "Engine/GameInstance.h"
#include "StoryObject/StoryDirector.h"
#include "MyCustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STORYOBJECTEXAMPLE_API UMyCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AStoryDirector* StoryDirector;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UWDG_FadeScreen* FadeScreen;
};
