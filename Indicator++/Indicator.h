#pragma once
#include "PluginSDK.h"

class Indicator
{
public:
	IUnit* hero;
	Indicator();
	void setHero(IUnit * h);
	IUnit * getHero();
	Vec2 getStartPosition(IUnit * hero);
	float getHpProc(float dmg);
	Vec2 getHpPosAfterDmg(float dmg);
	void drawDmg(float dmg, Vec4 Color);
	void fillHPBar(int to, int from, Vec4 Color);
};