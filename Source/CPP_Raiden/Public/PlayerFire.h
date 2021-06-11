// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerFire.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_RAIDEN_API UPlayerFire : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// ������� �Է��� ó���� �Լ�(�ݹ�)
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	//�Ѿ�Sound
	UPROPERTY(EditAnywhere,Category="Audio")
	class USoundBase* BulletSound;

	//����ڰ� �߻��ư�� ������ Bullet�� �߻��ϴ� ���
	void Fire();

	//�� ������Ʈ�� �����ϰ� �ִ� ����
	UPROPERTY()
	class APlayerCPP* me;
};
