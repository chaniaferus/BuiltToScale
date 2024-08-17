﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BuiltToScale/Public/BlockSpawner.h"

#include "TetrisSettings.h"
#include "BuiltToScale/Public/BlockGameMode.h"
#include "Kismet/GameplayStatics.h"

void UBlockSpawner::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UTetrisSettings* Settings = GetDefault<UTetrisSettings>();
	if (Settings == nullptr || Settings->BlockTypes.LoadSynchronous() == nullptr)
	{
		return;
	}

	TArray<FName> BlockTypes = Settings->BlockTypes->GetRowNames();

	FString Context;
	for (const auto RowName : BlockTypes)
	{
		FBlockClass* BlockClass = Settings->BlockTypes->FindRow<FBlockClass>(RowName, Context);
		if (BlockClass != nullptr)
		{
			AllBlocks.Add(BlockClass->BlockClass.LoadSynchronous());

			if (BlockClass->Level == 0)
			{
				InitialBlocks.Add(BlockClass->BlockClass.LoadSynchronous());
			}
		}
	}
	SetupInitialUnlockedBlocks(5);
}

void UBlockSpawner::SpawnBlock()
{
	if (!SpawnPoint)
	{
		return;
	}

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());

	if (!GameMode)
	{
		return;
	}

	const ABlockGameMode* BlockGameMode = Cast<ABlockGameMode>(GameMode);

	if (!BlockGameMode)
	{
		return;
	}

	const FVector SpawnLocation = SpawnPoint->GetActorLocation();
	FRotator SpawnRotation = FRotator(0, 0, 0);
	SpawnRotation.Roll += 90 * FMath::RandRange(0, 3);

	const int32 RandomIndex = FMath::RandRange(0, UnlockedBlocks.Num() - 1);

	if (!UnlockedBlocks.IsValidIndex(RandomIndex))
	{
		return;
	}

	const TSoftClassPtr<AActor> RandomBlockClass = UnlockedBlocks[RandomIndex];

	AActor* SpawnedActor = GetWorld()->SpawnActor(RandomBlockClass.Get(), &SpawnLocation, &SpawnRotation);
	ActiveBlock = SpawnedActor;
}

void UBlockSpawner::SetupInitialUnlockedBlocks(const int NumberOfBlocks)
{
	UnlockedBlocks.Reset();
	TArray<TSoftClassPtr<AActor>> BlocksPoll = InitialBlocks;

	for (int32 Index = 0; Index < FMath::Min(NumberOfBlocks, InitialBlocks.Num()); Index++)
	{
		int RandomIndex = FMath::RandRange(0, BlocksPoll.Num() - 1);
		UnlockedBlocks.Add(BlocksPoll[RandomIndex]);
		BlocksPoll.RemoveAt(RandomIndex);
	}
}

void UBlockSpawner::AddBlock(TSoftClassPtr<AActor> Block)
{
	if (!UnlockedBlocks.Contains(Block))
	{
		UnlockedBlocks.Add(Block);
	}
}

void UBlockSpawner::RemoveBlock(TSoftClassPtr<AActor> Block)
{
	if (UnlockedBlocks.Contains(Block))
	{
		UnlockedBlocks.Remove(Block);
	}
}
