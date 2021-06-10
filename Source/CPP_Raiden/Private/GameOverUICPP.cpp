// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUICPP.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

void UGameOverUICPP::ReStart()
{
	//Level�� �����
	UGameplayStatics::OpenLevel(this, TEXT("Riden"));
}

void UGameOverUICPP::Quit()
{
	//������ �����Ѵ�
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
