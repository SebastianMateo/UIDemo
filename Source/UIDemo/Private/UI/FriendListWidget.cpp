#include "UI/FriendListWidget.h"

#include "CommonListView.h"
#include "UIDemoController.h"

void UFriendListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AUIDemoController* PlayerController = Cast<AUIDemoController>(GetWorld()->GetFirstPlayerController());

	// Load the friend list
	TArray<UUIFriend*> Friends;
	PlayerController->GetFriendList(Friends);
	LoadFriendList(Friends);

	// Register for FriendUpdated
	PlayerController->FriendListUpdated.AddDynamic(this, &UFriendListWidget::OnFriendListUpdated);

	// Register to OnHover events on both the Offline and Online lists
	OnlineListView->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnItemIsHoveredChanged);
	OfflineListView->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnItemIsHoveredChanged);
}

void UFriendListWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (GetWorld() == nullptr || GetWorld()->GetFirstPlayerController() == nullptr) return;
	
	AUIDemoController* PlayerController = Cast<AUIDemoController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController != nullptr)
	{
		PlayerController->FriendListUpdated.RemoveDynamic(this, &UFriendListWidget::OnFriendListUpdated);	
	}
}

void UFriendListWidget::LoadFriendList(TArray<UUIFriend*> Friends)
{
	// Load the Friends in both the Online and Offline Friendlists
	for (UUIFriend* Friend : Friends)
	{
		if (Friend->bIsOnline)
		{
			OnlineListView->AddItem(Friend);		
		}
		else
		{
			OfflineListView->AddItem(Friend);
		}
	}
}

void UFriendListWidget::OnFriendListUpdated(TArray<UUIFriend*> Friends)
{
	// This is not going to be great
	// we could probable cache each player by an id so avoid this search
	// but for now it should work
	for (const UUIFriend* Friend : Friends)
	{
		// Iterate the list into which used to be to find the item
		// add it into the other list
		if (Friend->bIsOnline)
		{
			SwitchLists(Friend, OfflineListView, OnlineListView);
		}
		else
		{
			SwitchLists(Friend, OnlineListView, OfflineListView);
		}
	}
}

void UFriendListWidget::OnShowOnlineClicked() const
{
	SwitchVisibility(OnlineListView);
}

void UFriendListWidget::OnShowOfflineClicked() const
{
	SwitchVisibility(OfflineListView);
}

void UFriendListWidget::OnItemIsHoveredChanged(UObject* Object, bool bHovered)
{
	UUIFriend* Friend = Cast<UUIFriend>(Object);
	if (Friend)
	{
		if (bHovered)
		{
			// We never hovered anything
			// The thing we hovered is different to the one we have
			if ((!LastHoveredFriend) || (!(LastHoveredFriend == Friend)))
			{
				LastHoveredFriend = Friend;
				HoverChangedEvent.Broadcast(Friend, bHovered);
			}
		}
		else
		{
			// Broadcast when hiding
			HoverChangedEvent.Broadcast(Friend, bHovered);	
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UFriendListWidget - Error casting widget"));	
	}
}

void UFriendListWidget::SwitchVisibility(UCommonListView* ListView) const
{
	// Switch between Visible and Collapsed
	if (ListView->GetVisibility() == ESlateVisibility::Visible)
	{
		ListView->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		ListView->SetVisibility(ESlateVisibility::Visible);	
	}
}

void UFriendListWidget::SwitchLists(const UUIFriend* Friend, UCommonListView* FromList, UCommonListView* ToList)
{
	// Search from the friend in the FromList and add it in the ToList
	for (UObject* ListItem : FromList->GetListItems())
	{
		const UUIFriend* ListFriend = Cast<UUIFriend>(ListItem);
		if (ListFriend && ListFriend->Nickname == Friend->Nickname)
		{
			FromList->RemoveItem(ListItem);
			ToList->AddItem(ListItem);
			return;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Friend not found"));
}


