// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Friend.generated.h"

USTRUCT(BlueprintType)
struct FFriend : public FTableRowBase
{
	GENERATED_BODY()
	FFriend():
		Level(0),
		bIsOnline(false)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Nickname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOnline;
};


