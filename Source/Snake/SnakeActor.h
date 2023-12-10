// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SnakeActor.generated.h"

class ASnakeElementBase;


UENUM()
enum class EMovementDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STOP
};

UCLASS()
class SNAKE_API ASnakeActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASnakeActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDirection(EMovementDirection Direction) { LastPressedMoveDirection = Direction; }
	EMovementDirection GetDirection() { return MoveDirection; }
	void SetupDirection() { MoveDirection = LastPressedMoveDirection; }
	void AddSnakeElement(int N = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTransform GetElementOffset(FVector& MovementVector);
	void Move();
	void MoveHead(FVector& MovementVector);
	void MoveBody();
	void SetMovementVector(FVector& MovementVector);
	void SetupHead();
	UFUNCTION()
	void OnHeadInteract(AActor* OtherActor);
	void SetSnakeElement(FVector& MovementVector);
public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementClass;
	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;
	UPROPERTY(EditDefaultsOnly)
	float ElementSize;
	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

protected:
	UPROPERTY()
	EMovementDirection MoveDirection;

	EMovementDirection LastPressedMoveDirection;

	int ElementsToAdd = 0;
};
