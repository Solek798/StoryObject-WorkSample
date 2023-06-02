// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObjectComponent.h"


UStoryObjectComponent::UStoryObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStoryObjectComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

