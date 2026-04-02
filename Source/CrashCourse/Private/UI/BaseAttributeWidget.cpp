// 版权没有，拷贝自由。


#include "BaseAttributeWidget.h"
#include "AbilitySystem/BaseAttributeSet.h"

void UBaseAttributeWidget::OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute>& InAttributes, UBaseAttributeSet* AttributeSet)
{
	const float AttributeValue = InAttributes.Key.GetNumericValue(AttributeSet);
	const float MaxAttributeValue = InAttributes.Value.GetNumericValue(AttributeSet);

	BP_OnAttributeChanged(AttributeValue, MaxAttributeValue);
}

bool UBaseAttributeWidget::MatchAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& InAttributes) const
{
	return Attribute == InAttributes.Key && MaxAttribute == InAttributes.Value;
}
