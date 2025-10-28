// 版权没有，拷贝自由。


#include "AbilitySystem/Ability/Player/CC_Primary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "GameplayTag/CCTags.h"

TArray<AActor*> UCC_Primary::HitBoxOverlapTest()
{
	TArray<AActor*> HitActors;

	UWorld* World = GetWorld();
	if (!IsValid(World))
		return HitActors;

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetAvatarActorFromActorInfo());

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(IgnoredActors);

	// 设置ResponseParams，可以忽略某些碰撞通道
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	FCollisionShape SphereShape = FCollisionShape::MakeSphere(HitBoxRadius);

	TArray<FOverlapResult> OverlapResults;

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

	// 收集命中Actor
	for (auto& Result : OverlapResults)
	{
		if (!IsValid(Result.GetActor())) continue;

		HitActors.AddUnique(Result.GetActor());
	}

	// 发送命中事件
	SendGameplayEventToActors(HitActors);
	// 调试绘制
	if (bDrawDebugs)
	{
		DrawHitBoxOverlapDebugSphere(HitActors, HitBoxLocation);
	}
	return HitActors;
}

void UCC_Primary::SendGameplayEventToActors(const TArray<AActor*>& HitActors)
{
	// 发送命中事件
	for (auto& HitActor : HitActors)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, CCTags::Events::Enemy::HitReact, Payload);
	}
}

void UCC_Primary::DrawHitBoxOverlapDebugSphere(TArray<AActor*> OverlapActors, const FVector HitBoxLocation) const
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
		return;

	DrawDebugSphere(World, HitBoxLocation, HitBoxRadius, 12, FColor::Red, false, 3.f);
	for (auto& Result : OverlapActors)
	{
		FVector DrawDebugCenter = Result->GetActorLocation();
		DrawDebugCenter.Z += 100.f;
		DrawDebugSphere(World, DrawDebugCenter, 20.f, 12, FColor::Green, false, 3.f);
	}
}
