// 版权没有，拷贝自由。


#include "Character/CC_EnemyCharacter.h"

#include "AbilitySystemComponent.h"


ACC_EnemyCharacter::ACC_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* ACC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC)) return;

	ASC->InitAbilityActorInfo(this, this);

	if (!HasAuthority())return;

	GiveStartupAbilities();
}
