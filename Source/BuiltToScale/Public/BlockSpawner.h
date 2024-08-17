// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BlockSpawner.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FBlockClass : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftClassPtr<AActor> BlockClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Level = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> Image;
};

UCLASS()
class BUILTTOSCALE_API UBlockSpawner : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void SpawnBlock();

	UFUNCTION(BlueprintCallable)
	TSoftClassPtr<AActor> GetRandomUnlockedBlock();

	UFUNCTION(BlueprintCallable)
	void SetupInitialUnlockedBlocks(int NumberOfBlocks);

	UFUNCTION(BlueprintCallable)
	void AddBlock(TSoftClassPtr<AActor> Block);

	UFUNCTION(BlueprintCallable)
	void RemoveBlock(TSoftClassPtr<AActor> Block);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	AActor* ActiveBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSoftClassPtr<AActor> NextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	AActor* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")

	TArray<TSoftClassPtr<AActor>> AllBlocks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")

	TArray<TSoftClassPtr<AActor>> InitialBlocks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TArray<TSoftClassPtr<AActor>> UnlockedBlocks;
};
