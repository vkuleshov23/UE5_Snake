// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Camera/CameraComponent.h"
#include "SnakeActor.h"
#include "Components/InputComponent.h"


// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
	
}

void ASnakePawn::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeActor>(SnakeActorClass, FTransform());
}

void ASnakePawn::HandlePlayerVerticalInput(float value)
{
	if (IsValid(SnakeActor)) {
		if (value > 0 && SnakeActor->GetDirection() != EMovementDirection::DOWN) {
			SnakeActor->SetDirection(EMovementDirection::UP);
		}
		else if (value < 0 && SnakeActor->GetDirection() != EMovementDirection::UP) {
			SnakeActor->SetDirection(EMovementDirection::DOWN);
		}
	}
}

void ASnakePawn::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(SnakeActor)) {
		if (value > 0 && SnakeActor->GetDirection() != EMovementDirection::LEFT) {
			SnakeActor->SetDirection(EMovementDirection::RIGHT);
		}
		else if (value < 0 && SnakeActor->GetDirection() != EMovementDirection::RIGHT) {
			SnakeActor->SetDirection(EMovementDirection::LEFT);
		}
	}
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &ASnakePawn::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &ASnakePawn::HandlePlayerHorizontalInput);

}

