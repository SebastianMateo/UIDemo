#include "FriendConnectedWidget.h"

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"

void UFriendConnectedWidget::Show(const FString& Nickname)
{
	Txt_Nickname->SetText(FText::FromString(Nickname));
	OnToastWidgetShowed();
}

void UFriendConnectedWidget::OnShowEnded()
{
	OnShowEndDelegate.Execute();
}

void UFriendConnectedWidget::OnToastWidgetShowed_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("UFriendConnectedWidget::OnShow_Implementation"));
}
