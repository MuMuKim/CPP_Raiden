// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
ABulletCPP::ABulletCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��ü
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComp;
	//�ܰ�
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(BoxComp);
	//Root�� ��ġ���ʰ� �ڽ� Collision ���ֱ�
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABulletCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

//��� ���� �̵��ϰ� �ʹ�
void ABulletCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//����
	FVector dir(0, 0, 1);
	//P = P0 + vt, Sweep(ture)
	SetActorLocation(GetActorLocation() + dir * Speed * DeltaTime,true);

}

