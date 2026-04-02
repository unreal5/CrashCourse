// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MainPlayerCharacter.generated.h"


UCLASS()
class CRASHCOURSE_API AMainPlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AMainPlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;
	
	// 辅助函数 - 初始化 ASC 的 ActorInfo
	void InitializeAbilityActorInfo();
};
