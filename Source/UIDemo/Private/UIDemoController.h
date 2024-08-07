#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/UIFriend.h"

#include "UIDemoController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendListUpdatedDelegate, TArray<UUIFriend*>, Friends);

UCLASS()
class AUIDemoController : public APlayerController
{
	GENERATED_BODY()
public:
	FOnFriendListUpdatedDelegate FriendListUpdated;

	void GetFriendList(TArray<UUIFriend*> &OutFriendList) const;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* FriendListDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float SimulateUpdateTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int UpdateChance = 10;
	
	void SimulateUpdateFriends() const;
	
	FTimerHandle TimerHandle;
};
