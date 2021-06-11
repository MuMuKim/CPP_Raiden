// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BulletCPP.h"
#include <GameFramework/Actor.h>
#include "CRaidenGameMode.generated.h"

//������ ��������
//enum = ������
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

	//State �Լ�
	void ReadyPage(float DeltaSeconds);
	void PlayingPage();
	void GameOverPage();

	//GameMode�� �������ִ� �Լ�(Begin���� ���� ȣ��)
	virtual void InitGameState() override;

	virtual void BeginPlay() override;

	//�Ѿ��� ����� �Լ�
	ABulletCPP* CreateBullet();

	//�Ѿ��� �߰��ϴ� �Լ�
	void ADDBullet(ABulletCPP* Bullet);

	//�Ѿ��� Ȱ��ȭ ��Ű�� �Լ�
	void SetBulletActive(ABulletCPP* Bullet, bool IsActive);

	//�Ѿ��� �������� �Լ�
	UFUNCTION()
	ABulletCPP* GetBullet();

	//�ʿ�Ӽ�: źâũ��, źâ(Pool), �Ѿ˰���
	UPROPERTY(EditAnywhere, Category = "Bullet")
	int BulletPoolSize = 20;
	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	TArray <ABulletCPP*> BulletPool;
	UPROPERTY(EditAnywhere,Category = "BulletFactory")
	TSubclassOf<class ABulletCPP> BulletFactory;

	//PlayerFactory
	UPROPERTY(EditAnywhere, Category = "PlayerFactory")
	TSubclassOf<class APlayerCPP> PlayerFactory;

	//Screen�� ���¸� �����ֱ� ���� �Լ�
	UFUNCTION(BluePrintImplementableEvent,Category = "PrintLog")
	void PrintEnumDeta(EGameState value);

public:
	//ĸ��ȭ�� MState�� �������� ���� �Լ�
	EGameState GetState()
	{
		return MState;
	}
	//ĸ��ȭ�� MState�� �����ϱ� ���� �Լ�
	void SetState(EGameState s);

	//ĸ��ȭ�� ���������� Point�� ���� �Լ�
	void SetCurrentScore(int32 point);
	//ĸ��ȭ�� ���������� �ҷ��� �Լ�
	int32 GetCurrentScore();
	

private:
	//���º�ȭ�� �����ϴ� ����
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "State", meta = (AllowPrivateAccess = ture))
	EGameState MState = EGameState::Ready;
	//����ð��� �Ǹ� ReadyPage -> PlayingPage�� �ʿ��� �Ӽ�
	UPROPERTY(EditAnywhere, Category = "State", meta = (AllowPrivateAccess = ture))
	float ReadyTime = 2;
	UPROPERTY()
	float CrruntTime = 0;


	//ReadyUI ����
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> ReadyUIFactory;
	//Ready UI�� ��Ȱ���ϱ� ���� �Ӽ����� ���
	class UUserWidget* ReadyUI;

	//StartUI ����
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> StartUIFactory;
	//Start UI�� ��Ȱ���ϱ� ���� �Ӽ����� ���
	class UUserWidget* StartUI;

	//GameOverUI ����
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> GameOverUIFactory;
	//Start UI�� ��Ȱ���ϱ� ���� �Ӽ����� ���
	class UUserWidget* GameOvertUI;

	//���� ������ ��� ����
	int32 CurScore = 0;
	//�ְ� ������ ��� ����
	int32 TopScore = 0;
	
	//Score UI ����
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> ScoreUIFactory;
	//ScoreUI�� ��Ȱ���ϱ� ���� �Ӽ����� ���
	class UScoreCPP* ScoreUI;
};
