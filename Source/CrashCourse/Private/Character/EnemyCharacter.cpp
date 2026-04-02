// 版权没有，拷贝自由。


#include "Character/EnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	EnemyAsc = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("BaseEnemyASC"));
	EnemyAsc->SetIsReplicated(true);
	EnemyAsc->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseEnemyAttributeSet"));
}

UAbilitySystemComponent* AEnemyCharacter::GetAbilitySystemComponent() const
{
	return EnemyAsc;
}

UAttributeSet* AEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(EnemyAsc)) return;

	auto ASC = GetAbilitySystemComponent();

	ASC->InitAbilityActorInfo(this, this);
	// 触发 ASC 初始化完成的委托，供 UI 等系统使用（服务与客户端都需要）。
	OnASCInitialized.Broadcast(ASC, GetAttributeSet());

	// 只有服务器需要给予初始技能和属性，因为客户端会通过 ASC 的 Replication 来同步这些数据。
	if (HasAuthority())
	{
		GiveStartupAbilities();
		InitializeAttributes();
	}
}
