#pragma once

#include "CoreMinimal.h"
#include "UIFriend.generated.h"

UCLASS()
class UUIFriend : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE bool operator==(const UUIFriend& Other) const;
	FORCEINLINE bool operator!=(const UUIFriend& Other) const;
	
	FString Nickname;
	int32 Level;
	bool bIsOnline;
};
