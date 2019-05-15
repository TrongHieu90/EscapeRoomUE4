// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include <memory>

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();

	if(PhysicsHandle)
	{
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get the player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	//Log out to test

	/*UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString());*/


	//Draw debug red trace line
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()* _reach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f);

	//Setup Query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	
	//Raycasting
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);

	AActor* hitActor = Hit.GetActor();

	if (hitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor name is: %s"), *(hitActor->GetName()));
	}

	
}

