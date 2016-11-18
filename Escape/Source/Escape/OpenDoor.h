// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest); // FOnOpenRequest - Random Class Name
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest); // FOnOpenRequest - Random Class Name

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable) 
	FOnOpenRequest OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FOnCloseRequest OnCloseRequest;
	
protected:


private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float TriggerMass = 50.f;

	UPROPERTY()
	AActor* Owner;

	FRotator InitialDoorRotation;

	float GetTotalMassOfActorsOnPlate() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	ATriggerVolume* PressurePlate;
	
};
