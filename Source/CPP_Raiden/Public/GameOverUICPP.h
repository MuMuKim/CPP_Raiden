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
	//��ư�� �����ų �Լ�
	UFUNCTION()
	void OnRestartClicked();
	UFUNCTION()
	void OnQuitClicked();
	
	//BP���� �Լ��� ȣ���Ҽ��ֵ���
	UFUNCTION(BlueprintCallable)
	void ReStart();
	UFUNCTION(BlueprintCallable)
	void Quit();

	//UI Widjet ��������
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReStart_Button;
	UPROPERTY(BluePrintReadWrite, meta = (BindWiget))
	class UButton* Quit_Button;

};
