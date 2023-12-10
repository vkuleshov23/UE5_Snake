// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASnakeElementBase::ASnakeElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnakeElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeElementBase::Interact(AActor* Interactor)
{
	ASnakeActor* SnakeActor = Cast<ASnakeActor>(Interactor);
	if (SnakeActor) {
		SnakeActor->Destroy();
	}
}

void ASnakeElementBase::EnableCollision()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASnakeElementBase::DisableCollision()
{
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASnakeElementBase::SetFirstElementType_Implementation()
{
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::OnBeginOverlap);
}

void ASnakeElementBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IInteractable* inreactableObj = Cast<IInteractable>(OtherActor);
	if (inreactableObj) {
		OnIneract.Broadcast(OtherActor);
	}
}

