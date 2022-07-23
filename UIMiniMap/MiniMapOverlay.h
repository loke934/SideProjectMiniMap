#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniMapOverlay.generated.h"

class UOverlay;

UCLASS()
class UIMINIMAP_API UMiniMapOverlay : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	UOverlay* GetOverlay() const;
	
	UFUNCTION(BlueprintCallable)
	void SetUpMiniMap();

	UFUNCTION(BlueprintCallable)
	void ChangeMapImage();

	UFUNCTION(BlueprintCallable)
	void AddPlayerIconWidget();

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerPositionOnMiniMap();

	UFUNCTION(BlueprintCallable)
	void UpdateZoom();

	UFUNCTION(BlueprintCallable)
	void AddPointOfInterestWidget(AActor* Owner);
	
	UPROPERTY(EditAnywhere)
	UMaterialParameterCollection* MiniMapParameters;

	UPROPERTY()
	UMaterialParameterCollectionInstance* MPCInstance;

	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* MapInstance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerIconWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PointOfInterestWidgetClass;
	
	//Variables set from the HUD.
	UPROPERTY(EditAnywhere)
	float MapDimensions = 5000.f;

	UPROPERTY(EditAnywhere)
	float Zoom = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MapTexture;

	
	
};
