#pragma once
#include "PluginSDK.h"

class Indicator
{
public:
	IUnit* hero;
	bool Fill;
	bool Enabled;
	Indicator(bool E, bool f);
	void drawDmg(float dmg);
};