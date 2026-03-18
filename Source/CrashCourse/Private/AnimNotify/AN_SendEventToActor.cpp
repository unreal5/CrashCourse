// 版权没有，拷贝自由。


#include "AnimNotify/AN_SendEventToActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAN_SendEventToActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	// 基类实现会调用蓝图事件。
	Super::Notify(MeshComp, Animation, EventReference);

	auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());
	if (!IsValid(ASC)) return;

	AActor* Owner = ASC->GetOwnerActor();
	if (!IsValid(Owner)) return;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, EventTag, FGameplayEventData{});
}

FLinearColor UAN_SendEventToActor::GetEditorColor()
{
	return FLinearColor::Yellow;
}

FString UAN_SendEventToActor::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("发送事件: %s"), *EventTag.ToString());
}


