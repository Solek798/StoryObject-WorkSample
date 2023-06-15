// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryObjectComponent.h"


GENERATE_CLIENT_IMPLEMENTATION_BODY(UStoryObjectComponent)

UStoryObjectComponent::UStoryObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
