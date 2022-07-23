#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointOfInterest.generated.h"

class UImage;
class UThrobber;
class AUIMiniMapGameMode;

UENUM()
enum class EImageType : uint8
{
	EIT_Custom UMETA(DisplayName = "Custom"),
	EIT_Default UMETA(DisplayName = "Default"),
	EIT_MAX UMETA(DisplayName = "MAX")
	
};

UCLASS()
class UIMINIMAP_API UPointOfInterest : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdatePointOfInterestPosition();

	UFUNCTION()
	FVector2D GetMiniMapPosition(FVector2D MiniMapCoords);

	UFUNCTION()
	void EvaluateStaticIcon(FVector2D MiniMapPosition);
	
	UFUNCTION(BlueprintCallable)
	void SetIconImage();

	UFUNCTION()
	void SetIsStatic (bool Value) {bIsStatic = Value;}

	UFUNCTION()
	void SetOwner (AActor* Value) {Owner= Value;}

	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetCustomImage() const;

	UFUNCTION(BlueprintImplementableEvent)
	UThrobber* GetDefaultImage() const;

private:
	UPROPERTY()
	EImageType ImageType;
	
	UPROPERTY()
	bool bIsStatic;

	UPROPERTY()
	AActor* Owner;

	UPROPERTY()
	AUIMiniMapGameMode* GameMode;

};

