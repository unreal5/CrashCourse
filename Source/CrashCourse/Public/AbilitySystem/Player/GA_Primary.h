// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/BaseGameplayAbility.h"
#include "GameplayTag/CCTags.h"
#include "GA_Primary.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UGA_Primary : public UBaseGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	TArray<AActor*> HitBoxOverlapTest() const;
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	void SendHitReactEventToActors(const TArray<AActor*>& HitActors, const FGameplayTag& Tag) const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Crash|Abilities")
	FGameplayTag HitEventTag = CCTags::Events::Enemy::HitReact;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	float HitBoxRadius = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	float HitBoxForwardOffset = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	float HitBoxElevationOffset = 20.f;

private:
	void DrawHitBoxOverlapDebugs(const TArray<AActor*>& Overlaps, const FVector& HitBoxLocation) const;
};
