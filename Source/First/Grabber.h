// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/GameFramework/RootMotionSource.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRST_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//How far of the player can we reach in cm
	float Reach = 100.f;
	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UInputComponent *InputComponent = nullptr;

	//Ray-cast and grab what is in reach
	void Grab();

	//Called when Grab key is released
	void Release();

	//Find attached Physics component
	void FindPhysicsComponent();

	//Setup Input component
	void SetUpInputComponent();

	//Return Current start of the Reach Line 
	FVector GetReachLineStart();

	//Returns Current end of the Reach Line
	FVector GetReachLineEnd();

	//Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
		
};
