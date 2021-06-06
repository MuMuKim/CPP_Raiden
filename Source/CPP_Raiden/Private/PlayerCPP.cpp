// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include "BulletCPP.h"
#include <Kismet/GameplayStatics.h>
#include "CPP_RaidenGameModeBase.h"
#include "CRaidenGameMode.h"


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

	//�Ѿ˰���

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

	//ȸ��
	FRotator Rdir(0, 1, 0);
	SetActorRotation(GetActorRotation() + Rdir * 300 * DeltaTime);
}

//������� �Է¸��ΰ� ó���� �Լ��� �����ִ�(bind) ������ �ϴ� �Լ�
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Ű�Է¿� ���� ���ε�
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerCPP::InputHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerCPP::InputVertical);

	//�Ѿ˹߻� Ű�Է� (IE_Pressed ������ ������)
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &APlayerCPP::Fire);
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

void APlayerCPP::Fire()
{
	//�Ѿ˰��忡�� �Ѿ��� �ϳ� �����, �Ѿ��� �ѱ��� ��ġ�ϰ� �ʹ�
	//if (BulletFactory)
	//{
	//	//spwan
	//	FActorSpawnParameters Prams;
	//	//�׻� ���ڸ��� �ٸ� ��ü�� �ִ��� ������ ���͸� �����ض�
	//	Prams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//	//�ѱ���ġ�� �Ѿ˰��忡�� ���� �Ѿ��� ��ġ
	//	//GetWorld�ȿ� �ִ� �������Ͷ�� �Լ��ȿ� ������ ������(Bullet),�Ķ���ͷ� �Ѿ˰���,��� ��ġ����,
	//	GetWorld()->SpawnActor<ABulletCPP>(BulletFactory, FirePosition->GetComponentTransform(), Prams);

	//	//�Ѿ˹߻� ����
	//	UGameplayStatics::PlaySound2D(GetWorld(), BulletSound);
	//}

	auto GameMode = Cast<ACRaidenGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		//GameMode�� GetBullet�Լ��� ����� �Ѿ��� �����´�
		auto Bullet = GameMode->GetBullet();
		auto Bullet2 = GameMode->GetBullet();
		//����ڵ�
		if (Bullet == nullptr && Bullet2 == nullptr)
		{
			return;
		}

		//������ �Ѿ��� Ȱ��ȭ �����ش�
		GameMode->SetBulletActive(Bullet, true);
		GameMode->SetBulletActive(Bullet2, true);

		//��ġ��Ų��
		Bullet->SetActorLocation(FirePosition->GetComponentLocation()+FVector(0,-40,0));
		Bullet2->SetActorLocation(FirePosition->GetComponentLocation()+FVector(0,40,0));
		//�Ѿ˹߻� ����
		UGameplayStatics::PlaySound2D(GetWorld(), BulletSound);
	}
}

