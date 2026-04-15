// 版权没有，拷贝自由。


#include "AbilitySystem/BaseAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameplayTag/CCTags.h"
#include "Net/UnrealNetwork.h"

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always)

	DOREPLIFETIME(ThisClass, bAttributesInitialized)
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//UE_LOG(LogTemp, Log, TEXT("对%s执行了一个GameplayEffect"), *Data.EvaluatedData.Attribute.GetName());
	if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() <= 0)
	{
		// TODO: Send a gameplay event to the causer of this effect.
		FGameplayEventData PayLoad;
		PayLoad.Instigator = Data.Target.GetAvatarActor();

		// 获取到造成伤害的源头（如果有的话）
		AActor* DamageCauser = Data.EffectSpec.GetEffectContext().GetInstigator();
		if (!IsValid(DamageCauser)) return;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(DamageCauser, CCTags::Events::KillScore, PayLoad);
	}

	if (!bAttributesInitialized)
	{
		bAttributesInitialized = true;
		OnAttributesInitialized.Broadcast();
	}
}

void UBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue)
}

void UBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue)
}

void UBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldValue)
}

void UBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, OldValue)
}

void UBaseAttributeSet::OnRep_AttributesInitialized(const bool& OldValue) const
{
	if (bAttributesInitialized)
	{
		OnAttributesInitialized.Broadcast();
	}
}
