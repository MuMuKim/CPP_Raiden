// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerFire.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_RAIDEN_API UPlayerFire : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// 사용자의 입력을 처리할 함수(콜백)
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	//총알Sound
	UPROPERTY(EditAnywhere,Category="Audio")
	class USoundBase* BulletSound;

	//사용자가 발사버튼을 누르면 Bullet을 발사하는 기능
	void Fire();

	//이 컴포넌트를 소유하고 있는 액터
	UPROPERTY()
	class APlayerCPP* me;
};
