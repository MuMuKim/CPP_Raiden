// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaidenGameMode.h"
#include "EnemyCPP.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include "PlayerCPP.h"

ACRaidenGameMode::ACRaidenGameMode()
{
	//Tick�Լ��� ��� ȣ��ǵ��� ����
	PrimaryActorTick.bCanEverTick = true;
	//Player�� ������.
	DefaultPawnClass = NULL;
}

void ACRaidenGameMode::Tick(float DeltaSeconds)
{

	PrintEnumDeta(MState);
	UE_LOG(LogTemp, Warning, TEXT("Tick STATE"));
	// switch������ �Լ� �̵���� �����
	switch (MState)
	{
	case EGameState::Ready:
		ReadyPage(DeltaSeconds);
		break;
	case EGameState::Playing:
		PlayingPage();
		break;
	case EGameState::GameOver:
		GameOverPage();
		break;
	}
}

void ACRaidenGameMode::ReadyPage(float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("READY STATE"));

	//��� �ð��� �Ǹ� PlayingPage�� �Ѿ�� �ʹ�
	CrruntTime += GetWorld()->GetDeltaSeconds();

	if (CrruntTime >= ReadyTime)
	{
		MState = EGameState::Playing;

		CrruntTime = 0;
	}
}


void ACRaidenGameMode::PlayingPage()
{
	UE_LOG(LogTemp, Warning, TEXT("Playing STATE"));
}

void ACRaidenGameMode::GameOverPage()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOver STATE"));
	//Player Controller��������
	APlayerController* MyCtrl = GetWorld()->GetFirstPlayerController();

	//����ڵ尡 �ְ�, RŰ�� �����ٸ� Reset
	if (MyCtrl && MyCtrl->WasInputKeyJustPressed(EKeys::R))
	{
		ResetLevel();
	}
}

void ACRaidenGameMode::InitGameState()
{
	Super::InitGameState();

	//1. ȭ�鿡 Enemy�� �ִٸ� �� ����
	//����� it;�� ù��°�ּ�(�����ּ�)�� �� �����Ͱ� �ִ��� Ȯ��(ture���� ����), ++it�� ���� �ּҷ� �Ѿ�� ��
	//���� : ����󿡼� AEnemy�� �� �ܾ�´� - �����ּҺ��� �� ũ�⸸ŭ ����
	for (TActorIterator<AEnemyCPP> it(GetWorld()); it; ++it)
	{
		it->Destroy();
	}
	//2. ȭ�鿡 �Ѿ��� ������ �� Ǯ���ش�
	for (TActorIterator<ABulletCPP> it(GetWorld()); it; ++it)
	{
		ADDBullet(*it);

		/*ABulletCPP* Bullet = *it;
		ADDBullet(Bullet);*/
	}
	//3. Player�� ������ ������ش�
	//->����� Player�� ã�ƺ���
	auto PlayerObj = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCPP::StaticClass());
	//->2 ���� ����� Player�� ���ٸ�
	// ��� GameOver�� �Ǿ��ٸ� ������ Player�� ���� ������ ���ǿ� GameOver���� Ȯ�θ� ���ָ� ��.
	if (MState == EGameState::GameOver && PlayerObj == nullptr)
	{
		//->3 Player�� ����� �ʹ�
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//PlayerFactory�� ���� �ʿ���� DefaultPawnClass�� �־��ָ� ��
		auto Ctrl = GetWorld()->SpawnActor<APlayerCPP>(PlayerFactory, FVector::ZeroVector, FRotator::ZeroRotator);
		
		//�������� ������� Spawn���� Actor���� ����(Possess)���ش�
		GetWorld()->GetFirstPlayerController()->Possess(Ctrl);
	}

	//4 ���������� ���¸� Ready �� ��ȯ���ش�
	MState = EGameState::Ready;
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

