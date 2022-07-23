#include "BigMap.h"
#include "HUDOverlay.h"
#include "MiniMapOverlay.h"
#include "UIMiniMapGameMode.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UBigMap::NativeConstruct()
{
	Super::NativeConstruct();

	//Hide MiniMap.
	AUIMiniMapGameMode* GameMode = Cast<AUIMiniMapGameMode>(GetWorld()->GetAuthGameMode());
	MiniMapOverlay = GameMode->GetHudOverlay()->GetMiniMapOverlay();
	MiniMapOverlay->SetVisibility(ESlateVisibility::Hidden);

	PlayerIcon =  CreateWidget(this, PlayerIconWidgetClass);
	UOverlay* Overlay = Cast<UOverlay>(GetBigMapOverlay());
	UOverlaySlot* OverlaySlot = Overlay->AddChildToOverlay(PlayerIcon);
	//Center player icon on big map.
	OverlaySlot->SetHorizontalAlignment(HAlign_Center);
	OverlaySlot->SetVerticalAlignment(VAlign_Center);
}

void UBigMap::NativeDestruct()
{
	Super::NativeDestruct();

	//Make MiniMap visible again.
	MiniMapOverlay->SetVisibility(ESlateVisibility::Visible);
}

void UBigMap::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdatePlayerIconPosition();
}

void UBigMap::UpdatePlayerIconPosition()
{
	FVector PlayerPosition = UGameplayStatics::GetPlayerController(GetWorld(),0)->GetCharacter()->GetActorLocation();

	//Convert world units to widget units. 5000 is size in world units, 1000 is the size of the big map widget.
	float BigMapX = (PlayerPosition.X / 5000.f) * -1000.f; //Negate bc map orientation
	float BigMapY = (PlayerPosition.Y /5000.f) * 1000.f;
	FVector2D BigMapPosition =  UKismetMathLibrary::MakeVector2D(BigMapY, BigMapX);
	PlayerIcon->SetRenderTranslation(BigMapPosition);
}
