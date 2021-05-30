// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCPP.generated.h"

UCLASS()
class CPP_RAIDEN_API APlayerCPP : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//몸체(충돌 목적)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Body")
	class UBoxComponent* BoxComp;
		
	//외관
	UPROPERTY(VisibleAnywhere,Category = "Body")
	class UStaticMeshComponent* MeshComp;

	//사용자 입력에 따라 상하좌우 이동
	//필요속성 : 이동속도, 이동방향
	float MoveSpeed = 500;
	float h = 0;
	float v = 0;
	//필요기능 : 상하,좌우 입력 받는 기능 (binding)
	void InputHorizontal(float Value);
	void InputVertical(float Value);

};
