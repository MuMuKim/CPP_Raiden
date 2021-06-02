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

	//��ü
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComp;
	//�ܰ�
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(BoxComp);
		
}

// Called when the game starts or when spawned
void AEnemyCPP::BeginPlay()
{
	Super::BeginPlay();
	
	// �¾ �� �ѹ� ������ ���Ѵ�
	int32 Ran = FMath::RandRange(1, 100);
	
	if (Ran <= TraceRate)
	{
		//Ÿ�ٹ��ⱸ�ϱ�
		
		//���忡�� playerã��
		for (TActorIterator<APlayerCPP> it(GetWorld()); it; ++it)
		{
			Dir = it->GetActorLocation() - GetActorLocation();
		}
	}
	else
	{
		//�Ʒ�����
		Dir = FVector(0, 0, -1);
	}
	Dir.Normalize();
}

// Called every frame
void AEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//��ư��鼭 ��� �� �������� �̵��ϰ� �ʹ�
	//P = P0 + vt, Sweep
	SetActorLocation(GetActorLocation() + Dir * DeltaTime * MoveSpeed, true);
}

