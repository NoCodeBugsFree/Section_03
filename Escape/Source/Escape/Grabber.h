// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()
	//
public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:

	UPhysicsHandleComponent* PhysicsHandle;

	UInputComponent* InputComp;

	/** Reach in cm  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Reach = 100.f;
	
	/**  find (assumed) attached  PhysicsHandleComponent */
	void FindPhysicsHandleComponent();

	/**  Return current end of reach line */
	FVector GetReachLineEnd();

	/**  Return current start of reach line */
	FVector GetReachLineStart();

	/**  setup (assumed attached InputComponent */
	void SetupInputComponent();

	/** Raycast and grab that's in reach  */
	void GrabPressed();
	void GrabReleased();

	/** Return Hit for first physics body in reach  */
	const FHitResult GetFirstPhysicsBodyInReach();
	
};
