// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaidenGameMode.h"

ACRaidenGameMode::ACRaidenGameMode()
{
	//Player가 들어가있음.
	DefaultPawnClass = NULL;
}

void ACRaidenGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < BulletPoolSize; ++i)
	{
		ABulletCPP* Bullet = CreateBullet();

		ADDBullet(Bullet);
	}
}

ABulletCPP* ACRaidenGameMode::CreateBullet()
{
	//생성되는 위치에 다른 액터가 있더라도 생성시킨다.
	FActorSpawnParameters pram;
	pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//월드 안에 있는 스폰액터 기능에 접근해 인자값으로 위치지정, Param이란 조건을 추가
	auto Bullet = GetWorld()->SpawnActor<ABulletCPP>(BulletFactory, FVector::ZeroVector, FRotator::ZeroRotator);

	return Bullet;
}

void ACRaidenGameMode::ADDBullet(ABulletCPP* Bullet)
{
	//같은놈은 넣지 않는 Uique
	BulletPool.AddUnique(Bullet);
	//총알을 비활성화 시킨다
	SetBulletActive(Bullet, false);
}

void ACRaidenGameMode::SetBulletActive(ABulletCPP* Bullet, bool IsActive)
{
	Bullet->SetActorHiddenInGame(!IsActive); //게임에서 안보이게 할것이냐?
	Bullet->SetActorEnableCollision(IsActive); //충돌을 킬것이냐?
	Bullet->SetActorTickEnabled(IsActive); //실행 시킬것이냐?
}

ABulletCPP* ACRaidenGameMode::GetBullet()
{
	//총알을 탄창에서 하나씩 넣어 가져온다(return)
	ABulletCPP* Bullet = BulletPool.Pop();
	
	return Bullet;
}

