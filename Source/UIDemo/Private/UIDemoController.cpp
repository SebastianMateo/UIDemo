#include "UIDemoController.h"

#include "Data/Friend.h"

void AUIDemoController::BeginPlay()
{
	Super::BeginPlay();
	
	// Create a Timer to Update the friends
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AUIDemoController::SimulateUpdateFriends, SimulateUpdateTime, true);
	ensure(FriendListDataTable);
}

void AUIDemoController::GetFriendList(TArray<UUIFriend*>& OutFriendList) const
{
	// Should eventually be Async...
	// but for now this should work
	TArray<FName> RowNames = FriendListDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		const FString ContextString;
		const FFriend* Friend = FriendListDataTable->FindRow<FFriend>(RowName, ContextString);
		UUIFriend* UIFriend = NewObject<UUIFriend>(UUIFriend::StaticClass());
		UIFriend->Nickname = Friend->Nickname;
		UIFriend->Level = Friend->Level;
		UIFriend->bIsOnline = Friend->bIsOnline;
		OutFriendList.Emplace(UIFriend);
	}
}

void AUIDemoController::SimulateUpdateFriends() const
{
	TArray<FName> RowNames = FriendListDataTable->GetRowNames();
	TArray<UUIFriend*> UIFriends;
	for (const FName& RowName : RowNames)
	{
		const FString ContextString;
		FFriend* Friend = FriendListDataTable->FindRow<FFriend>(RowName, ContextString);
		
		if (FMath::RandRange(0, 100) <= UpdateChance)
		{
			// Update our Friend online status
			Friend->bIsOnline = !Friend->bIsOnline;
			
			UUIFriend* UIFriend = NewObject<UUIFriend>(UUIFriend::StaticClass());
			UIFriend->Nickname = Friend->Nickname;
			UIFriend->Level = Friend->Level;
			UIFriend->bIsOnline = Friend->bIsOnline;
			UIFriends.Emplace(UIFriend);	
		}
	}

	FriendListUpdated.Broadcast(UIFriends);
}
