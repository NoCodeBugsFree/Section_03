// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialDoorRotation = GetOwner()->GetActorRotation();

	Owner = GetOwner();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("NOT PressurePlate ..."));
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() const
{
	float TotalMass = 0.f;
	// defaultpawn -> physics -> constraints -> lock rotation x y z (set them to ticked)
	TArray<AActor*> OverlappedActors;

	// Find all the overlapping across
	if (PressurePlate)
	{
		// Returns list of actors this actor is overlapping 
		// (any component overlapping any component). Does not return itself.
		PressurePlate->GetOverlappingActors(OUT OverlappedActors);

		// Iterate through them adding their mass
		for (AActor* Actor  : OverlappedActors)
		{
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			UE_LOG(LogTemp, Error, TEXT("%s on pressure plate"), *Actor->GetName());
		}
	}
	
	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	// Poll the trigger volume
	// if the ActorThatOpen
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) 
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}

