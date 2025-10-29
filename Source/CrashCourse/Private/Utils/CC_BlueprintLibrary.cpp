// 版权没有，拷贝自由。


#include "Utils/CC_BlueprintLibrary.h"

#include "KismetAnimationLibrary.h"

EHitDirection UCC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	// 可以使用UKismetAnimationLibrary计算速度和朝向的夹角直接得到方向，这里的代码不过是重新发明轮子而已。
	EHitDirection Result = EHitDirection::Forward;

	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);
	
	if (Dot < -0.5f)
	{
		return Result = EHitDirection::Back;
	}
	if (Dot < 0.5f)
	{
		// 左右
		FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		Result = Cross.Z > 0.f ? EHitDirection::Right : EHitDirection::Left;
	}
	// 其它，正前方
	return Result;
	
}

FName UCC_BlueprintLibrary::GetHitDirectionName(const EHitDirection& InHitDirection)
{
	// 标准做法：
	// switch (InHitDirection)
	// {
	// case EHitDirection::Forward:
	// 	return FName(TEXT("Forward"));
	// case EHitDirection::Back:
	// 	return FName(TEXT("Back"));
	// case EHitDirection::Left:
	// 	return FName(TEXT("Left"));
	// case EHitDirection::Right:
	// 	return FName(TEXT("Right"));
	// default:
	// 	check(false);
	// 	return FName(TEXT("None"));
	// }
	// 这里为了学习，使用反射：
	if (const UEnum* Enum = StaticEnum<EHitDirection>())
	{
		// 使用 GetNameStringByValue 返回无前缀的枚举名，便于直接作为 FName 使用
		const FString NameStr = Enum->GetNameStringByValue(static_cast<int64>(InHitDirection));
		if (!NameStr.IsEmpty())
		{
			return FName(*NameStr);
		}
	}

	// 反射失败或值无效时的回退值
	return FName(TEXT("None"));
}
