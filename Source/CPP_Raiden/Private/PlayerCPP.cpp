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

	//�Ӽ��� ����� ������Ʈ�� �����س���.
	//�����ο��� �߰����ֱ�

	//��ü(��Ʈ ������Ʈ)
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComp;

	//�ܰ�(��Ʈ�� �ڽ�����)
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(BoxComp);
	//Root�� ��ġ���ʰ� �ڽ� Collision ���ֱ�
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//�ѱ�(��Ʈ�� �ڽ�����)
	FirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(RootComponent);

	//PlayerMove ������Ʈ �Ҵ�
	PlayerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));

	//PlayerFire ������Ʈ �Ҵ�
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

//������� �Է¸��ΰ� ó���� �Լ��� �����ִ�(bind) ������ �ϴ� �Լ�
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//PlayerMove ������Ʈ���� �̵� ����
	PlayerMove->SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerFire ������Ʈ���� �̵� ����
	PlayerFire->SetupPlayerInputComponent(PlayerInputComponent);
}	



