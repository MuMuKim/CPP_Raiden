// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletCPP.generated.h"

UCLASS()
class CPP_RAIDEN_API ABulletCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//个眉(面倒 格利)
	UPROPERTY(VisibleAnywhere, Category = "Body")
	class UBoxComponent* BoxComp;

	//寇包
	UPROPERTY(VisibleAnywhere, Category = "Body")
	class UStaticMeshComponent* MeshComp;

	//捞悼加档
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed = 1000;

};
