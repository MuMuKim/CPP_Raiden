// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerCPP.generated.h"

UCLASS()
class CPP_RAIDEN_API AEnemyManagerCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagerCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//���� �ð����� Enemy�� �����ϰ� �ʹ�
	//�����ð� 
	UPROPERTY(EditAnywhere, Category = "Setting")
	float CreateTime = 2;
	//����ð�
	float CurrentTime = 0;
	//������
	UPROPERTY(EditAnywhere, Category = "Setting")
	TSubclassOf<class AEnemyCPP>EnemyFactory;
};
