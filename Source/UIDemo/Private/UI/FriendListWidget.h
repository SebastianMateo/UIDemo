#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "FriendListWidget.generated.h"

class UFriendTooltipWidget;
class UUIFriend;
class UCommonButtonBase;
class UCommonListView;

DECLARE_EVENT_TwoParams(UFriendListWidget, FHoverChangedEvent, UUIFriend* /*UIFriend*/, const bool /*bIsHovered*/);

UCLASS()
class UFriendListWidget : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	void LoadFriendList(TArray<UUIFriend*> Friends);

	FHoverChangedEvent HoverChangedEvent;
protected:
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(Transient)
	UUIFriend* LastHoveredFriend = nullptr;
	
	UFUNCTION()
	void OnFriendListUpdated(TArray<UUIFriend*> Friends);
	
	UFUNCTION(BlueprintCallable)
	void OnShowOnlineClicked() const;
	
	UFUNCTION(BlueprintCallable)
	void OnShowOfflineClicked() const;

	UFUNCTION()
	void OnItemIsHoveredChanged(UObject* Object, bool bHovered);
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UCommonListView* OnlineListView;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UCommonListView* OfflineListView;
	
	void SwitchVisibility(UCommonListView* ListView) const;
	void SwitchLists(const UUIFriend* Friend, UCommonListView* FromList, UCommonListView* ToList);
};
