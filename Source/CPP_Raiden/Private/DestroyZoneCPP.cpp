// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZoneCPP.h"
#include "CRaidenGameMode.h"
#include "BulletCPP.h"
#include "PlayerCPP.h"

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
	//부딪힌 대상이 Player라면 함수를 실행시키지 않는다
	APlayerCPP* Player = Cast<APlayerCPP>(OtherActor);
	if (Player != nullptr)
	{
		return;
	}

	// 부딪힌 액터가 총알이라면 다시 탄창(Pool)에 넣어준다
	auto Bullet = Cast<ABulletCPP>(OtherActor);

	auto GameMode = Cast<ACRaidenGameMode>(GetWorld()->GetAuthGameMode());

	if (Bullet && IsValid(Bullet) && GameMode)
	{
		//재장전
		GameMode->ADDBullet(Bullet);
	}
	else
	{
		OtherActor->Destroy();
	}
}