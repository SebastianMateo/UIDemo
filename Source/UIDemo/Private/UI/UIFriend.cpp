#include "UI/UIFriend.h"

bool UUIFriend::operator==(const UUIFriend& Other) const
{
	return Nickname == Other.Nickname;
}

bool UUIFriend::operator!=(const UUIFriend& Other) const
{
	UE_LOG(LogTemp, Log, TEXT("Unequal operator"));
	return Nickname != Other.Nickname;
}