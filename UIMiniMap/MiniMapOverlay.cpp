#include "MiniMapOverlay.h"
#include "PlayerIcon.h"
#include "PointOfInterest.h"
#include "PointOfInterestComponent.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollectionInstance.h"


void UMiniMapOverlay::SetUpMiniMap()
{
	MPCInstance = GetWorld()->GetParameterCollectionInstance(MiniMapParameters);
	MPCInstance->SetScalarParameterValue("MapDimensions", MapDimensions);
	MPCInstance->SetScalarParameterValue("Zoom", Zoom);
	MapInstance->SetTextureParameterValue("MapTexture", MapTexture);
}

void UMiniMapOverlay::ChangeMapImage()
{
	MapInstance->SetTextureParameterValue("MapTexture", MapTexture);
}

void UMiniMapOverlay::AddPlayerIconWidget()
{
	if (PlayerIconWidgetClass != nullptr)
	{
		UUserWidget* PlayerIcon = CreateWidget(this,PlayerIconWidgetClass);
		UOverlay* Overlay = Cast<UOverlay>(GetRootWidget());
		UOverlaySlot* Placement = Overlay->AddChildToOverlay(PlayerIcon);
		Placement->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		Placement->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				2,
				FColor::Red,
				FString::Printf(TEXT("MiniMapOverlay script: player icon widget class is nullptr")));
		}
	}
}

void UMiniMapOverlay::UpdatePlayerPositionOnMiniMap()
{
	FVector CurrenPositionWorld= UGameplayStatics::GetPlayerController(GetWorld(),0)->GetPawn()->GetActorLocation();
	MPCInstance->SetScalarParameterValue("X", CurrenPositionWorld.X);
	MPCInstance->SetScalarParameterValue("Y", CurrenPositionWorld.Y);
}

void UMiniMapOverlay::UpdateZoom()
{
	MPCInstance->SetScalarParameterValue("Zoom", Zoom);
}

void UMiniMapOverlay::AddPointOfInterestWidget(AActor* Owner)
{
	UPointOfInterest* PointOfInterest = Cast<UPointOfInterest>(CreateWidget(this,PointOfInterestWidgetClass));
	PointOfInterest->SetIsStatic(Owner->FindComponentByClass<UPointOfInterestComponent>()->GetIsStatic());
	PointOfInterest->SetOwner(Owner);
	
	UOverlay* Overlay = Cast<UOverlay>(GetRootWidget());
	UOverlaySlot* Placement = Overlay->AddChildToOverlay(PointOfInterest);
	Placement->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	Placement->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
}


