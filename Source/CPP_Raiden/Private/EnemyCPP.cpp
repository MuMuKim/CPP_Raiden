// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include "DestroyZoneCPP.h"
#include <Components/PrimitiveComponent.h>
#include "CRaidenGameMode.h"
// Sets default values
AEnemyCPP::AEnemyCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��ü
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComp;
	//������Ʈ �浹�� ���� ���
	//BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCPP::OnTrigerEnter);
	
	//�ܰ�
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(BoxComp);
	//Root�� ��ġ���ʰ� �ڽ� Collision ���ֱ�
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
}

// Called when the game starts or when spawned
void AEnemyCPP::BeginPlay()
{
	Super::BeginPlay();

	//Ÿ��(Player)�� ���� �׸�(�迭)
	TArray<AActor*> objs;
	//����� Actor�� ã�Ƴֱ� (�迭�� ��ƾ���)
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCPP::StaticClass(), objs);
	//actor��� �ӽú����� objs�� ��� �ڷḸŭ ���� �ִ´�
	for (AActor* actor : objs)
	{
		Target = actor;
	}
	
	// 50%Ȯ���� ���� �������
	int32 Ran = FMath::RandRange(1, 100);

	//���ʿ� ó�������� �Ʒ�����
	Dir = FVector(0, 0, -1);

	// Ÿ���� �ְ�, Ÿ���� ��ȿ�ϴٸ�(��ȿ�� �˻�: nullptr, IsValid)
	if (Target && IsValid(Target))
	{
		//50%Ȯ���� Ÿ�ٹ������� �����ϱ�
		if (Ran <= 50)
		{
			// target - me
			Dir = Target->GetActorLocation() - GetActorLocation();
		}
	}
	Dir.Normalize();
	
	//-----------------------------------------------������ ���(������ ����)
	//if (Ran <= TraceRate)
	//{
	//	//Ÿ�ٹ��ⱸ�ϱ�
	//	
	//	//���忡�� playerã��
	//	for (TActorIterator<APlayerCPP> it(GetWorld()); it; ++it)
	//	{
	//		Dir = it->GetActorLocation() - GetActorLocation();
	//	}
	//}
	//else
	//{
	//	//�Ʒ�����
	//	Dir = FVector(0, 0, -1);
	//}
	//Dir.Normalize();
}

// Called every frame
void AEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (Target && IsValid(Target))
	{
		Dir = Target->GetActorLocation() - GetActorLocation();
	}
	else
	{
		Dir = FVector(0, 0, -1);
	}
	Dir.Normalize();*/

	//��ư��鼭 ��� �� �������� �̵��ϰ� �ʹ�
	//P = P0 + vt, Sweep
	SetActorLocation(GetActorLocation() + Dir * DeltaTime * MoveSpeed, true);
}
void AEnemyCPP::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//�ε��� ����� Enemy,DestroyZone�̸� �Լ��� �������� �ʴ´�
	auto Enemy = Cast<AEnemyCPP>(OtherActor);
	auto DZ = Cast<ADestroyZoneCPP>(OtherActor);
	if (Enemy != nullptr || DZ != nullptr)
	{
		return;
	}

	//����ȿ��
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFactory, GetActorTransform());

	//���߻���
	UGameplayStatics::PlaySound2D(GetWorld(), ExSound);

	// �ε��� ���Ͱ� �Ѿ��̶�� �ٽ� źâ(Pool)�� �־��ش�
	auto Bullet = Cast<ABulletCPP>(OtherActor);

	auto GameMode = Cast<ACRaidenGameMode>(GetWorld()->GetAuthGameMode());
	if (Bullet && GameMode)
	{
		//������
		GameMode->ADDBullet(Bullet);
	}
	else
	{
		// Player��
		// ����Ȯ��
		auto Player = Cast<APlayerCPP>(OtherActor);
		if (Player)
		{
			//���¸� GameOver�� �����
			GameMode->SetState(EGameState::GameOver);
		}
		OtherActor->Destroy();
	}
	GameMode->SetCurrentScore(GameMode->GetCurrentScore() + 1);
	Destroy();
}
//Componunt �浹 �Լ�
//void AEnemyCPP::OnTrigerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)

