// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUICPP.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

void UGameOverUICPP::ReStart()
{
	//Level을 재시작
	UGameplayStatics::OpenLevel(this, TEXT("Riden"));
}

void UGameOverUICPP::Quit()
{
	//게임을 종료한다
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
