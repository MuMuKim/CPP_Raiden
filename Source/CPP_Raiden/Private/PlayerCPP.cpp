// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include "BulletCPP.h"
#include <Kismet/GameplayStatics.h>
#include "CPP_RaidenGameModeBase.h"
#include "CRaidenGameMode.h"
#include "PlayerMove.h"
#include "PlayerFire.h"


// Sets default values
APlayerCPP::APlayerCPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//속성에 사용할 컴포넌트를 선언해놨다.
	//구현부에서 추가해주기

	//몸체(루트 컴포넌트)
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComp;

	//외관(루트의 자식으로)
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(BoxComp);
	//Root와 겹치지않게 자식 Collision 없애기
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//총구(루트의 자식으로)
	FirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(RootComponent);

	//PlayerMove 컴포넌트 할당
	PlayerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));

	//PlayerFire 컴포넌트 할당
	PlayerFire = CreateDefaultSubobject<UPlayerFire>(TEXT("PlayerFire"));

}

// Called when the game starts or when spawned
void APlayerCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

//사용자의 입력매핑과 처리할 함수를 묶어주는(bind) 역할을 하는 함수
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//PlayerMove 컴포넌트에서 이동 실행
	PlayerMove->SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerFire 컴포넌트에서 이동 실행
	PlayerFire->SetupPlayerInputComponent(PlayerInputComponent);
}	



