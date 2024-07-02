// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatrixUtility.generated.h"

/**
 * 
 */
UCLASS()
class TIJERITAS_API UMatrixUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/* Allocates all the memory for the bool matrix */
	UFUNCTION(BlueprintCallable)
	static void SetupBoolMatrix(const int32 Columns, const int32 Rows, TArray<bool>& BoolMatrix);

	/* Sets all the fields in the matrix as False */
	UFUNCTION(BlueprintCallable)
	static void ClearMatrix(TArray<bool>& BoolMatrix);

	/* Maps the points from Unreal units to a boolean matrix coordinates to find intersections */
	UFUNCTION(BlueprintCallable)
	static void FillMatrixFromPoints(const TArray<FVector> Points, const float Radius, const int32 InitialColumns, const int32 InitialRows, const int32 TargetColumns, const int32 TargetRows, TArray<bool>& BoolMatrix);

	/* Uses the X, Y and Radius variables to draw a circle in the bool matrix */
	UFUNCTION(BlueprintCallable)
	static void DrawCircleInMatrix(const int32 X, const int32 Y, const int32 Radius, const int32 Columns, const int32 Rows, TArray<bool>& BoolMatrix);

	/* Simply sets the specified point in the matrix as True*/
	UFUNCTION(BlueprintCallable)
	static void SetPointInMatrix(const int32 X, const int32 Y, const int32 Columns, const int32 Rows, TArray<bool>& BoolMatrix);

	/* Checks if the specified point is set as true in the matrix */
	UFUNCTION(BlueprintCallable)
	static bool IsPointInMatrix(const float X, const float Y, const int32 InitialColumns, const int32 InitialRows, const int32 TargetColumns, const int32 TargetRows, TArray<bool>& BoolMatrix);

	/* Converts a matrix position to a list index */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int MatrixToListIndex(const int32 X, const int32 Y, const int32 Columns, const int32 Rows);

	/* Converts a list index to a matrix position */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void ListIndexToMatrix(const int32 Index, const int32 Columns, const int32 Rows, int32& X, int32& Y);

	/* Useful for printing matrices */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void MatrixToString(const int32 Columns, const int32 Rows, const TArray<bool>& BoolMatrix, FString& Message);
};
