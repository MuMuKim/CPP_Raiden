// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerCPP.h"
#include "EnemyCPP.h"
#include "CRaidenGameMode.h"

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

	//Playing상태가 아니라면 함수를 끝낸다(실행시키지 않는다)
	auto GameMode = Cast<ACRaidenGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	//생성시간이 되면 Enemy를 만들고 싶다
	CurrentTime += DeltaTime;

	if (CurrentTime > CreateTime)
	{
		// 적을 만들고 싶다
		FActorSpawnParameters pram;
		pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AEnemyCPP>(EnemyFactory, GetActorLocation(), GetActorRotation(), pram);

		//경과시간 초기화
		CurrentTime = 0;
	}
}

