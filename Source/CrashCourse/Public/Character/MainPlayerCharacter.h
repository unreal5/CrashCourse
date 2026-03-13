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
private:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;
};
