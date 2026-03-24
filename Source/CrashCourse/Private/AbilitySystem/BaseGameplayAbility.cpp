// 版权没有，拷贝自由。


#include "AbilitySystem/BaseGameplayAbility.h"

void UBaseGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (bDrawDebug && IsValid(GEngine))
	{
		bool bIsAuthority = ActorInfo->IsNetAuthority();
		FString DebugMessage = FString::Printf(TEXT("Activated Ability: %s，在[%s]上"), *GetName(), bIsAuthority ? TEXT("服务器") : TEXT("客户端"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, DebugMessage);
	}
}
