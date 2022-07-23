#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerIcon.generated.h"


UCLASS()
class UIMINIMAP_API UPlayerIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
