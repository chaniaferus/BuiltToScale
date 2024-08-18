// Fill out your copyright notice in the Description page of Project Settings.


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
			AllBlocks.Add(*BlockClass);

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

	if (NextBlock == nullptr)
	{
		NextBlock = GetRandomUnlockedBlock();
	}

	const FVector SpawnLocation = SpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = FRotator(0, 0, 0);
	SpawnRotation.Roll += 90 * FMath::RandRange(0, 3);

	AActor* SpawnedActor = GetWorld()->SpawnActor(NextBlock.Get(), &SpawnLocation, &SpawnRotation);
	ActiveBlock = SpawnedActor;
	NextBlock = GetRandomUnlockedBlock();
}

TSoftClassPtr<AActor> UBlockSpawner::GetRandomUnlockedBlock()
{
	const int32 RandomIndex = FMath::RandRange(0, UnlockedBlocks.Num() - 1);
	if (!UnlockedBlocks.IsValidIndex(RandomIndex))
	{
		return nullptr;
	}

	return UnlockedBlocks[RandomIndex];
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

TArray<TSoftClassPtr<AActor>> UBlockSpawner::GetRandomUnlockedBlocks(int32 Number)
{
	TArray<TSoftClassPtr<AActor>> Result;
	TArray<TSoftClassPtr<AActor>> BlocksPoll;
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());

	if (!GameMode)
	{
		return {};
	}

	const ABlockGameMode* BlockGameMode = Cast<ABlockGameMode>(GameMode);

	if (!BlockGameMode)
	{
		return {};
	}
	
	for (FBlockClass Block : AllBlocks)
	{
		if (Block.Level <= BlockGameMode->PlayerLevel)
		{
			BlocksPoll.Add(Block.BlockClass);
		}
	}

	for (int32 Index = 0; Index < FMath::Min(Number, BlocksPoll.Num()); Index++)
	{
		const int RandomIndex = FMath::RandRange(0, BlocksPoll.Num() - 1);
		Result.Add(BlocksPoll[RandomIndex]);
		BlocksPoll.RemoveAt(RandomIndex);
	}

	return Result;
}
