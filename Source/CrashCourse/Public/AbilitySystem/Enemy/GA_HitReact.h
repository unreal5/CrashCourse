// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/BaseGameplayAbility.h"
#include "GA_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UGA_HitReact : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Crash|HitReact")
	void CacheHitDirectionVectors(AActor* InInstigator);
	
	UPROPERTY(BlueprintReadOnly, Category="Crash|HitReact")
	FVector AvatarForward;
	UPROPERTY(BlueprintReadOnly, Category="Crash|HitReact")
	FVector ToInstigator;
};
