// 版权没有，拷贝自由。


#include "AbilitySystem/Ability/Player/CC_Primary.h"

#include "Engine/OverlapResult.h"

void UCC_Primary::HitBoxOverlapTest()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
		return;

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetAvatarActorFromActorInfo());

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(IgnoredActors);

	// 设置ResponseParams，可以忽略某些碰撞通道
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	TArray<FOverlapResult> OverlapResults;

	FCollisionShape SphereShape = FCollisionShape::MakeSphere(HitBoxRadius);

	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(
		0.f, 0.f, HitBoxEvevationOffset);

	World->OverlapMultiByChannel(
		OverlapResults,
		HitBoxLocation,
		FQuat::Identity,
		ECC_Visibility,
		SphereShape,
		QueryParams,
		ResponseParams
	);

	if (bDrawDebugs)
	{
		DrawDebugSphere(
			World,
			HitBoxLocation,
			HitBoxRadius,
			12,
			FColor::Red,
			false,
			3.f
		);
		for (auto& Result : OverlapResults)
		{
			if (IsValid(Result.GetActor()))
			{
				FVector DrawDebugCenter = Result.GetActor()->GetActorLocation();
				DrawDebugCenter.Z += 100.f;
				DrawDebugSphere(
					World,
					DrawDebugCenter,
					20.f,
					12,
					FColor::Green,
					false,
					3.f
				);
			}
		}
	}
}
