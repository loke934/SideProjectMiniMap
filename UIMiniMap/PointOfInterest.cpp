#include "PointOfInterest.h"
#include "HUDOverlay.h"
#include "MiniMapOverlay.h"
#include "PointOfInterestComponent.h"
#include "UIMiniMapGameMode.h"
#include "Components/Image.h"
#include "Components/Throbber.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UPointOfInterest::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<AUIMiniMapGameMode>(GetWorld()->GetAuthGameMode());
}

void UPointOfInterest::UpdatePointOfInterestPosition()
{
	//Make widget move and offset it based on the distance between the player and owning actor.
	//Update the location of this widget in relation to the mini-map.
	if (IsValid(Owner))
	{
		FVector PlayerPosition = UGameplayStatics::GetPlayerController(GetWorld(),0)->GetCharacter()->GetActorLocation();
		FVector PointOfInterestPosition = Owner->GetActorLocation();
		//Distance between the poi and player and translate that value into a ratio relative to the size of the level compared to the mini map.
		//Difference in size between level map dimensions and minimap dimensions. To get the difference divide map dimensions with mini map widget size.
		float MiniMapDimensions = GameMode->GetHudOverlay()->GetMiniMapOverlay()->MapDimensions / 300.f;
		//Multiply by zoom since the whole map is not shown.
		float Zoom = GameMode->GetHudOverlay()->GetMiniMapOverlay()->Zoom;
		float Dimensions = MiniMapDimensions * Zoom;
		
		//Dist between player and poi actor, going to be in 2D.
		float MiniMapX = PlayerPosition.X - PointOfInterestPosition.X;
		float MiniMapY = (PlayerPosition.Y - PointOfInterestPosition.Y) * -1.f; //inverse movement

		//Remap to minimap coords.
		MiniMapX /= Dimensions;
		MiniMapY /= Dimensions;

		//Distance between poi and player made into coords on mini map.
		FVector2D MiniMapCoords = UKismetMathLibrary::MakeVector2D(MiniMapX,MiniMapY);
		FVector2D MiniMapPosition = GetMiniMapPosition(MiniMapCoords);
		
		SetRenderTranslation(MiniMapPosition);
		EvaluateStaticIcon(MiniMapPosition);
	}
	
	else
	{
		RemoveFromParent();
	}
}

FVector2D UPointOfInterest::GetMiniMapPosition(FVector2D MiniMapCoords)
{
	//Find Angle between player and poi. SohCahToa- opp is the diff in y and adj is the diff in x. Player is always center so 0,0.
	//inverse of tan
	float Radians = UKismetMathLibrary::Atan2(0-MiniMapCoords.Y, 0-MiniMapCoords.X);
	float Radius = MiniMapCoords.Size();

	//Have the dist and clamp it and keep icon on edge of mini map. Diameter is 300 of mini map, radius 150 (take 130 bc offset a lil).
	//We have angle and hypotenuse which can give us opp(sin) and adj(cos) which will give the coords to clamp it to. Keep icon in range of minimap circle.
	float ClampedRadius = UKismetMathLibrary::Clamp(Radius,0,130);

	//Y
	float SinDeg = UKismetMathLibrary::Sin(Radians);
	float MiniMapPosY = (ClampedRadius * SinDeg) * -1.f; //negate bc map is not faced north
	//X
	float CosDeg = UKismetMathLibrary::Cos(Radians);
	float MiniMapPosX = (ClampedRadius * CosDeg) * -1.f;
	
	FVector2D MiniMapPosition = UKismetMathLibrary::MakeVector2D(MiniMapPosY,MiniMapPosX);
	return MiniMapPosition;
}

void UPointOfInterest::EvaluateStaticIcon(FVector2D MiniMapPosition)
{
	if (!bIsStatic)
	{
		if (MiniMapPosition.Size() == 130.f)
		{
			switch (ImageType)
			{
			case EImageType::EIT_Custom:
				GetCustomImage()->SetVisibility(ESlateVisibility::Hidden);
				break;
			case EImageType::EIT_Default:
				GetDefaultImage()->SetVisibility(ESlateVisibility::Hidden);
				break;
			default:
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1,10,FColor::Red,FString::Printf(TEXT("No image enum type set!")));
				}
			}
		}
		else
		{
			switch (ImageType)
			{
			case EImageType::EIT_Custom:
				GetCustomImage()->SetVisibility(ESlateVisibility::Visible);
				break;
			case EImageType::EIT_Default:
				GetDefaultImage()->SetVisibility(ESlateVisibility::Visible);
				break;
			default:
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1,10,FColor::Red,FString::Printf(TEXT("No image enum type set!")));
				}
			}
		}
	}
}

void UPointOfInterest::SetIconImage()
{
	if (IsValid(Owner->FindComponentByClass<UPointOfInterestComponent>()->IconImage))
	{
		GetCustomImage()->SetBrushFromTexture(Owner->FindComponentByClass<UPointOfInterestComponent>()->IconImage);
		GetDefaultImage()->SetVisibility(ESlateVisibility::Hidden);
		ImageType = EImageType::EIT_Custom;
	}
	else
	{
		GetCustomImage()->SetVisibility(ESlateVisibility::Hidden);
		ImageType = EImageType::EIT_Default;
	}
}
