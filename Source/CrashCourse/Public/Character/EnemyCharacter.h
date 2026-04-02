// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UAttributeSet;
class UBaseAbilitySystemComponent;
class UAbilitySystemComponent;

UCLASS()
class CRASHCOURSE_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	TObjectPtr<UBaseAbilitySystemComponent> EnemyAsc;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
