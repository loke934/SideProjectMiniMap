#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BigMap.generated.h"

class UOverlay;
class UImage;
class UMiniMapOverlay;

UCLASS()
class UIMINIMAP_API UBigMap : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	UOverlay* GetBigMapOverlay() const;
	
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerIconPosition();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerIconWidgetClass;

private:
	UPROPERTY()
	UMiniMapOverlay* MiniMapOverlay;

	UPROPERTY()
	UUserWidget* PlayerIcon;
	
};
