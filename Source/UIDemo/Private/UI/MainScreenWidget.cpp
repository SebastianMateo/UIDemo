#include "UI/MainScreenWidget.h"

#include "FriendConnectedWidget.h"
#include "FriendListWidget.h"
#include "FriendTooltipWidget.h"
#include "UIDemoController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UMainScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	AUIDemoController* PlayerController = Cast<AUIDemoController>(GetWorld()->GetFirstPlayerController());
	PlayerController->FriendListUpdated.AddDynamic(this, &ThisClass::OnFriendListUpdated);
	ToastWidget->OnShowEndDelegate.BindDynamic(this, &ThisClass::OnFriendConnectedEnd);
	FriendListWidget->HoverChangedEvent.AddUObject(this, &ThisClass::OnFriendHover);
	FriendTooltipWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (GetWorld() == nullptr || GetWorld()->GetFirstPlayerController() == nullptr) return;
	
	AUIDemoController* PlayerController = Cast<AUIDemoController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController != nullptr)
	{
		PlayerController->FriendListUpdated.RemoveDynamic(this, &UMainScreenWidget::OnFriendListUpdated);	
	}
}

void UMainScreenWidget::OnFriendListUpdated(TArray<UUIFriend*> Friends)
{
	for (UUIFriend* Friend : Friends)
	{
		// If it's not online, we don't care
		if (!Friend->bIsOnline) continue;

		if (!ToastWidget->IsVisible())
		{
			ToastWidget->Show(Friend->Nickname);
		}
		else
		{
			// We are showing a notification, so we need to queue this
			FriendQueue.Enqueue(Friend);	
		}
	}
}

void UMainScreenWidget::OnFriendConnectedEnd()
{
	// Try and get the next on the queue
	UUIFriend* Friend;
	if (FriendQueue.Dequeue(Friend))
	{
		ToastWidget->Show(Friend->Nickname);		
	}
}

void UMainScreenWidget::OnFriendHover(UUIFriend* UIFriend, bool bIsHovered)
{
	if (bIsHovered)
	{
		FriendTooltipWidget->Txt_Nickname->SetText(FText::FromString(UIFriend->Nickname));
		// Important to be HitTestInvisible else it will HitTest and change the HoverCondition
		FriendTooltipWidget->SetVisibility(ESlateVisibility::HitTestInvisible); 
	}
	else
	{
		FriendTooltipWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// When the tooltip is visible, set the coordinates of the containing panel's slot to the mouse position.
	Super::NativeTick(MyGeometry, InDeltaTime); 
	
	if(FriendTooltipWidget->IsVisible())
	{
		const FVector2D& MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		if(UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(FriendTooltipWidget->Slot))
		{
			PanelSlot->SetPosition(MousePosition);
		}
	}
}