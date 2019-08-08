// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
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
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	FindPhysicsComponent();

	SetUpInputComponent();

	
	
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabbed"))
		//LINE TRACE andsee if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
		//if we hit something attach a physics handle
		//TODO attach physics handle
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit) {
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,//no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true //allow rotation
		);
	}


}


void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Released"))
		//TODO release physics handle
		if (!PhysicsHandle) { return; }
		PhysicsHandle->ReleaseComponent();
}


void UGrabber::FindPhysicsComponent() {
	///Look for atached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle) {
		UE_LOG(LogTemp, Warning, TEXT("Physicas found!"))
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}
}


void UGrabber::SetUpInputComponent() {
	///Look for atached Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input  component"), *GetOwner()->GetName())
	}

}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	//Line trace / Ray-cast out to reach distance
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(OUT HitResult, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody));

	AActor *ActorHit = HitResult.GetActor();

	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("This is a %s"), *(ActorHit->GetName()));
	}

	return HitResult;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent) {
		//move the object the way we re holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}


}

FVector UGrabber::GetReachLineEnd() {

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	//Get player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location : %s , Position : %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	return  (PlayerViewPointLocation + PlayerViewPointRotation.Vector() *Reach);
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return PlayerViewPointLocation;
}

