// Fill out your copyright notice in the Description page of Project Settings.


#include "MatrixUtility.h"

void UMatrixUtility::SetupBoolMatrix(const int32 Columns, const int32 Rows, TArray<bool>& BoolMatrix)
{
	for (int Y = 0; Y < Rows; Y++)
	{
		for (int X = 0; X < Columns; X++)
		{
			BoolMatrix.Add(false);
		}
	}
}

void UMatrixUtility::ClearMatrix(TArray<bool>& BoolMatrix)
{
	for (int Index = 0; Index < BoolMatrix.Num(); Index++)
	{
		BoolMatrix[Index] = false;
	}
}

void UMatrixUtility::FillMatrixFromPoints(const TArray<FVector> Points, const float Radius, const int32 InitialColumns, const int32 InitialRows, const int32 TargetColumns, const int32 TargetRows, TArray<bool>& BoolMatrix)
{
	float SizeMultiplier = 10.0f;	// Converts 12.5 to 125 to be more precise when converting to matrix int indexes

	float ColumnConvertionFactor = (float)TargetColumns / (float)(InitialColumns * SizeMultiplier);
	float RowConvertionFactor = (float)TargetRows / (float)(InitialRows * SizeMultiplier);

	int32 RoundRadius = (int)(Radius * SizeMultiplier * RowConvertionFactor);

	FVector CurrentVector = FVector(0, 0, 0);
	FVector NextVector = FVector(0, 0, 0);

	// Loop through every point and generate a line between them
	// Also add a radius to every point (useful for fail margin in the shapes matrix)
	for (int Current = 0; Current < Points.Num() - 1; Current++)
	{
		int Next = Current + 1;

		CurrentVector.X = (int)(Points[Current].X * SizeMultiplier * ColumnConvertionFactor);
		CurrentVector.Y = (int)(Points[Current].Y * SizeMultiplier * RowConvertionFactor);

		NextVector.X = (int)(Points[Next].X * SizeMultiplier * ColumnConvertionFactor);
		NextVector.Y = (int)(Points[Next].Y * SizeMultiplier * RowConvertionFactor);

		// Radius consideration
		int Diff = (int)(FVector::Dist(CurrentVector, NextVector));
		float Progress = 0.0f;
		while (Progress <= 1.0f)
		{
			int X = (int)(FMath::Lerp(CurrentVector.X, NextVector.X, Progress));
			int Y = (int)(FMath::Lerp(CurrentVector.Y, NextVector.Y, Progress));

			DrawCircleInMatrix(X, Y, RoundRadius, TargetColumns, TargetRows, BoolMatrix);
			Progress += 0.1f;
		}
	}
}

void UMatrixUtility::DrawCircleInMatrix(const int32 X, const int32 Y, const int32 Radius, const int32 Columns, const int32 Rows, TArray<bool>& BoolMatrix)
{
	int32 PowRadius = (int)(Radius * Radius);

	int32 XStart = X - Radius;
	int32 XEnd = X + Radius;

	int32 YStart = Y - Radius;
	int32 YEnd = Y + Radius;

	// Draw a 'Sub Matrix' inside the main matrix considering the specified radius to draw the circle
	for (int CurY = YStart; CurY <= YEnd; CurY++)
	{
		for (int CurX = XStart; CurX <= XEnd; CurX++)
		{
			float SquaredDistance = FMath::Pow(Y - CurY, 2.0f) + FMath::Pow(X - CurX, 2.0f);
			if (SquaredDistance <= PowRadius)
			{
				SetPointInMatrix(CurX, CurY, Columns, Rows, BoolMatrix);
			}
		}
	}
}

void UMatrixUtility::SetPointInMatrix(const int32 X, const int32 Y, const int32 Columns, const int32 Rows, TArray<bool>& BoolMatrix)
{
	// Out of bounds, don't draw
	if (X < 0 || X >= Columns ||
		Y < 0 || Y >= Rows)
	{
		return;
	}

	int32 Index = MatrixToListIndex(X, Y, Columns, Rows);
	BoolMatrix[Index] = true;
}

bool UMatrixUtility::IsPointInMatrix(const float X, const float Y, const int32 InitialColumns, const int32 InitialRows, const int32 TargetColumns, const int32 TargetRows, TArray<bool>& BoolMatrix)
{
	float SizeMultiplier = 10.0f;	// Converts 12.5 to 125 to be more precise when converting to matrix int indexes

	float ColumnConvertionFactor = (float)TargetColumns / (float)(InitialColumns * SizeMultiplier);
	float RowConvertionFactor = (float)TargetRows / (float)(InitialRows * SizeMultiplier);

	int32 MatrixPositionX = (int)(X * SizeMultiplier * ColumnConvertionFactor);
	int32 MatrixPositionY = (int)(Y * SizeMultiplier * RowConvertionFactor);

	// Out of bounds
	if (MatrixPositionX < 0 || MatrixPositionX >= TargetColumns ||
		MatrixPositionY < 0 || MatrixPositionY >= TargetRows)
	{
		return false;
	}

	return BoolMatrix[MatrixToListIndex(MatrixPositionX, MatrixPositionY, TargetColumns, TargetRows)];
}

int UMatrixUtility::MatrixToListIndex(const int32 X, const int32 Y, const int32 Columns, const int32 Rows)
{
	return (Columns * Y) + X;
}

void UMatrixUtility::ListIndexToMatrix(const int32 Index, const int32 Columns, const int32 Rows, int32& X, int32& Y)
{
	Y = Index / Columns;
	X = Index - (Y * Columns);
}

void UMatrixUtility::MatrixToString(const int32 Columns, const int32 Rows, const TArray<bool>& BoolMatrix, FString& Message)
{
	Message = "";

	for (int Y = 0; Y < Rows; Y++)
	{
		for (int X = 0; X < Columns; X++)
		{
			Message += (BoolMatrix[MatrixToListIndex(X, Y, Columns, Rows)] ? "[1]" : "[0]");
		}

		Message += "\n";
	}
}
