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
	//��ü(�浹 ����)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Body")
	class UBoxComponent* BoxComp;
		
	//�ܰ�
	UPROPERTY(VisibleAnywhere,Category = "Body")
	class UStaticMeshComponent* MeshComp;

	//�ѱ�
	UPROPERTY(VisibleAnywhere,Category = "Body")
	class UArrowComponent* FirePosition;

	//PlayerMove ������Ʈ �߰�
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPlayerMove* PlayerMove;

	//PlayerFire ������Ʈ �߰�
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPlayerFire* PlayerFire;
};
