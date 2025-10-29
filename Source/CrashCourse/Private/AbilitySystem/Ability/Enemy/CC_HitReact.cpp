// 版权没有，拷贝自由。


#include "AbilitySystem/Ability/Enemy/CC_HitReact.h"

void UCC_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	
	const FVector AvatarLocaiton = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();
	
	ToInstigator = (InstigatorLocation - AvatarLocaiton).GetSafeNormal();
}
