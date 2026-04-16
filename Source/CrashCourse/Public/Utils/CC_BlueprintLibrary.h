// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CC_BlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Forward,
	Backward,
};

USTRUCT(BlueprintType)
struct FClosestActorWithTagResult
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> Actor;
	UPROPERTY(BlueprintReadWrite)
	float Distance = 0.f;
};

UCLASS()
class CRASHCOURSE_API UCC_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Crash|Utils")
	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);

	UFUNCTION(BlueprintPure, Category="Crash|Utils")
	static FName GetHitDirectionName(EHitDirection HitDirection);
	
	UFUNCTION(BlueprintPure, Category="Crash|Utils")
	static FClosestActorWithTagResult FindClosestActorWithTag(UObject* WorldContextObject, const FVector& FromLocation, const FName& Tag);
};
