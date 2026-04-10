// 版权没有，拷贝自由。


#include "Tasks/BaseAttributeChangeTask.h"

#include "AbilitySystemComponent.h"

UBaseAttributeChangeTask* UBaseAttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* InASC,
                                                                             FGameplayAttribute InAttribute)
{
	if (!InASC) return nullptr;

	auto WaitForAttributeChangedTask = NewObject<ThisClass>();
	if (!WaitForAttributeChangedTask) return nullptr;
	WaitForAttributeChangedTask->ASC = InASC;
	WaitForAttributeChangedTask->AttributeToListenFor = InAttribute;

	InASC->GetGameplayAttributeValueChangeDelegate(InAttribute).AddUObject(
		WaitForAttributeChangedTask, &UBaseAttributeChangeTask::AttributeChanged);
	
	return WaitForAttributeChangedTask;
}

void UBaseAttributeChangeTask::EndTask()
{
	if (ASC.IsValid())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}
	// MarkPendingKill() will mark the object for garbage collection, but it won't be collected until the next GC cycle. This is useful for cleaning up objects that are no longer needed, but it allows any pending operations to complete before the object is destroyed. In this case, it ensures that any pending attribute change notifications are processed before the task is destroyed.
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UBaseAttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
