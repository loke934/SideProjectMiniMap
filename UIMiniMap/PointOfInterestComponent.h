#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PointOfInterestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UIMINIMAP_API UPointOfInterestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPointOfInterestComponent();

	UFUNCTION(BlueprintCallable)
	void AddToMiniMap();

	UFUNCTION()
	bool GetIsStatic() const {return bIsStatic;}

protected:
		virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintImplementableEvent)
	UTexture2D* GetIconImage() const;
	
	UPROPERTY(EditAnywhere)
	bool bIsStatic;

	UPROPERTY(EditAnywhere)
	UTexture2D* IconImage;
	
};
