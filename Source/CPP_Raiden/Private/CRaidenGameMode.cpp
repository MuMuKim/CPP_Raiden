// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaidenGameMode.h"
#include "EnemyCPP.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include "PlayerCPP.h"
#include <Blueprint/UserWidget.h>

ACRaidenGameMode::ACRaidenGameMode()
{
	//Tick�Լ��� ��� ȣ��ǵ��� ����
	PrimaryActorTick.bCanEverTick = true;
	//Player�� ������.
	DefaultPawnClass = NULL;
}
#pragma region Tick(Page)

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
		//ReadyUI�� �ִٸ� Playing���� �Ѿ �� UI�� ���ش�
		if (ReadyUI)
		{
			//Ready UI�� ���� ��,
			ReadyUI->RemoveFromViewport();			
		}

		//StartUI�� �ִٸ� Playing���� �Ѿ �� UI�� ���ش�
		if (StartUI)
		{
			//Ready UI�� ���� ��,
			StartUI->AddToViewport();
		}
	}
}


void ACRaidenGameMode::PlayingPage()
{
	UE_LOG(LogTemp, Warning, TEXT("Playing STATE"));

	//���� �ð��� ������ְ�,
	CrruntTime += GetWorld()->GetDeltaSeconds();
	//����ð��� �ȴٸ�
	if (CrruntTime >= 1)
	{
		//StartUI�� ���ش�.
		StartUI->RemoveFromViewport();

		CrruntTime = 0;
	}
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
#pragma endregion

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

	//ReadyUI�� �ִٸ� ReadyUIȭ�鿡 ���
	if (ReadyUI)
	{
		//ȭ�鿡 ���̰��ϱ�
		ReadyUI->AddToViewport();
	}
}

void ACRaidenGameMode::BeginPlay()
{
	Super::BeginPlay();

	//�¾ �� �Ѿ� źâ�� �־����
	for (int32 i = 0; i < BulletPoolSize; ++i)
	{
		ABulletCPP* Bullet = CreateBullet();

		ADDBullet(Bullet);
	}

	//����ڵ�(ReadyUIFactory�� Null�� �ƴ϶��)
	if (ReadyUIFactory)
	{
		//ReadyUI�� ����� �ʹ�
		ReadyUI = CreateWidget<UUserWidget>(GetWorld(), ReadyUIFactory);
		//ȭ�鿡 ���̰� �ϱ�
		ReadyUI->AddToViewport();
	}

	//����ڵ�(ReadyUIFactory�� Null�� �ƴ϶��)
	if (StartUIFactory)
	{
		//ReadyUI�� ����� �ʹ�
		StartUI = CreateWidget<UUserWidget>(GetWorld(), StartUIFactory);
	}

	//����ڵ�(ReadyUIFactory�� Null�� �ƴ϶��)
	if (GameOverUIFactory)
	{
		//ReadyUI�� ����� �ʹ�
		GameOvertUI = CreateWidget<UUserWidget>(GetWorld(), GameOverUIFactory);
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

void ACRaidenGameMode::SetState(EGameState s)
{
	MState = s;

	//MStet�� GameOver���°� �Ǿ��ٸ�
	if (MState == EGameState::GameOver)
	{
		//������ �Ͻ����� �ϰ�
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		//���콺Ŀ���� ���̰��Ѵ�
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		//GameOverUI�� ���̰��Ѵ�
		GameOvertUI->AddToViewport();
	}
}


