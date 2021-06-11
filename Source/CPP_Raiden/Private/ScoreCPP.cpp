// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCPP.h"
#include <Components/TextBlock.h>

void UScoreCPP::PrintCurrentScore(int32 point)
{
	//���� Text_CurrentScore�� �ִٸ�
	if (Text_CurrentScore)
	{
		// point�� �Ҵ�����ش�
		FString ScoreStr = FString::Printf(TEXT("Current Score: %d"), point);

		//UI�� ���� �Ҵ��Ѵ�
		Text_CurrentScore->SetText(FText::FromString(ScoreStr));
	}
}

void UScoreCPP::PrintTopScore(int32 point)
{
	//���� Text_TopScore�� �ִٸ�
	if (Text_TopScore)
	{
		// point�� �Ҵ�����ش�
		FString ScoreStr = FString::Printf(TEXT("Top Score: %d"), point);

		//UI�� ���� �Ҵ��Ѵ�
		Text_TopScore->SetText(FText::FromString(ScoreStr));
	}
}
