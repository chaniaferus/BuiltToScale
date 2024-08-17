// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TetrisSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig)
class BUILTTOSCALE_API UTetrisSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "General")
	TSoftObjectPtr<UDataTable> BlockTypes;
};
