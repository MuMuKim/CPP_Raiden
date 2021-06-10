// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUICPP.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Components/Button.h>

void UGameOverUICPP::NativeConstruct()
{
	//UMG에 등록된 UI Widjet를 찾아서 가져오고 싶다 *TEXT에 들어가는 이름은 버튼의 이름으로 해야함
	//auto reStart = Cast<UButton>(GetWidgetFromName(TEXT("ReStart_Button")));
	
	//만약 잘가져왔다면
	if (ReStart_Button)
	{
		//Clic이벤트를 할당하고 싶다
		ReStart_Button->OnClicked.AddDynamic(this, &UGameOverUICPP::OnRestartClicked);
		//OnClicked는 델리게이트 = 지정한 함수 너로 처리할거야
	}

	//auto quit = Cast<UButton>(GetWidgetFromName(TEXT("Quit_Button")));
	//만약 잘가져왔다면
	if (Quit_Button)
	{
		//Clic이벤트를 할당하고 싶다
		Quit_Button->OnClicked.AddDynamic(this, &UGameOverUICPP::OnQuitClicked);
		//OnClicked는 델리게이트 = 지정한 함수 너로 처리할거야
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
	//Level을 재시작
	UGameplayStatics::OpenLevel(this, TEXT("Raiden_Map"));
}

void UGameOverUICPP::Quit()
{
	//게임을 종료한다
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
