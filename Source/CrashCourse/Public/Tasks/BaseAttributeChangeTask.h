// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "BaseAttributeChangeTask.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangeSignature, FGameplayAttribute, Attribute, float,
                                               NewValue, float, OldValue);

UCLASS()
class CRASHCOURSE_API UBaseAttributeChangeTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnAttributeChanged;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UBaseAttributeChangeTask* ListenForAttributeChange(UAbilitySystemComponent* InASC, FGameplayAttribute InAttribute);
	
	UFUNCTION(BlueprintCallable)
	void EndTask();
	
	void AttributeChanged(const FOnAttributeChangeData& Data) const;
private:
	TWeakObjectPtr<UAbilitySystemComponent> ASC;
	FGameplayAttribute AttributeToListenFor;
};
