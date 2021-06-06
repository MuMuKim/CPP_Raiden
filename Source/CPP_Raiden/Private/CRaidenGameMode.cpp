// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaidenGameMode.h"

ACRaidenGameMode::ACRaidenGameMode()
{
	//Player�� ������.
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
	//�����Ǵ� ��ġ�� �ٸ� ���Ͱ� �ִ��� ������Ų��.
	FActorSpawnParameters pram;
	pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//���� �ȿ� �ִ� �������� ��ɿ� ������ ���ڰ����� ��ġ����, Param�̶� ������ �߰�
	auto Bullet = GetWorld()->SpawnActor<ABulletCPP>(BulletFactory, FVector::ZeroVector, FRotator::ZeroRotator);

	return Bullet;
}

void ACRaidenGameMode::ADDBullet(ABulletCPP* Bullet)
{
	//�������� ���� �ʴ� Uique
	BulletPool.AddUnique(Bullet);
	//�Ѿ��� ��Ȱ��ȭ ��Ų��
	SetBulletActive(Bullet, false);
}

void ACRaidenGameMode::SetBulletActive(ABulletCPP* Bullet, bool IsActive)
{
	Bullet->SetActorHiddenInGame(!IsActive); //���ӿ��� �Ⱥ��̰� �Ұ��̳�?
	Bullet->SetActorEnableCollision(IsActive); //�浹�� ų���̳�?
	Bullet->SetActorTickEnabled(IsActive); //���� ��ų���̳�?
}

ABulletCPP* ACRaidenGameMode::GetBullet()
{
	//�Ѿ��� źâ���� �ϳ��� �־� �����´�(return)
	ABulletCPP* Bullet = BulletPool.Pop();
	
	return Bullet;
}

