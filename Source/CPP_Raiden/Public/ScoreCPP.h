// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreCPP.generated.h"

/**
 * 
 */
UCLASS()
class CPP_RAIDEN_API UScoreCPP : public UUserWidget
{
	GENERATED_BODY()

public:
	// 점수를 담는 변수
	UPROPERTY(BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* Text_CurrentScore;
	UPROPERTY(BlueprintReadWrite, meta =(BindWidget))
	class UTextBlock* Text_TopScore;
	
	//화면에 출력해줄 함수
	void PrintCurrentScore(int32 point);
	void PrintTopScore(int32 point);

};
