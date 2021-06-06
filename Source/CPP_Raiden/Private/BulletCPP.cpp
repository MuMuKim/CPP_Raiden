// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
ABulletCPP::ABulletCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//몸체
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComp;
	//외관
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(BoxComp);
	//Root와 겹치지않게 자식 Collision 없애기
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABulletCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

//계속 위로 이동하고 싶다
void ABulletCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//방향
	FVector dir(0, 0, 1);
	//P = P0 + vt, Sweep(ture)
	SetActorLocation(GetActorLocation() + dir * Speed * DeltaTime,true);

}

