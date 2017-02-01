#include "stdafx.h"
#include "Indicator.h"

	float width = 104;
	float height = 9;
	float OffsetX = 10;
	float OffsetY = 20;
	IUnit* hero;
	Vec2 startPos;

	Indicator::Indicator()
	{
	}

	void Indicator::setHero(IUnit* h)
	{
		hero = h;
	}

	IUnit* Indicator::getHero()
	{
		return hero;
	}

	Vec2 Indicator::getStartPosition(IUnit* hero)
	{
		if (hero != nullptr && hero->GetHPBarPosition(startPos))
		{
			startPos = Vec2(startPos.x + OffsetX, startPos.y + OffsetY);
			return startPos;
		}
		else
			return Vec2(0, 0);
	}

	float Indicator::getHpProc(float dmg)
	{
		float health = ((hero->GetHealth() - dmg) > 0) ? (hero->GetHealth() - dmg) : 0;
		return (health / hero->GetMaxHealth());
	}

	Vec2 Indicator::getHpPosAfterDmg(float dmg)
	{
		float w = getHpProc(dmg) * width;
		Vec2 pos = getStartPosition(hero);
		if (pos.x > 0 && pos.y > 0)
			return Vec2(pos.x + w, pos.y);
		else
			return Vec2(0, 0);
	}

	void Indicator::drawDmg(float dmg, Vec4 Color)
	{
		Vec2 hpPosNow = getHpPosAfterDmg(0);
		Vec2 hpPosAfter = getHpPosAfterDmg(dmg);
		if(hpPosAfter.x > 0 && hpPosAfter.y > 0)
			fillHPBar((int)hpPosNow.x - startPos.x, (int)hpPosAfter.x - startPos.x, Color);
	}

	void Indicator::fillHPBar(int to, int from, Vec4 Color)
	{
		Vec2 sPos = startPos;

		for (int i = from; i < to; i++)
		{
			GRender->DrawLine(Vec2(sPos.x + i, sPos.y), Vec2(sPos.x + i, sPos.y + 9), Color);
		}
	}
