// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape.h"
#include "PossitionReport.h"


// Sets default values for this component's properties
UPossitionReport::UPossitionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	
	
}


// Called when the game starts
void UPossitionReport::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner())
	{
		return;
	}

	FString OwnerName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Possition Report reporting on %s !"), *OwnerName);
	
}


// Called every frame
void UPossitionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}
