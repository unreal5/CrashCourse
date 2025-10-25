// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "CC_BaseCharacter.h"
#include "CC_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CRASHCOURSE_API ACC_PlayerCharacter : public ACC_BaseCharacter
{
	GENERATED_BODY()

public:
	ACC_PlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Called when this Pawn is possessed. Only called on the server (or in standalone).
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
