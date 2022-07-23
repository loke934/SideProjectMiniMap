#include "PlayerIcon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UPlayerIcon::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FRotator PlayerRotation = UGameplayStatics::GetPlayerController(GetWorld(),0)->GetCharacter()->GetMesh()->GetComponentRotation();
	SetRenderTransformAngle(PlayerRotation.Yaw);
}
