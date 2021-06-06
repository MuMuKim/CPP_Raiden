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

	
};
