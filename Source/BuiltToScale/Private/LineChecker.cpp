// Fill out your copyright notice in the Description page of Project Settings.


#include "LineChecker.h"

void ULineChecker::SetTriggerPoints(TArray<ATriggerPoint*> TriggerPoints)
{
	Lines.Empty();
	for (ATriggerPoint* TriggerPoint : TriggerPoints)
	{
		if (TriggerPoint == nullptr)
		{
			continue;
		}

		if (!Lines.Contains(TriggerPoint->PositionY))
		{
			Lines.Add(TriggerPoint->PositionY);
		}
		Lines[TriggerPoint->PositionY].TriggerPoints.Add(TriggerPoint);
	}
}

TArray<int32> ULineChecker::GetLinesToClean()
{
	TArray<int32> LinesToClean;
	for (TTuple<int, FTriggerLine> TriggerPointLine : Lines)
	{
		bool bAddLine = true;
		for (ATriggerPoint* TriggerPoint : TriggerPointLine.Value.TriggerPoints)
		{
			if (!TriggerPoint->bTaken)
			{
				bAddLine = false;
				break;
			}
		}

		if (bAddLine)
		{
			LinesToClean.Add(TriggerPointLine.Key);
		}
	}

	return LinesToClean;
}

void ULineChecker::CleanLines(TArray<int32> LineNumbers)
{
	for (int32 LineNumber : LineNumbers)
	{
		TArray<ATriggerPoint*> TriggerPoints = Lines[LineNumber].TriggerPoints;
		
		for (ATriggerPoint* TriggerPoint : TriggerPoints)
		{
			if (TriggerPoint->OverlappingBlock)
			{
				TriggerPoint->OverlappingBlock->Destroy();
			}
		}
	}
}

void ULineChecker::FillEmptyLines(TArray<int32> EmptyLines)
{
	if (EmptyLines.Num() == 0)
	{
		return;
	}

	TArray<int32> LinesToMove;

	int32 EmptyLinesIndex = 0;
	for (int32 Index = 0; Index < Lines.Num(); Index++)
	{
		if (EmptyLines.IsValidIndex(EmptyLinesIndex) && Index == EmptyLines[EmptyLinesIndex])
		{
			EmptyLinesIndex++;
			continue;
		}

		if (!Lines.Contains(Index))
		{
			return;
		}
		
		TArray<ATriggerPoint*> BlocksToMove = Lines[Index].TriggerPoints;
		for (const ATriggerPoint* TriggerPoint : BlocksToMove)
		{
			if (TriggerPoint->OverlappingBlock)
			{
				FVector DeltaLocation = FVector::ZeroVector;
				DeltaLocation.Z -= EmptyLinesIndex * 100;
				TriggerPoint->OverlappingBlock->AddActorWorldOffset(DeltaLocation);
			}
		}
	}
}
