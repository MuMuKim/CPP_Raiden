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

	//총알공장

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

	//상태가 Playing이 아니라면 실행하지 않게한다.
	auto GameMode = Cast<ACRaidenGameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	//사용자가 입력한 방향으로 이동하고 싶다.
	FVector dir(0, h, v);
	dir.Normalize();
	SetActorLocation(GetActorLocation() + dir * MoveSpeed * DeltaTime);

	//회전
	FRotator Rdir(0, 1, 0);
	SetActorRotation(GetActorRotation() + Rdir * 300 * DeltaTime);
}

//사용자의 입력매핑과 처리할 함수를 묶어주는(bind) 역할을 하는 함수
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//키입력에 따른 바인딩
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerCPP::InputHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerCPP::InputVertical);

	//총알발사 키입력 (IE_Pressed 누르는 순간에)
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &APlayerCPP::Fire);
}	
//사용자가 좌우 키를 누르면 실행되는 함수
void APlayerCPP::InputHorizontal(float Value)
{
	h = Value;
}

//사용자가 상하 키를 누르면 실행되는 함수
void APlayerCPP::InputVertical(float Value)
{
	v = Value;
}

void APlayerCPP::Fire()
{
	//총알공장에서 총알을 하나 만들고, 총알을 총구에 배치하고 싶다
	//if (BulletFactory)
	//{
	//	//spwan
	//	FActorSpawnParameters Prams;
	//	//항상 이자리에 다른 물체가 있더라도 무조건 액터를 생성해라
	//	Prams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//	//총구위치에 총알공장에서 만든 총알을 배치
	//	//GetWorld안에 있는 스폰액터라는 함수안에 무엇을 만들지(Bullet),파라미터로 총알공장,어디에 배치될지,
	//	GetWorld()->SpawnActor<ABulletCPP>(BulletFactory, FirePosition->GetComponentTransform(), Prams);

	//	//총알발사 사운드
	//	UGameplayStatics::PlaySound2D(GetWorld(), BulletSound);
	//}

	auto GameMode = Cast<ACRaidenGameMode>(GetWorld()->GetAuthGameMode());

	//Playing 상태가 아니라면 함수를 끝낸다(실행시키지 않는다)
	if (GameMode->GetState() != EGameState::Playing)
	{
		return;
	}
	if (GameMode)
	{
		//gameMode의 GetBullet함수에 리턴값인 bullet을 받아와 bullet변수로 받아준다.
		auto bullet = GameMode->GetBullet(); // 1발
		//방어코드
		if (bullet == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet 1 NULL!!!!!!!!!!!!!"));
			return;
		}
		//두번째 총알을 가져올때 탄창에 더이상 총알이 없다면
		//발사할 수 없기 때문에 첫번째 가져온 총알은 다시 탄창에 반납한다
		auto bullet2 = GameMode->GetBullet(); // 2발
		if (bullet2 == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet 2 NULL!!!!!!!!!!!!!"));
			GameMode->ADDBullet(bullet);
			return;
		}
		
		//첫번째 총알을 활성화 시켜준다
		GameMode->SetBulletActive(bullet, true);
		//첫번째 총알을 FirePosition의 Location값에서 +60해 배치시킨다
		bullet->SetActorLocation(FirePosition->GetComponentLocation() + FVector(0, 60, 0));
		bullet->SetActorRelativeRotation(FirePosition->GetComponentRotation());
		UE_LOG(LogTemp, Warning, TEXT("Bullet 1 Setting Clear!!!!!!!!!!!!!"));
		//두번째 총알을 활성화 시켜준다
		GameMode->SetBulletActive(bullet2, true);
		//두번째 총알을 FirePosition의 Location값에서 -60해 배치시킨다
		bullet2->SetActorLocation(FirePosition->GetComponentLocation() + FVector(0, -60, 0));
		bullet2->SetActorRelativeRotation(FirePosition->GetComponentRotation());
		UE_LOG(LogTemp, Warning, TEXT("Bullet 2 Setting Clear!!!!!!!!!!!!!"));
	}
	//총알발사 사운드
	UGameplayStatics::PlaySound2D(GetWorld(), BulletSound);
}

