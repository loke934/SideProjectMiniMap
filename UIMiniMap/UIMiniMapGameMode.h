// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UIMiniMapGameMode.generated.h"

class UHUDOverlay;

UCLASS(minimalapi)
class AUIMiniMapGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUIMiniMapGameMode();

	UFUNCTION(BlueprintImplementableEvent)
	UHUDOverlay* GetHudOverlay() const;
};



