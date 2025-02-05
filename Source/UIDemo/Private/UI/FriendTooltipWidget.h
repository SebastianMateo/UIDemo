// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FriendTooltipWidget.generated.h"

class UTextBlock;

UCLASS()
class UFriendTooltipWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	UTextBlock* Txt_Nickname;	
};
