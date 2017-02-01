#include "stdafx.h"
#include "SpiffyC.h"

bool SpiffyCommon::CanHarass()
{
	return false;
}

bool SpiffyCommon::ShouldWait()
{
	return false;
}

float SpiffyCommon::GetEchoLudenDamage(IUnit * target)
{
	return 0.0f;
}

bool SpiffyCommon::CanHitSkillShot(IUnit * target, Vec3 Start, Vec3 End, ISpellData * SData)
{
	return false;
}

float SpiffyCommon::GetKsDamage(IUnit * t, ISpell2 * QWER, bool includeIncomingDamage)
{
	return 0.0f;
}

bool SpiffyCommon::ValidUlt(IUnit * target)
{
	return false;
}

bool SpiffyCommon::CanMove(IUnit * target)
{
	return false;
}

float SpiffyCommon::GetDistancePos(Vec3 pos1, Vec3 pos2)
{
	return (pos1 - pos2).Length2D();
}

auto SpiffyCommon::GetDistance(IUnit * player, IUnit * target)
{
	return (player->GetPosition() - target->GetPosition()).Length2D();
}

bool SpiffyCommon::IsUnderTurret(IUnit * Source, bool CheckAllyTurrets, bool CheckEnemyTurrets)
{
	return false;
}

int SpiffyCommon::CountEnemiesInRange(float range)
{
	int enemies = 0;
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && GEntityList->Player()->IsValidTarget(enemy, range))
			enemies++;
	}
	return enemies;
}

int SpiffyCommon::CountMinionsInRange(float range)
{
	int minions = 0;
	for (auto enemy : GEntityList->GetAllMinions(false, true,false))
	{
		if (enemy != nullptr && GEntityList->Player()->IsValidTarget(enemy, range))
			minions++;
	}
	return minions;
}

int SpiffyCommon::CountEnemiesInRangePos(float range, Vec3 pos)
{
	return 0;
}

int SpiffyCommon::AutosToKill(IUnit * target)
{
	return (int)target->GetHealth() / GDamage->CalcPhysicalDamage(GEntityList->Player(),target,GEntityList->Player()->PhysicalDamage());
}

void SpiffyCommon::PotionManager()
{
}
