// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SendEventToActor.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UAN_SendEventToActor : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Crash|AnimNotify")
	FGameplayTag EventTag;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;
	virtual FLinearColor GetEditorColor() override;
	virtual FString GetNotifyName_Implementation() const override;
};
