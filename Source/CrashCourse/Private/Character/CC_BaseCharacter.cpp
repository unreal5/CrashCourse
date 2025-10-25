// 版权没有，拷贝自由。


#include "Character/CC_BaseCharacter.h"


ACC_BaseCharacter::ACC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	// 无论是否可见，都刷新骨骼和动画，否则在不可见时动画不会更新，导致dedicated服务器上角色姿势错误。
	// 许多动画相关的功能都依赖于在专门的服务器上正确更新动画。
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* ACC_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}
