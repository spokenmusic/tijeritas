// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MatrixUtility.h"
#include "PlayerBase.generated.h"

UCLASS()
class TIJERITAS_API APlayerBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerBase();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bool Matrices|Setup")
	int32 InitialColumns = 31;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bool Matrices|Setup")
	int32 InitialRows = 22;

	// Imagine that the sheet is rotated 90 degrees
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bool Matrices|Setup")
	int32 Columns = 439;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bool Matrices|Setup")
	int32 Rows = 310;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bool Matrices|Setup")
	float Radius = 0.5f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Bool Matrices")
	TArray<bool> ShapeMatrix;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Bool Matrices")
	TArray<bool> CutMatrix;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Bool Matrices")
	TArray<FVector> ShapePoints;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Bool Matrices")
	TArray<FVector> CutPoints;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void SetupShapeMatrix();

	UFUNCTION(BlueprintCallable)
	void IsPointInShape(FVector Point, bool& PointInShape);

	UFUNCTION(BlueprintCallable)
	void SaveCutsAndEvaluate();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
