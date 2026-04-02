// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "BaseAttributeWidget.generated.h"


class UBaseAttributeSet;
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UBaseAttributeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Carsh | Attribute")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Carsh | Attribute")
    FGameplayAttribute MaxAttribute;

	void OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& InAttributes, UBaseAttributeSet* AttributeSet);

	bool MatchAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& InAttributes) const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Crash | Attribute", meta = (DisplayName = "On Attribute Changed"))
	void BP_OnAttributeChanged(const float Value, const float MaxValue);
};
