// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Find Owner
	//OpenDoor();
	
}

void UOpenDoor::OpenDoor()
{
	
	 
	//create a rotator
	FRotator NewRotation = FRotator(0.f, OpenAngle, 0.f);
	//set the rotation
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
	
	//create a rotator
	FRotator NewRotation = FRotator(0.f, 0.f, 0.f);
	//set the rotation
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Poll the trigger Volume
	if (GetTotalMassOfActorsOnPlate() > 50.f) //TODO make param 
	{
		
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	//check if it s time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	 }

	
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {

	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	//Find all the Overlaping actors 
	if (!PressurePlate) { return 0.f; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//Iterate through their masses
	for (const auto& Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("TotalMass = %.f"), TotalMass)
	}

	return TotalMass;
}

