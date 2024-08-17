// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintTools.generated.h"

/**
 * 
 */

UCLASS(BlueprintType)
class BUILTTOSCALE_API ATriggerPoint : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PositionX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PositionY = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTaken = false;
};

UCLASS()
class BUILTTOSCALE_API UBlueprintTools : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="BlueprintTools")
	static void GenerateTriggerGrid(UObject* WorldContext, TSoftClassPtr<ATriggerPoint> Class,
	                                UStaticMeshComponent* BottomBorder, int32 CubeSize, int32 SizeX, int32 SizeY);
};
