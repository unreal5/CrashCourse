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

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(EnemyAsc)) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

	if (!HasAuthority()) return;

	GiveStartupAbilities();
}
