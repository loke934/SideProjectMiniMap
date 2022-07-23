#include "PointOfInterestComponent.h"

#include "HUDOverlay.h"
#include "MiniMapOverlay.h"
#include "UIMiniMapGameMode.h"

UPointOfInterestComponent::UPointOfInterestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPointOfInterestComponent::AddToMiniMap()
{
	AUIMiniMapGameMode* GameMode = Cast<AUIMiniMapGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->GetHudOverlay()->GetMiniMapOverlay()->AddPointOfInterestWidget(GetOwner());
}

void UPointOfInterestComponent::BeginPlay()
{
	Super::BeginPlay();

}


