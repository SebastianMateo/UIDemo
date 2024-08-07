#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FriendRowWidget.generated.h"

class UTextBlock;
class UUIFriend;

DECLARE_EVENT_TwoParams(UFriendWidget, FHoverChangedEvent, UUIFriend*, const bool);

UCLASS()
class UFriendRowWidget : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	// Now here we receive the UIFriend Object, and we can set it to our rows
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Txt_Nickname;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Txt_Level;
};
