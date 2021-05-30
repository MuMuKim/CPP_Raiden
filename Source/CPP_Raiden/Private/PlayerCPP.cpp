// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>


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

	//����ڰ� �Է��� �������� �̵��ϰ� �ʹ�.
	FVector dir(0, h, v);
	dir.Normalize();
	SetActorLocation(GetActorLocation() + dir * MoveSpeed * DeltaTime);
}

//������� �Է¸��ΰ� ó���� �Լ��� �����ִ�(bind) ������ �ϴ� �Լ�
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Ű�Է¿� ���� ���ε�
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerCPP::InputHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerCPP::InputVertical);
}
//����ڰ� �¿� Ű�� ������ ����Ǵ� �Լ�
void APlayerCPP::InputHorizontal(float Value)
{
	h = Value;
}

//����ڰ� ���� Ű�� ������ ����Ǵ� �Լ�
void APlayerCPP::InputVertical(float Value)
{
	v = Value;
}

