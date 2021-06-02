// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerCPP.h"
#include "EnemyCPP.h"

// Sets default values
AEnemyManagerCPP::AEnemyManagerCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManagerCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManagerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//�����ð��� �Ǹ� Enemy�� ����� �ʹ�

	CurrentTime += DeltaTime;

	if (CurrentTime > CreateTime)
	{
		// ���� ����� �ʹ�
		FActorSpawnParameters pram;
		pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AEnemyCPP>(EnemyFactory, GetActorLocation(), GetActorRotation(), pram);

		//����ð� �ʱ�ȭ
		CurrentTime = 0;
	}
}

