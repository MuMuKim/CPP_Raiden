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

	//상태가 Playing이 아니라면 실행하지 않게한다.
	auto GameMode = Cast<ACRaidenGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	//사용자가 입력한 방향으로 이동하고 싶다.
	FVector dir(0, h, v);
	dir.Normalize();
	me->SetActorLocation(me->GetActorLocation() + dir * MoveSpeed * DeltaTime);

	//회전
	FRotator Rdir(0, 1, 0);
	me->SetActorRotation(me->GetActorRotation() + Rdir * 300 * DeltaTime);
}

void UPlayerMove::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//키입력에 따른 바인딩
	PlayerInputComponent->BindAxis("Horizontal", this, &UPlayerMove::InputHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &UPlayerMove::InputVertical);
}
//사용자가 좌우 키를 누르면 실행되는 함수
void UPlayerMove::InputHorizontal(float Value)
{
	h = Value;
}

//사용자가 상하 키를 누르면 실행되는 함수
void UPlayerMove::InputVertical(float Value)
{
	v = Value;
}

