// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaidenGameMode.h"
#include "EnemyCPP.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include "PlayerCPP.h"

ACRaidenGameMode::ACRaidenGameMode()
{
	//Tick함수가 계속 호출되도록 설정
	PrimaryActorTick.bCanEverTick = true;
	//Player가 들어가있음.
	DefaultPawnClass = NULL;
}

void ACRaidenGameMode::Tick(float DeltaSeconds)
{

	PrintEnumDeta(MState);
	UE_LOG(LogTemp, Warning, TEXT("Tick STATE"));
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
	UE_LOG(LogTemp, Warning, TEXT("READY STATE"));

	//경과 시간이 되면 PlayingPage로 넘어가고 싶다
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
	//Player Controller가져오기
	APlayerController* MyCtrl = GetWorld()->GetFirstPlayerController();

	//방어코드가 있고, R키를 눌렀다면 Reset
	if (MyCtrl && MyCtrl->WasInputKeyJustPressed(EKeys::R))
	{
		ResetLevel();
	}
}

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

