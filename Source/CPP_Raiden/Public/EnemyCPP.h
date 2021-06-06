// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Sound/SoundBase.h>
#include "EnemyCPP.generated.h"

UCLASS()
class CPP_RAIDEN_API AEnemyCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//몸체
	UPROPERTY(VisibleAnywhere, Category = "Body")
	class UBoxComponent* BoxComp;
	//외관
	UPROPERTY(VisibleAnywhere,Category = "Body")
	class UStaticMeshComponent* MeshComp;

	//계속 이동하고 싶다
	//->랜덤한 확률로 타겟방향으로
	//->랜덤한 확률로 아래방향으로
	//이동속도
	UPROPERTY(EditAnywhere,Category = "Setting")
	float MoveSpeed = 700;
	//이동방향
	FVector Dir; 
	//확률
	UPROPERTY(EditAnywhere,Category = "Setting")
	int32 TraceRate = 50;

	//적이 다른 물체와 충돌했을 때 처리를 하고 싶다.
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//다른 물체와 충돌했을 때 폭발 효과를 발생시키고 싶다
	UPROPERTY(EditAnywhere, Category = "Setting")
	class UParticleSystem* ExplosionFactory;

	//폭발사운드
	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* ExSound;

	//Player를 담을 변수
	UPROPERTY()
	class AActor* Target;
};
