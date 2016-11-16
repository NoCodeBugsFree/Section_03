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

	// Look for attached Physics Handle
	FindPhysicsHandleComponent();
	
	// try to find InputComponent ans setup InputComponent
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

		FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

}

void UGrabber::FindPhysicsHandleComponent()
{
	// Searches components array and returns first encountered component of the specified class
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Component NOT FOUND !!!"));
	}
}

void UGrabber::SetupInputComponent()
{
	// Implement an Actor component for input bindings
	// An Input Component is a transient component that is to an Actor to bind various forms 
	// of input events to delegate functions. Input components are processed from 
	// a stack managed by the PlayerController and processed by the PlayerInput. 
	// Each binding can consume the input event preventing other components 
	// on the input stack from processing the input.

	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComp)
	{
		UE_LOG(LogTemp, Error, TEXT("InputComp was found ..."));
		// Bind the input axis
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabPressed);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::GrabReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComp NOT FOUND !"));
	}
}

void UGrabber::GrabPressed()
{
	// LINE TRACE and see if we reach any actors with physics body collision channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

 	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	// if we hit something then attach a physics handle
	// TODO attach Physics Handle

	if (ActorHit)
	{
		if (PhysicsHandle)
		{
			// UPhysicsHandleComponent::GrabComponent
			// Grab the specified component
			PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true); // allow rotation
		}
	}
}

void UGrabber::GrabReleased()
{
	// Release Physics Handle
	if (PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get the player viewpoint

	// AController::GetPlayerViewPoint
	// Returns Player's Point of View For the AI this means the Pawn's 'Eyes'
	// ViewPoint For a Human player, this means the Camera's ViewPoint 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// Line Trace (AKA ray-cast) out to reach distance
	FCollisionQueryParams CQP(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), CQP);

	return Hit;
}

