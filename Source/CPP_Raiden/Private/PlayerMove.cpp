// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "CRaidenGameMode.h"
#include "PlayerCPP.h"

// Sets default values for this component's properties
UPlayerMove::UPlayerMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<APlayerCPP>(GetOwner());
	
}


// Called every frame
void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//���°� Playing�� �ƴ϶�� �������� �ʰ��Ѵ�.
	auto GameMode = Cast<ACRaidenGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	//����ڰ� �Է��� �������� �̵��ϰ� �ʹ�.
	FVector dir(0, h, v);
	dir.Normalize();
	me->SetActorLocation(me->GetActorLocation() + dir * MoveSpeed * DeltaTime);

	//ȸ��
	FRotator Rdir(0, 1, 0);
	me->SetActorRotation(me->GetActorRotation() + Rdir * 300 * DeltaTime);
}

void UPlayerMove::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//Ű�Է¿� ���� ���ε�
	PlayerInputComponent->BindAxis("Horizontal", this, &UPlayerMove::InputHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &UPlayerMove::InputVertical);
}
//����ڰ� �¿� Ű�� ������ ����Ǵ� �Լ�
void UPlayerMove::InputHorizontal(float Value)
{
	h = Value;
}

//����ڰ� ���� Ű�� ������ ����Ǵ� �Լ�
void UPlayerMove::InputVertical(float Value)
{
	v = Value;
}

