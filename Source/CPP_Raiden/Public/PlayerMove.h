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
	// 사용자의 입력을 처리할 함수(콜백)
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	//필요기능 : 상하,좌우 입력 받는 기능 (binding)
	void InputHorizontal(float Value);
	void InputVertical(float Value);

	//사용자 입력에 따라 상하좌우 이동
	//필요속성 : 이동속도, 이동방향
	float MoveSpeed = 500;
	float h = 0;
	float v = 0;
	
	//이 컴포넌트를 소유하고 있는 액터
	class APlayerCPP* me;
};
