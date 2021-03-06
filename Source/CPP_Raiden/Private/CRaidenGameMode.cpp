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
	//Tick함수가 계속 호출되도록 설정
	PrimaryActorTick.bCanEverTick = true;
	//Player가 들어가있음.
	DefaultPawnClass = NULL;
}
#pragma region Tick(Page)

void ACRaidenGameMode::Tick(float DeltaSeconds)
{

	PrintEnumDeta(MState);
	//UE_LOG(LogTemp, Warning, TEXT("Tick STATE"));
	// switch문으로 함수 이동제어문 만들기
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

	//경과 시간이 되면 PlayingPage로 넘어가고 싶다
	CrruntTime += GetWorld()->GetDeltaSeconds();

	if (CrruntTime >= ReadyTime)
	{
		MState = EGameState::Playing;
		
		CrruntTime = 0;
		//ReadyUI가 있다면 Playing으로 넘어갈 시 UI를 꺼준다
		if (ReadyUI)
		{
			//Ready UI를 꺼준 후,
			ReadyUI->RemoveFromViewport();			
		}

		//StartUI가 있다면 Playing으로 넘어갈 시 UI를 켜준다
		if (StartUI)
		{
			//Ready UI를 꺼준 후,
			StartUI->AddToViewport();
		}
	}
}


void ACRaidenGameMode::PlayingPage()
{
	//UE_LOG(LogTemp, Warning, TEXT("Playing STATE"));

	//현재 시간을 만들어주고,
	CrruntTime += GetWorld()->GetDeltaSeconds();
	//경과시간이 된다면
	if (CrruntTime >= 1)
	{
		//StartUI를 꺼준다.
		StartUI->RemoveFromViewport();
		CrruntTime = 0;
	}
}

void ACRaidenGameMode::GameOverPage()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOver STATE"));
	//Player Controller가져오기
	APlayerController* MyCtrl = GetWorld()->GetFirstPlayerController();

	//방어코드가 있고, R키를 눌렀다면 Reset
	if (MyCtrl && MyCtrl->WasInputKeyJustPressed(EKeys::R))
	{
		ResetLevel();
	}
}
#pragma endregion

void ACRaidenGameMode::InitGameState()
{
	Super::InitGameState();

	//1. 화면에 Enemy가 있다면 다 제거
	//가운데에 it;는 첫번째주소(시작주소)로 들어가 데이터가 있는지 확인(ture여야 실행), ++it는 다음 주소로 넘어가는 뜻
	//정리 : 월드상에서 AEnemy를 싹 긁어온다 - 시작주소부터 방 크기만큼 돈다
	for (TActorIterator<AEnemyCPP> it(GetWorld()); it; ++it)
	{
		it->Destroy();
	}
	//2. 화면에 총알이 있으면 다 풀해준다
	for (TActorIterator<ABulletCPP> it(GetWorld()); it; ++it)
	{
		ADDBullet(*it);

		/*ABulletCPP* Bullet = *it;
		ADDBullet(Bullet);*/
	}
	//3. Player가 없으면 만들어준다
	//->월드상에 Player를 찾아본다
	auto PlayerObj = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCPP::StaticClass());
	//->2 만약 월드상에 Player가 없다면
	// 사실 GameOver가 되었다면 무조건 Player는 없기 때문에 조건에 GameOver인지 확인만 해주면 됨.
	if (MState == EGameState::GameOver && PlayerObj == nullptr)
	{
		//->3 Player를 만들고 싶다
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//PlayerFactory를 해줄 필요없이 DefaultPawnClass를 넣어주면 됌
		auto Ctrl = GetWorld()->SpawnActor<APlayerCPP>(PlayerFactory, FVector::ZeroVector, FRotator::ZeroRotator);
		
		//조종권을 얻기위해 Spawn해준 Actor에서 빙의(Possess)해준다
		GetWorld()->GetFirstPlayerController()->Possess(Ctrl);
	}

	//4 마지막으로 상태를 Ready 로 전환해준다
	MState = EGameState::Ready;

	//ReadyUI가 있다면 ReadyUI화면에 출력
	if (ReadyUI)
	{
		//화면에 보이게하기
		ReadyUI->AddToViewport();
	}

	//--------------------------------------------------------------------
	//SaveData 로드하기
	SaveData = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("TopScore"), 0));

	//먄약 저장데이터가 없다면
	if (SaveData == nullptr)
	{
		//SaveData를 하나만든다
		auto SaveGame = UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass());
		SaveData = Cast<USaveData>(SaveGame);
		//0으로 초기화
		SaveData->TopScore = 0;

		//저장슬롯
		UGameplayStatics::SaveGameToSlot(SaveData, TEXT("TopScore"), 0);
	}
	//TopScore에 로드된 데이터 할당
	TopScore = SaveData->TopScore;

	if (ScoreUI)
	{
		//UI에 TopScore출력
		ScoreUI->PrintTopScore(TopScore);
		//CurSore가 처음 0으로 출력되게
		ScoreUI->PrintCurrentScore(CurScore);
	}
}

void ACRaidenGameMode::BeginPlay()
{
	Super::BeginPlay();

	//(방어코드)
	if (BulletFactory) //실행순서 1
	{
		//태어날 때 총알 탄창에 넣어놓기
		for (int32 i = 0; i < BulletPoolSize; ++i)
		{
			ABulletCPP* Bullet = CreateBullet();

			ADDBullet(Bullet);
		}
	}
	

	//방어코드(ReadyUIFactory가 Null이 아니라면)
	if (ReadyUIFactory)
	{
		//ReadyUI를 만들고 싶다
		ReadyUI = CreateWidget<UUserWidget>(GetWorld(), ReadyUIFactory);
		//화면에 보이게 하기
		ReadyUI->AddToViewport();
	}

	//방어코드(ReadyUIFactory가 Null이 아니라면)
	if (StartUIFactory)
	{
		//ReadyUI를 만들고 싶다
		StartUI = CreateWidget<UUserWidget>(GetWorld(), StartUIFactory);
	}

	//방어코드(ReadyUIFactory가 Null이 아니라면)
	if (GameOverUIFactory)
	{
		//ReadyUI를 만들고 싶다
		GameOvertUI = CreateWidget<UUserWidget>(GetWorld(), GameOverUIFactory);
	}

	//Score UI를 등록하고 생성
	ScoreUI = CreateWidget<UScoreCPP>(GetWorld(), ScoreUIFactory);
	//만약 ScoreUI가 잘 들어왔다면
	if (ScoreUI)
	{
		//Socre UI를 보여주고
		ScoreUI->AddToViewport();
		//CurScore가 처음 0으로 나오게
		ScoreUI->PrintCurrentScore(CurScore);
		//TopScore를 출력
		ScoreUI->PrintTopScore(TopScore);
	}
}

ABulletCPP* ACRaidenGameMode::CreateBullet() //실행순서 2
{
	FActorSpawnParameters pram;
	//생성되는 위치에 다른액터가 있더라도 생성시킨다
	pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//게임매니저(GetWorld)안에 있는 스폰액터기능에 접근해 인자값으로 위치를 지정해주고 pram이란 조건을 추가
	auto Bullet = GetWorld()->SpawnActor<ABulletCPP>(BulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, pram);

	return Bullet;
}

void ACRaidenGameMode::ADDBullet(ABulletCPP* Bullet) //실행순서 3
{
	//같은놈은 넣지 않는 Uique
	BulletPool.AddUnique(Bullet);
	//총알을 비활성화 시킨다
	SetBulletActive(Bullet, false);
}
	
void ACRaidenGameMode::SetBulletActive(ABulletCPP* Bullet, bool IsActive) //실행순서 4
{
	Bullet->SetActorHiddenInGame(!IsActive); //게임에서 안보이게 할것이냐?
	Bullet->SetActorEnableCollision(IsActive); //충돌을 킬것이냐?
	Bullet->SetActorTickEnabled(IsActive); //실행 시킬것이냐?

}

ABulletCPP* ACRaidenGameMode::GetBullet() //실행순서 5
{
	//총알을 탄창에서 하나씩 넣어 가져온다(return)
	ABulletCPP* Bullet = BulletPool.Pop();
	
	return Bullet;
}

void ACRaidenGameMode::SetState(EGameState s)
{
	MState = s;

	//MStet가 GameOver상태가 되었다면
	if (MState == EGameState::GameOver)
	{
		//게임을 일시정지 하고
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		//마우스커서를 보이게한다
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		//GameOverUI를 보이게한다
		GameOvertUI->AddToViewport();
	}
}

void ACRaidenGameMode::SetCurrentScore(int32 point)
{
	//현재점수 넣어주기
	CurScore = point;
	//UI에 표시해주기
	//->Score UI Widget 에 값을 할당시켜준다
	ScoreUI->PrintCurrentScore(CurScore);
	
	//TopScore
	//->현재점수가 최고점수를 넘으면 
	if (CurScore > TopScore)
	{
		//현재점수가 최고점수가 된다
		TopScore = CurScore;
		//Top Score 값 할당
		ScoreUI->PrintTopScore(TopScore);

		SaveData->TopScore = TopScore;
		UGameplayStatics::SaveGameToSlot(SaveData, TEXT("TopScore"),0);
	}
}

int32 ACRaidenGameMode::GetCurrentScore()
{
	return CurScore;
}

