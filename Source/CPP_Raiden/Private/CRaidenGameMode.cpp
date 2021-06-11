// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaidenGameMode.h"
#include "EnemyCPP.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include "PlayerCPP.h"
#include <Blueprint/UserWidget.h>
#include "ScoreCPP.h"
#include "SaveData.h"
#include <Engine/EngineTypes.h>
#include <Engine/World.h>

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
	//UE_LOG(LogTemp, Warning, TEXT("Tick STATE"));
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
	//UE_LOG(LogTemp, Warning, TEXT("READY STATE"));

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
	//UE_LOG(LogTemp, Warning, TEXT("Playing STATE"));

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

	//--------------------------------------------------------------------
	//SaveData �ε��ϱ�
	SaveData = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("TopScore"), 0));

	//�þ� ���嵥���Ͱ� ���ٸ�
	if (SaveData == nullptr)
	{
		//SaveData�� �ϳ������
		auto SaveGame = UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass());
		SaveData = Cast<USaveData>(SaveGame);
		//0���� �ʱ�ȭ
		SaveData->TopScore = 0;

		//���彽��
		UGameplayStatics::SaveGameToSlot(SaveData, TEXT("TopScore"), 0);
	}
	//TopScore�� �ε�� ������ �Ҵ�
	TopScore = SaveData->TopScore;

	if (ScoreUI)
	{
		//UI�� TopScore���
		ScoreUI->PrintTopScore(TopScore);
		//CurSore�� ó�� 0���� ��µǰ�
		ScoreUI->PrintCurrentScore(CurScore);
	}
}

void ACRaidenGameMode::BeginPlay()
{
	Super::BeginPlay();

	//(����ڵ�)
	if (BulletFactory) //������� 1
	{
		//�¾ �� �Ѿ� źâ�� �־����
		for (int32 i = 0; i < BulletPoolSize; ++i)
		{
			ABulletCPP* Bullet = CreateBullet();

			ADDBullet(Bullet);
		}
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

	//Score UI�� ����ϰ� ����
	ScoreUI = CreateWidget<UScoreCPP>(GetWorld(), ScoreUIFactory);
	//���� ScoreUI�� �� ���Դٸ�
	if (ScoreUI)
	{
		//Socre UI�� �����ְ�
		ScoreUI->AddToViewport();
		//CurScore�� ó�� 0���� ������
		ScoreUI->PrintCurrentScore(CurScore);
		//TopScore�� ���
		ScoreUI->PrintTopScore(TopScore);
	}
}

ABulletCPP* ACRaidenGameMode::CreateBullet() //������� 2
{
	FActorSpawnParameters pram;
	//�����Ǵ� ��ġ�� �ٸ����Ͱ� �ִ��� ������Ų��
	pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//���ӸŴ���(GetWorld)�ȿ� �ִ� �������ͱ�ɿ� ������ ���ڰ����� ��ġ�� �������ְ� pram�̶� ������ �߰�
	auto Bullet = GetWorld()->SpawnActor<ABulletCPP>(BulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, pram);

	return Bullet;
}

void ACRaidenGameMode::ADDBullet(ABulletCPP* Bullet) //������� 3
{
	//�������� ���� �ʴ� Uique
	BulletPool.AddUnique(Bullet);
	//�Ѿ��� ��Ȱ��ȭ ��Ų��
	SetBulletActive(Bullet, false);
}
	
void ACRaidenGameMode::SetBulletActive(ABulletCPP* Bullet, bool IsActive) //������� 4
{
	Bullet->SetActorHiddenInGame(!IsActive); //���ӿ��� �Ⱥ��̰� �Ұ��̳�?
	Bullet->SetActorEnableCollision(IsActive); //�浹�� ų���̳�?
	Bullet->SetActorTickEnabled(IsActive); //���� ��ų���̳�?

}

ABulletCPP* ACRaidenGameMode::GetBullet() //������� 5
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

void ACRaidenGameMode::SetCurrentScore(int32 point)
{
	//�������� �־��ֱ�
	CurScore = point;
	//UI�� ǥ�����ֱ�
	//->Score UI Widget �� ���� �Ҵ�����ش�
	ScoreUI->PrintCurrentScore(CurScore);
	
	//TopScore
	//->���������� �ְ������� ������ 
	if (CurScore > TopScore)
	{
		//���������� �ְ������� �ȴ�
		TopScore = CurScore;
		//Top Score �� �Ҵ�
		ScoreUI->PrintTopScore(TopScore);

		SaveData->TopScore = TopScore;
		UGameplayStatics::SaveGameToSlot(SaveData, TEXT("TopScore"),0);
	}
}

int32 ACRaidenGameMode::GetCurrentScore()
{
	return CurScore;
}

