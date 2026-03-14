// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputAction;

UCLASS()
class CRASHCOURSE_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Crash|Input")
	TArray<TObjectPtr<class UInputMappingContext>> InputMappingContexts;
	
	UPROPERTY(EditAnywhere, Category="Crash|Input|Movement")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Crash|Input|Movement")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Crash|Input|Movement")
	UInputAction* LookAction;
	
	/** Abilities Input Action */
	UPROPERTY(EditAnywhere, Category="Crash|Input|Abilities")
	UInputAction* PrimaryAction;

private:
	void Primary();
};
