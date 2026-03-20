// 版权没有，拷贝自由。


#include "AbilitySystem/Player/GA_Primary.h"

#include "Engine/OverlapResult.h"

void UGA_Primary::HitBoxOverlapTest()
{
	auto AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor) return;

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(AvatarActor);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(IgnoredActors);

	//只能在C+++里设置碰撞查询参数，蓝图里设置不了。
	// 蓝图只可以设置与所有碰撞通道的响应，然后再过滤掉不需要的通道，无法直接设置每个通道的响应。
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECollisionResponse::ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	TArray<FOverlapResult> Overlaps;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	FVector ForwardVector = AvatarActor->GetActorForwardVector() * HitBoxForwardOffset;
	FVector StartLocation = AvatarActor->GetActorLocation() + ForwardVector + FVector(0, 0, HitBoxElevationOffset);
	GetWorld()->OverlapMultiByChannel(Overlaps,
	                                  StartLocation,
	                                  FQuat::Identity,
	                                  ECC_Pawn,
	                                  Sphere,
	                                  QueryParams,
	                                  ResponseParams);
	if (!bDrawDebug)
		return;

	for (const FOverlapResult& Overlap : Overlaps)
	{
		if (AActor* OverlappedActor = Overlap.GetActor())
		{
			UE_LOG(LogTemp, Log, TEXT("HitBox overlapped with: %s"), *OverlappedActor->GetName());
			// 在这里可以对OverlappedActor进行伤害处理或其他逻辑
			DrawDebugSphere(GetWorld(), OverlappedActor->GetActorLocation(), 20.f, 12, FColor::Red, false, 10.0f);
		}
	}
}
