// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/InputComponent.h>
#include "PlayerMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_RAIDEN_API UPlayerMove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// ������� �Է��� ó���� �Լ�(�ݹ�)
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	//�ʿ��� : ����,�¿� �Է� �޴� ��� (binding)
	void InputHorizontal(float Value);
	void InputVertical(float Value);

	//����� �Է¿� ���� �����¿� �̵�
	//�ʿ�Ӽ� : �̵��ӵ�, �̵�����
	float MoveSpeed = 500;
	float h = 0;
	float v = 0;
	
	//�� ������Ʈ�� �����ϰ� �ִ� ����
	class APlayerCPP* me;
};
