// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"


UCLASS()
class CRASHCOURSE_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Crash|Attributes")
	FGameplayAttributeData Health;


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, Category="Crash|Attributes")
	FGameplayAttributeData MaxHealth;


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Crash|Attributes")
	FGameplayAttributeData Mana;


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Crash|Attributes")
	FGameplayAttributeData MaxMana;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, Health)
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MaxHealth)
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, Mana)
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MaxMana)

private:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
};
