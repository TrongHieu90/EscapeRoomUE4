// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoorScript.h"

#define OUT

// Sets default values for this component's properties
UOpenDoorScript::UOpenDoorScript()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorScript::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();


	
}


// Called every frame
void UOpenDoorScript::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorOnPlate() > 50.0f) //TODO make into parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//check if its time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

void UOpenDoorScript::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoorScript::CloseDoor()
{

	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

float UOpenDoorScript::GetTotalMassOfActorOnPlate()
{
	auto TotalMass = 0.0f;

	TArray<AActor*> OverlappingActors;
	//find all the overlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//iterate all the weights
	for(const auto* Actor:OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()-> GetMass();
	}

	return TotalMass;
}

