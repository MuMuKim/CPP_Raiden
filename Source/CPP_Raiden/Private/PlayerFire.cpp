// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFire.h"
#include "PlayerCPP.h"
#include "CRaidenGameMode.h"
#include <Components/ArrowComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UPlayerFire::UPlayerFire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerFire::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<APlayerCPP>(GetOwner());
	
}


// Called every frame
void UPlayerFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerFire::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//�Ѿ˹߻� Ű�Է� (IE_Pressed ������ ������)
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &UPlayerFire::Fire);
}

void UPlayerFire::Fire()
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

	//Playing ���°� �ƴ϶�� �Լ��� ������(�����Ű�� �ʴ´�)
	if (GameMode->GetState() != EGameState::Playing)
	{
		return;
	}
	if (GameMode)
	{
		//gameMode�� GetBullet�Լ��� ���ϰ��� bullet�� �޾ƿ� bullet������ �޾��ش�.
		auto bullet = GameMode->GetBullet(); // 1��
		//����ڵ�
		if (bullet == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet 1 NULL!!!!!!!!!!!!!"));
			return;
		}
		//�ι�° �Ѿ��� �����ö� źâ�� ���̻� �Ѿ��� ���ٸ�
		//�߻��� �� ���� ������ ù��° ������ �Ѿ��� �ٽ� źâ�� �ݳ��Ѵ�
		auto bullet2 = GameMode->GetBullet(); // 2��
		if (bullet2 == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet 2 NULL!!!!!!!!!!!!!"));
			GameMode->ADDBullet(bullet);
			return;
		}

		//ù��° �Ѿ��� Ȱ��ȭ �����ش�
		GameMode->SetBulletActive(bullet, true);
		//ù��° �Ѿ��� FirePosition�� Location������ +60�� ��ġ��Ų��
		bullet->SetActorLocation(me->FirePosition->GetComponentLocation() + FVector(0, 60, 0));
		bullet->SetActorRelativeRotation(me->FirePosition->GetComponentRotation());
		UE_LOG(LogTemp, Warning, TEXT("Bullet 1 Setting Clear!!!!!!!!!!!!!"));
		//�ι�° �Ѿ��� Ȱ��ȭ �����ش�
		GameMode->SetBulletActive(bullet2, true);
		//�ι�° �Ѿ��� FirePosition�� Location������ -60�� ��ġ��Ų��
		bullet2->SetActorLocation(me->FirePosition->GetComponentLocation() + FVector(0, -60, 0));
		bullet2->SetActorRelativeRotation(me->FirePosition->GetComponentRotation());
		UE_LOG(LogTemp, Warning, TEXT("Bullet 2 Setting Clear!!!!!!!!!!!!!"));
	}
	//�Ѿ˹߻� ����
	UGameplayStatics::PlaySound2D(GetWorld(), BulletSound);
}

