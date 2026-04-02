// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

class UAttributeSet;
class UBaseAbilitySystemComponent;
class UAbilitySystemComponent;

UCLASS()
class CRASHCOURSE_API AMainPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMainPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
protected:
	UBaseAbilitySystemComponent* GetBaseAbilitySystemComponent() const;

	// Blueprint 子类已经依赖这个默认子对象；后续请尽量只改访问器，不要再改底层 UPROPERTY 名。
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CrashCourse|AbilitySystem")
	TObjectPtr<UBaseAbilitySystemComponent> CharAsc;

private:
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
