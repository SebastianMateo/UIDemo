#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FriendConnectedWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnShowEndDelegate);

class UTextBlock;

UCLASS()
class UFriendConnectedWidget : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	void Show(const FString& Nickname);
	
	FOnShowEndDelegate OnShowEndDelegate;
	
protected:
	UFUNCTION(BlueprintCallable)
	void OnShowEnded();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnToastWidgetShowed();

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UTextBlock* Txt_Nickname;
};
