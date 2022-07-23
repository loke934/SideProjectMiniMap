#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDOverlay.generated.h"

class UMiniMapOverlay;

UCLASS()
class UIMINIMAP_API UHUDOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	UMiniMapOverlay* GetMiniMapOverlay() const;
	
};
