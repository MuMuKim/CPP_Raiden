// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include "DestroyZoneCPP.h"
// Sets default values
AEnemyCPP::AEnemyCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//몸체
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComp;
	//외관
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetupAttachment(BoxComp);
	//Root와 겹치지않게 자식 Collision 없애기
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
}

// Called when the game starts or when spawned
void AEnemyCPP::BeginPlay()
{
	Super::BeginPlay();

	//타겟(Player)을 담을 그릇(배열)
	TArray<AActor*> objs;
	//월드상에 Actor을 찾아넣기 (배열로 담아야함)
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCPP::StaticClass(), objs);
	//actor라는 임시변수에 objs의 담긴 자료만큼 돌아 넣는다
	for (AActor* actor : objs)
	{
		Target = actor;
	}
	
	// 50%확률을 위한 랜덤기능
	int32 Ran = FMath::RandRange(1, 100);

	//애초에 처음방향은 아래방향
	Dir = FVector(0, 0, -1);

	//50%확률로 타겟방향으로 가게하기
	if (Target && IsValid(Target))
	{
		if (Ran <= 50)
		{
			// target - me
			Dir = Target->GetActorLocation() - GetActorLocation();
		}
	}
	Dir.Normalize();
	
	//-----------------------------------------------동영상 방법(빠르고 좋음)
	//if (Ran <= TraceRate)
	//{
	//	//타겟방향구하기
	//	
	//	//월드에서 player찾기
	//	for (TActorIterator<APlayerCPP> it(GetWorld()); it; ++it)
	//	{
	//		Dir = it->GetActorLocation() - GetActorLocation();
	//	}
	//}
	//else
	//{
	//	//아래방향
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

	//살아가면서 계속 그 방향으로 이동하고 싶다
	//P = P0 + vt, Sweep
	SetActorLocation(GetActorLocation() + Dir * DeltaTime * MoveSpeed, true);
}

void AEnemyCPP::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//부딪힌 대상이 Enemy,DestroyZone이면 함수를 실행하지 않는다
	auto Enemy = Cast<AEnemyCPP>(OtherActor);
	auto DZ = Cast<ADestroyZoneCPP>(OtherActor);
	if (Enemy != nullptr || DZ != nullptr)
	{
		return;
	}
	/*if (OtherActor->GetWorld()->GetName().Contains(TEXT("DestroyZone")))
	{
		return;
	}*/
	//폭발효과 생성
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFactory, GetActorTransform());

	//폭발사운드
	UGameplayStatics::PlaySound2D(GetWorld(), ExSound);

	OtherActor->Destroy();
	Destroy();
}


