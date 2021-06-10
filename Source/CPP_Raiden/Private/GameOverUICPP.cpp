// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUICPP.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Components/Button.h>

void UGameOverUICPP::NativeConstruct()
{
	//UMG�� ��ϵ� UI Widjet�� ã�Ƽ� �������� �ʹ� *TEXT�� ���� �̸��� ��ư�� �̸����� �ؾ���
	//auto reStart = Cast<UButton>(GetWidgetFromName(TEXT("ReStart_Button")));
	
	//���� �߰����Դٸ�
	if (ReStart_Button)
	{
		//Clic�̺�Ʈ�� �Ҵ��ϰ� �ʹ�
		ReStart_Button->OnClicked.AddDynamic(this, &UGameOverUICPP::OnRestartClicked);
		//OnClicked�� ��������Ʈ = ������ �Լ� �ʷ� ó���Ұž�
	}

	//auto quit = Cast<UButton>(GetWidgetFromName(TEXT("Quit_Button")));
	//���� �߰����Դٸ�
	if (Quit_Button)
	{
		//Clic�̺�Ʈ�� �Ҵ��ϰ� �ʹ�
		Quit_Button->OnClicked.AddDynamic(this, &UGameOverUICPP::OnQuitClicked);
		//OnClicked�� ��������Ʈ = ������ �Լ� �ʷ� ó���Ұž�
	}
}

void UGameOverUICPP::OnRestartClicked()
{
	ReStart();
}

void UGameOverUICPP::OnQuitClicked()
{
	Quit();
}

void UGameOverUICPP::ReStart()
{
	//Level�� �����
	UGameplayStatics::OpenLevel(this, TEXT("Raiden_Map"));
}

void UGameOverUICPP::Quit()
{
	//������ �����Ѵ�
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}