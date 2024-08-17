// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintTools.h"

void UBlueprintTools::GenerateTriggerGrid(UObject* WorldContext, const TSoftClassPtr<ATriggerPoint> Class,
                                          UStaticMeshComponent* BottomBorder, const int32 CubeSize, const int32 SizeX,
                                          const int32 SizeY)
{
	FVector StartPoint = BottomBorder->GetComponentLocation();
	StartPoint.Y += CubeSize * 0.5;
	StartPoint.Z += CubeSize * 1.5;
	StartPoint.X += CubeSize * 0.5;

	FVector CurrentLocation = StartPoint;
	for (int32 PositionY = 0; PositionY < SizeY; PositionY++)
	{
		CurrentLocation.Y = StartPoint.Y;
		for (int32 PositionX = 0; PositionX < SizeX; PositionX++)
		{
			AActor* SpawnedTrigger = WorldContext->GetWorld()->SpawnActor(Class.Get(), &CurrentLocation);
			if (SpawnedTrigger == nullptr)
			{
				continue;
			}

			ATriggerPoint* TriggerPoint = Cast<ATriggerPoint>(SpawnedTrigger);
			if (TriggerPoint != nullptr)
			{
				TriggerPoint->SetActorLocation(CurrentLocation);
				TriggerPoint->PositionX = PositionX;
				TriggerPoint->PositionY = PositionY;
			}
			CurrentLocation.Y += CubeSize;
		}
		CurrentLocation.Z += CubeSize;
	}
}
