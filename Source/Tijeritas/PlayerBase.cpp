// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerBase::Initialize()
{
	UMatrixUtility::SetupBoolMatrix(Columns, Rows, ShapeMatrix);
	UMatrixUtility::SetupBoolMatrix(Columns, Rows, CutMatrix);
}

void APlayerBase::SetupShapeMatrix()
{
	UMatrixUtility::FillMatrixFromPoints(ShapePoints, Radius, InitialColumns, InitialRows, Columns, Rows, ShapeMatrix);
}

void APlayerBase::IsPointInShape(FVector Point, bool& PointInShape)
{
	PointInShape = UMatrixUtility::IsPointInMatrix(Point.X, Point.Y, InitialColumns, InitialRows, Columns, Rows, ShapeMatrix);
}

void APlayerBase::SaveCutsAndEvaluate()
{
	UMatrixUtility::ClearMatrix(CutMatrix);
	UMatrixUtility::FillMatrixFromPoints(CutPoints, 0, InitialColumns, InitialRows, Columns, Rows, CutMatrix);

	int32 TotalCutPoints = 0;
	int32 CorrectCutPoints = 0;
	int32 IncorrectCutPoints = 0;

	for (int Index = 0; Index < ShapeMatrix.Num(); Index++)
	{
		// Count of total points in matrix
		if (CutMatrix[Index] == true)
		{
			TotalCutPoints++;
		}

		// Active in cut only
		if (CutMatrix[Index] == true && ShapeMatrix[Index] == false)
		{
			IncorrectCutPoints++;
		}

		// Active in both
		if (CutMatrix[Index] == true && ShapeMatrix[Index] == true)
		{
			CorrectCutPoints++;
		}
	}

	float Grade = (((float)CorrectCutPoints - (float)IncorrectCutPoints) / (float)TotalCutPoints) * 100.0f;
	Grade = FMath::Clamp(Grade, 0.0f, 100.0f);

	//
	GEngine->AddOnScreenDebugMessage(-1, 200.0f, FColor::Green, FString::Printf(TEXT("Correct: %d, Incorrect: %d, Total: %d, Grade: %f"), CorrectCutPoints, IncorrectCutPoints, TotalCutPoints, Grade));
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

