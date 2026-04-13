// 版权没有，拷贝自由。


#include "GameplayTag/CCTags.h"


namespace CCTags
{
	namespace CCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "CCTags.CCAbilities.ActivateOnGiven", "当给予时激活标签")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "CCTags.CCAbilities.Primary", "主要能力标签")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "CCTags.CCAbilities.Secondary", "次要能力标签")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "CCTags.CCAbilities.Tertiary", "第三能力标签")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, "CCTags.CCAbilities.Death", "死亡能力标签")

		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "CCTags.CCAbilities.Enemy.HitReact", "敌人受击反应能力标签")
		}
	}

	namespace Events
	{
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "CCTags.Events.Player.Primary", "玩家主要事件标签")
		}
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "CCTags.Events.Enemy.HitReact", "敌人受击反应事件标签")
		}
	}
}
