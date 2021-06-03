// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZoneCPP.h"

// Sets default values
ADestroyZoneCPP::ADestroyZoneCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestroyZoneCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyZoneCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZoneCPP::NotifyActorBeginOverlap(AActor* OtherActor)
{
	OtherActor->Destroy();
}