// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletCPP.generated.h"

UCLASS()
class CPP_RAIDEN_API ABulletCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//��ü(�浹 ����)
	UPROPERTY(VisibleAnywhere, Category = "Body")
	class UBoxComponent* BoxComp;

	//�ܰ�
	UPROPERTY(VisibleAnywhere, Category = "Body")
	class UStaticMeshComponent* MeshComp;

	//�̵��ӵ�
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed = 1000;

};
