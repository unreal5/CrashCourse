// 版权没有，拷贝自由。


#include "Utils/CC_BlueprintLibrary.h"

EHitDirection UCC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = TargetForward | ToInstigator;
	if (Dot > 0.707f) // cos(45°)
	{
		return EHitDirection::Forward;
	}
	else if (Dot < -0.707f) // cos(135°)
	{
		return EHitDirection::Backward;
	}
	else
	{
		//const float CrossZ = TargetForward.X * ToInstigator.Y - TargetForward.Y * ToInstigator.X;
		// 直接用 FVector 的叉积运算符 ^ 来计算，结果的 Z 分量就是我们需要的值。
		const FVector Cross = TargetForward ^ ToInstigator;
		const float CrossZ = Cross.Z;
		return CrossZ > 0 ? EHitDirection::Right : EHitDirection::Left;
	}
}

FName UCC_BlueprintLibrary::GetHitDirectionName(EHitDirection HitDirection)
{
	// 能完StaticEnum<EHitDirection>() 拿到 UEnum
	const UEnum* HitDirectionEnum = StaticEnum<EHitDirection>();
	if (!ensure(HitDirectionEnum != nullptr))
	{
		return NAME_None;
	}

	// 用 GetNameStringByValue(...) 取到枚举项名
	return FName(*HitDirectionEnum->GetNameStringByValue(static_cast<int64>(HitDirection)));
}
