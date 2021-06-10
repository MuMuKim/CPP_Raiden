// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUICPP.generated.h"

/**
 * 
 */
UCLASS()
class CPP_RAIDEN_API UGameOverUICPP : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//BP에서 함수를 호출할수있도록
	UFUNCTION(BlueprintCallable)
	void ReStart();
	UFUNCTION(BlueprintCallable)
	void Quit();
};
