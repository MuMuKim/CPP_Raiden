// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BulletCPP.h"
#include <GameFramework/Actor.h>
#include "CRaidenGameMode.generated.h"

//게임의 상태제어
//enum = 열거형
UENUM(BlueprintType)
enum class EGameState : uint8
{
	Ready UMETA(ThisPlayName = "READY_STATE"),
	Playing UMETA(ThisPlayName = "Playing_STATE"),
	GameOver UMETA(ThisPlayName = "GameOver_STATE")
};

UCLASS()
class CPP_RAIDEN_API ACRaidenGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACRaidenGameMode();
	virtual void Tick(float DeltaSeconds) override;

	//State 함수
	void ReadyPage(float DeltaSeconds);
	void PlayingPage();
	void GameOverPage();

	//GameMode가 제공해주는 함수(Begin보다 먼저 호출)
	virtual void InitGameState() override;

	virtual void BeginPlay() override;

	//총알을 만드는 함수
	ABulletCPP* CreateBullet();

	//총알을 추가하는 함수
	void ADDBullet(ABulletCPP* Bullet);

	//총알을 활성화 시키는 함수
	void SetBulletActive(ABulletCPP* Bullet, bool IsActive);

	//총알을 가져오는 함수
	UFUNCTION()
	ABulletCPP* GetBullet();

	//필요속성: 탄창크기, 탄창(Pool), 총알공장
	UPROPERTY(EditAnywhere, Category = "Bullet")
	int BulletPoolSize = 20;
	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	TArray <ABulletCPP*> BulletPool;
	UPROPERTY(EditAnywhere,Category = "BulletFactory")
	TSubclassOf<class ABulletCPP> BulletFactory;

	//PlayerFactory
	UPROPERTY(EditAnywhere, Category = "PlayerFactory")
	TSubclassOf<class APlayerCPP> PlayerFactory;

	//Screen에 상태를 보여주기 위한 함수
	UFUNCTION(BluePrintImplementableEvent,Category = "PrintLog")
	void PrintEnumDeta(EGameState value);

public:
	//캡슐화된 MState를 가져오기 위한 함수
	EGameState GetState()
	{
		return MState;
	}
	//캡슐화된 MState를 수정하기 위한 함수
	void SetState(EGameState s);

	//캡슐화된 현재점수에 Point를 넣을 함수
	void SetCurrentScore(int32 point);
	//캡슐화된 현재점수를 불러올 함수
	int32 GetCurrentScore();
	

private:
	//상태변화를 관리하는 변수
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "State", meta = (AllowPrivateAccess = ture))
	EGameState MState = EGameState::Ready;
	//경과시간이 되면 ReadyPage -> PlayingPage에 필요한 속성
	UPROPERTY(EditAnywhere, Category = "State", meta = (AllowPrivateAccess = ture))
	float ReadyTime = 2;
	UPROPERTY()
	float CrruntTime = 0;


	//ReadyUI 공장
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> ReadyUIFactory;
	//Ready UI를 재활용하기 위해 속성으로 등록
	class UUserWidget* ReadyUI;

	//StartUI 공장
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> StartUIFactory;
	//Start UI를 재활용하기 위해 속성으로 등록
	class UUserWidget* StartUI;

	//GameOverUI 공장
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> GameOverUIFactory;
	//Start UI를 재활용하기 위해 속성으로 등록
	class UUserWidget* GameOvertUI;

	//현재 점수를 담는 변수
	int32 CurScore = 0;
	//최고 점수를 담는 변수
	int32 TopScore = 0;
	
	//Score UI 공장
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> ScoreUIFactory;
	//ScoreUI를 재활용하기 위해 속성으로 등록
	class UScoreCPP* ScoreUI;
};
