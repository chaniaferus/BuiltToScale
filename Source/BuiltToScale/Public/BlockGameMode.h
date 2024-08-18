// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlockGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BUILTTOSCALE_API ABlockGameMode : public AGameModeBase
{
	GENERATED_BODY()

	public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSoftClassPtr<AActor> BlockClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float MoveInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int PlayerLevel = 0;
};
