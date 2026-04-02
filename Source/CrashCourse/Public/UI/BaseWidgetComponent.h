// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "BaseWidgetComponent.generated.h"


class UBaseAttributeSet;
class UBaseAbilitySystemComponent;
class ABaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRASHCOURSE_API UBaseWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;
private:
	TWeakObjectPtr<ABaseCharacter> CrashCharacter;
	TWeakObjectPtr<UBaseAbilitySystemComponent> CrashASC;
	TWeakObjectPtr<UBaseAttributeSet> CrashAttributeSet;

	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegates();
	void BindWidgetToAttributeChange(UWidget* InWidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& InAttributes) const;
	
	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* Asc, UAttributeSet* AttributeSet);
	UFUNCTION()
	void BindToAttributeChange();
};
