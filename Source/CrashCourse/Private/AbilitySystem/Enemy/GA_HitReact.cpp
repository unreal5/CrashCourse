// 版权没有，拷贝自由。


#include "AbilitySystem/Enemy/GA_HitReact.h"

void UGA_HitReact::CacheHitDirectionVectors(AActor* InInstigator)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!IsValid(AvatarActor) || !IsValid(InInstigator)) return;
	
	AvatarForward = AvatarActor->GetActorForwardVector();
	ToInstigator = (InInstigator->GetActorLocation() - AvatarActor->GetActorLocation()).GetSafeNormal2D();
	
}
