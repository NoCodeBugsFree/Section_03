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
}

void UOpenDoor::OpenDoor()
{
	// Create a Rotator
	FRotator NewRotation = FRotator(InitialDoorRotation.Pitch, InitialDoorRotation.Yaw + OpenAngle, InitialDoorRotation.Roll);

	// Set the door rotation
	if (Owner)
	{
		Owner->SetActorRotation(NewRotation);
	}
}

void UOpenDoor::CloseDoor()
{
	// Set the door rotation
	if (Owner)
	{
		Owner->SetActorRotation(InitialDoorRotation);
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() const
{
	float TotalMass = 0.f;

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
	if (GetTotalMassOfActorsOnPlate() > 50.f) // TODO remove HC
	{
		OpenDoor();

		// time in seconds since world was brought up for play
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		//GetWorld()->GetTimerManager().SetTimer(CloseDoorTimer, this, &UOpenDoor::CloseDoor, DoorClosedDelay, false);
	}

	// Check if it time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorClosedDelay)
	{
		CloseDoor();
	}
}

