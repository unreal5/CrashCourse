// 版权没有，拷贝自由。


#include "UI/BaseWidgetComponent.h"

#include "BaseAttributeWidget.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Character/BaseCharacter.h"


void UBaseWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystemData();
	if (!IsASCInitialized())
	{
		if (CrashCharacter.IsValid())
		{
			// 如果 ASC 没有初始化，说明 Character 还没有触发 ASC 初始化完成的委托。我们需要监听这个委托，以便在 ASC 初始化完成后获取相关数据。
			CrashCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		}
		return;
	}

	InitializeAttributeDelegates();
}

void UBaseWidgetComponent::InitAbilitySystemData()
{
	CrashCharacter = Cast<ABaseCharacter>(GetOwner());
	if (!CrashCharacter.IsValid()) return;

	CrashAttributeSet = Cast<UBaseAttributeSet>(CrashCharacter->GetAttributeSet());

	CrashASC = Cast<UBaseAbilitySystemComponent>(CrashCharacter->GetAbilitySystemComponent());
	if (!CrashASC.IsValid()) return;
}

bool UBaseWidgetComponent::IsASCInitialized() const
{
	return CrashASC.IsValid() && CrashAttributeSet.IsValid();
}

void UBaseWidgetComponent::InitializeAttributeDelegates()
{
	if (!CrashAttributeSet->bAttributesInitialized)
	{
		CrashAttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::BindToAttributeChange);
	}
	else
	{
		BindToAttributeChange();
	}
}


void UBaseWidgetComponent::OnASCInitialized(UAbilitySystemComponent* Asc, UAttributeSet* AttributeSet)
{
	CrashAttributeSet = Cast<UBaseAttributeSet>(CrashCharacter->GetAttributeSet());
	CrashASC = Cast<UBaseAbilitySystemComponent>(CrashCharacter->GetAbilitySystemComponent());


	if (!IsASCInitialized()) return;

	InitializeAttributeDelegates();
}

void UBaseWidgetComponent::BindToAttributeChange()
{
	//UE_LOG(LogTemp, Log, TEXT("BindToAttributeChange called in BaseWidgetComponent"));

	for (const auto& Item : AttributeMap)
	{
		if (!Item.Key.IsValid() || !Item.Value.IsValid()) continue;

		auto AttributeWidget = Cast<UBaseAttributeWidget>(GetUserWidgetObject());
		if (!IsValid(AttributeWidget)) continue;

		BindWidgetToAttributeChange(AttributeWidget, Item);
		AttributeWidget->WidgetTree->ForEachWidget([this, &Item](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChange(ChildWidget, Item);
			return true;
		});
	}
}

void UBaseWidgetComponent::BindWidgetToAttributeChange(UWidget* InWidgetObject,
                                                       const TTuple<FGameplayAttribute, FGameplayAttribute>&
                                                       InAttributes) const
{
	// 检查持有的UserWidget对象是否是UBaseAttributeWidget类型，如果是，则调用它的OnAttributeChanged方法。
	auto AttributeWidget = Cast<UBaseAttributeWidget>(InWidgetObject);
	if (!IsValid(AttributeWidget) || !AttributeWidget->MatchAttributes(InAttributes)) return;

	// 初始化
	AttributeWidget->OnAttributeChanged(InAttributes, CrashAttributeSet.Get());
	// 绑定属性变化的委托，当属性发生变化时，调用UserWidget对象的OnAttributeChanged方法。
	CrashASC->GetGameplayAttributeValueChangeDelegate(InAttributes.Key).AddLambda(
		[AttributeWidget, &InAttributes, this](const FOnAttributeChangeData& Data)
		{
			AttributeWidget->OnAttributeChanged(InAttributes, CrashAttributeSet.Get());
		});
}
