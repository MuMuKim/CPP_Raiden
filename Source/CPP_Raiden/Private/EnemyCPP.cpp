// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCPP.h"
#include <Components/BoxComponent.h>

#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"
#include <EngineUtils.h>
// Sets default values
AEnemyCPP::AEnemyCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//몸체
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComp;
	//외관
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(BoxComp);
		
}

// Called when the game starts or when spawned
void AEnemyCPP::BeginPlay()
{
	Super::BeginPlay();
	
	// 태어날 때 한번 방향을 구한다
	int32 Ran = FMath::RandRange(1, 100);
	
	if (Ran <= TraceRate)
	{
		//타겟방향구하기
		
		//월드에서 player찾기
		for (TActorIterator<APlayerCPP> it(GetWorld()); it; ++it)
		{
			Dir = it->GetActorLocation() - GetActorLocation();
		}
	}
	else
	{
		//아래방향
		Dir = FVector(0, 0, -1);
	}
	Dir.Normalize();
}

// Called every frame
void AEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//살아가면서 계속 그 방향으로 이동하고 싶다
	//P = P0 + vt, Sweep
	SetActorLocation(GetActorLocation() + Dir * DeltaTime * MoveSpeed, true);
}

