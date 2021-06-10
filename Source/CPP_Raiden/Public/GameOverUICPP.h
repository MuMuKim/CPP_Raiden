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

	virtual void NativeConstruct() override;

	
public:
	//버튼을 실행시킬 함수
	UFUNCTION()
	void OnRestartClicked();
	UFUNCTION()
	void OnQuitClicked();
	
	//BP에서 함수를 호출할수있도록
	UFUNCTION(BlueprintCallable)
	void ReStart();
	UFUNCTION(BlueprintCallable)
	void Quit();

	//UI Widjet 가져오기
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReStart_Button;
	UPROPERTY(BluePrintReadWrite, meta = (BindWiget))
	class UButton* Quit_Button;

};
