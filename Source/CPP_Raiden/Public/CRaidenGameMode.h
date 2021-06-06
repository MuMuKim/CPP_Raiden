// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BulletCPP.h"
#include <GameFramework/Actor.h>
#include "CRaidenGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPP_RAIDEN_API ACRaidenGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACRaidenGameMode();

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

	
};
