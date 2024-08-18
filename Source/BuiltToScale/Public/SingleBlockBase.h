// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleBlockBase.generated.h"

UCLASS()
class BUILTTOSCALE_API ASingleBlockBase : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void DestroyBlock();
};
