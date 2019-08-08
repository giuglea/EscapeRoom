// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstC.h"


// Sets default values for this component's properties
UFirstC::UFirstC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UFirstC::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	FString ObjectPosition = GetOwner()->GetTransform().GetLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("This %s is at %s"), *ObjectName,*ObjectPosition);
	
	// ...
	
}


// Called every frame
void UFirstC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

