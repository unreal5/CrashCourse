// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/CC_GameplayAbility.h"
#include "CC_Primary.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CRASHCOURSE_API UCC_Primary : public UCC_GameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category="Crash|Ability")
	void HitBoxOverlapTest();

private:
	UPROPERTY(EditDefaultsOnly, Category="Crash|Ability")
	float HitBoxRadius = 100.f;
	UPROPERTY(EditDefaultsOnly, Category="Crash|Ability")
	float HitBoxForwardOffset = 200.f;
	UPROPERTY(EditDefaultsOnly, Category="Crash|Ability")
	float HitBoxEvevationOffset = 20.f;
};
