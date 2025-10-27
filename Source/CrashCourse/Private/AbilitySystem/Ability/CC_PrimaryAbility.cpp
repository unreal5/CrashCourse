// 版权没有，拷贝自由。


#include "AbilitySystem/Ability/CC_PrimaryAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UCC_PrimaryAbility::UCC_PrimaryAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bRetriggerInstancedAbility = false;
}

void UCC_PrimaryAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!IsValid(AbilityMontage))
	{
		K2_EndAbility();
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		// EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		K2_EndAbility();
		return;
	}

	// 在两个地方可以触发：1、服务端；2、客户端有预测键。
	/* 预测键是由该Ability的Owner生成的，只有在客户端才会有预测键。 */
	if (!HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		// EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		K2_EndAbility();
		return;
	}
	// 使用C++实现“PlayMontageAndWait”任务
	// 工厂模式：创建，设置，激活。
	auto MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AbilityMontage);
	if (!MontageTask)
	{
		K2_EndAbility();
		return;
	}
	// 绑定委托
	MontageTask->OnBlendOut.AddDynamic(this, &ThisClass::K2_EndAbility);
	MontageTask->OnInterrupted.AddDynamic(this, &ThisClass::K2_EndAbility);
	MontageTask->OnCancelled.AddDynamic(this, &ThisClass::K2_EndAbility);
	MontageTask->OnCompleted.AddDynamic(this, &ThisClass::K2_EndAbility);
	// 启动任务（Task完成准备工作）
	MontageTask->ReadyForActivation();
}
