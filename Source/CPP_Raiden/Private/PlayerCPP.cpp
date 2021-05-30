// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>


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

	//사용자가 입력한 방향으로 이동하고 싶다.
	FVector dir(0, h, v);
	dir.Normalize();
	SetActorLocation(GetActorLocation() + dir * MoveSpeed * DeltaTime);
}

//사용자의 입력매핑과 처리할 함수를 묶어주는(bind) 역할을 하는 함수
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//키입력에 따른 바인딩
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerCPP::InputHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerCPP::InputVertical);
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

