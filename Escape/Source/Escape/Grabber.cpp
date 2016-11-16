// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("Grabber... "));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get the player viewpoint

	// AController::GetPlayerViewPoint
	// Returns Player's Point of View For the AI this means the Pawn's 'Eyes'
	// ViewPoint For a Human player, this means the Camera's ViewPoint 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// log out to test
	/*
	UE_LOG(LogTemp, Error, TEXT("Location = %s  Rotation = %s"), 
		*PlayerViewPointLocation.ToString(), 
		*PlayerViewPointRotation.ToString());
	*/

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// Draw a red trace in the world to visualize
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, DeltaTime, 0, 20.f);

	// Line Trace (AKA ray-cast) out to reach distance
	FCollisionQueryParams CQP(FName(TEXT("")), false, GetOwner());

	// FCollisionObjectQueryParams COQP;
	// COQP.AddObjectTypesToQuery(ECC_PhysicsBody);
	
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), CQP);

	// see what we hit
	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *Hit.GetActor()->GetName());
	}

}

