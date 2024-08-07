#include "UI/FriendRowWidget.h"

#include "UIFriend.h"
#include "Components/TextBlock.h"

void UFriendRowWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UUIFriend* UIFriend = Cast<UUIFriend>(ListItemObject);
	if (UIFriend != nullptr)
	{
		Txt_Nickname->SetText(FText::FromString(UIFriend->Nickname));
		Txt_Level->SetText(FText::FromString(FString::FromInt(UIFriend->Level)));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Casting error on NativeOnListItemObjectSet"));
	}
}