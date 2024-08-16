// Fill out your copyright notice in the Description page of Project Settings.


#include "BuiltToScale/Public/BlockSpawner.h"

#include "BuiltToScale/Public/BlockGameMode.h"
#include "Kismet/GameplayStatics.h"

void UBlockSpawner::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
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

	const TSoftClassPtr<AActor> BlockClass = BlockGameMode->BlockClass.LoadSynchronous();
	
	const FVector SpawnLocation = SpawnPoint->GetActorLocation();
	FRotator SpawnRotation = FRotator(0, 0, 0);
	SpawnRotation.Roll += 90 * FMath::RandRange(0,3);
	
	AActor* SpawnedActor = GetWorld()->SpawnActor(BlockClass.Get(), &SpawnLocation, &SpawnRotation);
	ActiveBlock = SpawnedActor;
}

