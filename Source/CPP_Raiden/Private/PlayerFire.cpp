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
	//총알발사 키입력 (IE_Pressed 누르는 순간에)
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &UPlayerFire::Fire);
}

void UPlayerFire::Fire()
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
		bullet->SetActorLocation(me->FirePosition->GetComponentLocation() + FVector(0, 60, 0));
		bullet->SetActorRelativeRotation(me->FirePosition->GetComponentRotation());
		UE_LOG(LogTemp, Warning, TEXT("Bullet 1 Setting Clear!!!!!!!!!!!!!"));
		//두번째 총알을 활성화 시켜준다
		GameMode->SetBulletActive(bullet2, true);
		//두번째 총알을 FirePosition의 Location값에서 -60해 배치시킨다
		bullet2->SetActorLocation(me->FirePosition->GetComponentLocation() + FVector(0, -60, 0));
		bullet2->SetActorRelativeRotation(me->FirePosition->GetComponentRotation());
		UE_LOG(LogTemp, Warning, TEXT("Bullet 2 Setting Clear!!!!!!!!!!!!!"));
	}
	//총알발사 사운드
	UGameplayStatics::PlaySound2D(GetWorld(), BulletSound);
}

