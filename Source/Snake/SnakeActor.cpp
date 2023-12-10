// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeActor.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeActor::ASnakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	LastPressedMoveDirection = EMovementDirection::STOP;
	MovementSpeed = 1.0;
}

// Called when the game starts or when spawned
void ASnakeActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	SetupHead();
}

void ASnakeActor::SetupHead()
{
	FTransform HeadTransform = FTransform(FVector(ForceInitToZero));
	ASnakeElementBase* Head = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, HeadTransform);
	int32 pos = SnakeElements.Add(Head);
	Head->SetFirstElementType();
	Head->OnIneract.AddDynamic(this, &ASnakeActor::OnHeadInteract);
}

void ASnakeActor::AddSnakeElement(int N)
{
	if (N >= 0) {
		ElementsToAdd += N;
	}
}

void ASnakeActor::OnHeadInteract(AActor* OtherActor)
{
	IInteractable* Interactor = Cast<IInteractable>(OtherActor);
	if (Interactor) {
		Interactor->Interact(this);
	}
}

void ASnakeActor::Move()
{
	FVector MovementVector(ForceInitToZero);
	SetMovementVector(MovementVector);
	MoveBody();
	SetSnakeElement(MovementVector);
	MoveHead(MovementVector);
}

void ASnakeActor::SetMovementVector(FVector& MovementVector)
{
	SetupDirection();
	switch (MoveDirection) {
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
	}
}

void ASnakeActor::MoveBody()
{
	SnakeElements[0]->DisableCollision();
	for (int i = SnakeElements.Num() - 1; i > 0; i--) {
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		CurrentElement->SetActorLocation(PrevElement->GetActorLocation());
	}
}

void ASnakeActor::SetSnakeElement(FVector& MovementVector)
{
	if (ElementsToAdd > 0) {
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, GetElementOffset(MovementVector));
		SnakeElements.Add(NewSnakeElement);
		ElementsToAdd--;
	}
}

FTransform ASnakeActor::GetElementOffset(FVector& MovementVector)
{
	return FTransform(SnakeElements.Top()->GetActorLocation());
}

void ASnakeActor::MoveHead(FVector& MovementVector)
{
	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->EnableCollision();

	//FHitResult* OutSweepHitResult = new FHitResult();
	//SnakeElements[0]->AddActorWorldOffset(MovementVector, true, OutSweepHitResult);
	//if (OutSweepHitResult->bBlockingHit == true) {
	//	FString name = OutSweepHitResult->GetActor()->GetFName().ToString();
	//	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("%s"), *name));
	//}
	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("no collision"));
	//}
	//delete OutSweepHitResult;
}

// Called every frame
void ASnakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->Move();

}

