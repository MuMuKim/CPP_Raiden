// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCPP.h"
#include <Components/TextBlock.h>

void UScoreCPP::PrintCurrentScore(int32 point)
{
	//만약 Text_CurrentScore가 있다면
	if (Text_CurrentScore)
	{
		// point를 할당시켜준다
		FString ScoreStr = FString::Printf(TEXT("Current Score: %d"), point);

		//UI에 값을 할당한다
		Text_CurrentScore->SetText(FText::FromString(ScoreStr));
	}
}

void UScoreCPP::PrintTopScore(int32 point)
{
	//만약 Text_TopScore가 있다면
	if (Text_TopScore)
	{
		// point를 할당시켜준다
		FString ScoreStr = FString::Printf(TEXT("Top Score: %d"), point);

		//UI에 값을 할당한다
		Text_TopScore->SetText(FText::FromString(ScoreStr));
	}
}
