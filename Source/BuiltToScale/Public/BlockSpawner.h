// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BlockSpawner.generated.h"

/**
 * 
 */
UCLASS()
class BUILTTOSCALE_API UBlockSpawner : public UWorldSubsystem
{
	GENERATED_BODY()

	public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void SpawnBlock();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	AActor* ActiveBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	AActor* SpawnPoint;
};
