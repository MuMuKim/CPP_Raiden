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

	//��ü
	UPROPERTY(VisibleAnywhere, Category = "Body")
	class UBoxComponent* BoxComp;
	//�ܰ�
	UPROPERTY(VisibleAnywhere,Category = "Body")
	class UStaticMeshComponent* MeshComp;

	//��� �̵��ϰ� �ʹ�
	//->������ Ȯ���� Ÿ�ٹ�������
	//->������ Ȯ���� �Ʒ���������
	//�̵��ӵ�
	UPROPERTY(EditAnywhere,Category = "Setting")
	float MoveSpeed = 700;
	//�̵�����
	FVector Dir; 
	//Ȯ��
	UPROPERTY(EditAnywhere,Category = "Setting")
	int32 TraceRate = 50;

	//���� �ٸ� ��ü�� �浹���� �� ó���� �ϰ� �ʹ�.
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//�ٸ� ��ü�� �浹���� �� ���� ȿ���� �߻���Ű�� �ʹ�
	UPROPERTY(EditAnywhere, Category = "Setting")
	class UParticleSystem* ExplosionFactory;

	//���߻���
	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* ExSound;

	//Player�� ���� ����
	UPROPERTY()
	class AActor* Target;
};
