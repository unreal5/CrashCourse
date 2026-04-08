// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRASHCOURSE_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="CrashCourse|Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> InAbilityClass, int32 InLevel);
	
	UFUNCTION(BlueprintCallable, Category="CrashCourse|Abilities")
	void AddToAbilityLevel(TSubclassOf<UGameplayAbility> InAbilityClass, int32 InLevel = 1);
protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;
private:
	void HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec);
};
