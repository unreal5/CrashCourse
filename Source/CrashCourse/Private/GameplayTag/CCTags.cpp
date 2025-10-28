// 版权没有，拷贝自由。


#include "GameplayTag/CCTags.h"


namespace CCTags
{
	namespace CCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "CCTags.CCAbilities.ActivateOnGiven", "被赋予技能时，如果有这个标记，则激活");

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "CCTags.CCAbilities.Primary", "主技能标记");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "CCTags.CCAbilities.Secondary", "次技能标记");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Teriary, "CCTags.CCAbilities.Teriary", "第三技能标记");
	}
	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "CCTags.Events.Enemy.HitReact", "敌人受击反应事件");
		}
	}
}
