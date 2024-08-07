// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MainScreenWidget.generated.h"

class UFriendTooltipWidget;
class UFriendListWidget;
class UUIFriend;
class UFriendConnectedWidget;

UCLASS()
class UMainScreenWidget : public UCommonUserWidget
{
	GENERATED_BODY()
protected:
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	UFUNCTION()
	void OnFriendListUpdated(TArray<UUIFriend*> Friends);

	UFUNCTION()
	void OnFriendConnectedEnd();

	UFUNCTION()
	void OnFriendHover(UUIFriend* UIFriend, bool bIsHovered);
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess, BindWidget))
	UFriendConnectedWidget* ToastWidget;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess, BindWidget))
	UFriendListWidget* FriendListWidget;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess, BindWidget))
	UFriendTooltipWidget* FriendTooltipWidget;
	
	TQueue<UUIFriend*> FriendQueue;
};
