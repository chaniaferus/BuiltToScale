// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintTools.h"
#include "Subsystems/WorldSubsystem.h"
#include "LineChecker.generated.h"

/**
 * 
 */
USTRUCT()
struct FTriggerLine
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ATriggerPoint*> TriggerPoints;
};

UCLASS()
class BUILTTOSCALE_API ULineChecker : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetTriggerPoints(TArray<ATriggerPoint*> TriggerPoints);

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetLinesToClean();

	UFUNCTION(BlueprintCallable)
	void CleanLines(TArray<int32> LineNumbers);

	UFUNCTION(BlueprintCallable)
	void FillEmptyLines(TArray<int32> EmptyLines);

private:
	TMap<int32, FTriggerLine> Lines;
};
