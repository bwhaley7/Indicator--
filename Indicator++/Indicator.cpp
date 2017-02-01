#include "stdafx.h"
#include "Indicator.h"
#include "algorithm"

int xOffset = 10;
int yOffset = 20;
int Width = 103;
int Height = 8;
Vec4 Color = Vec4(105,198,5,255);
Vec4 FillColor = Vec4(198,176,5,255);

Indicator::Indicator(bool E, bool f)
{
	Indicator::Enabled = E;
	Indicator::Fill = f;
}

void Indicator::drawDmg(float dmg)
{
	if (!Enabled || dmg <= 0)
		return;

	for (auto hero : GEntityList->GetAllHeros(false, true))
	{
			Vec2 barPos = Vec2();
			if (hero->GetHPBarPosition(barPos))
			{
				float damage = dmg;
				float percentHealthAfterDamage = max(0, hero->GetHealth() - damage) / hero->GetMaxHealth();
				float yPos = barPos.y + yOffset;
				float xPosDamage = barPos.x + xOffset + Width * percentHealthAfterDamage;
				float xPosCurrentHp = barPos.x + xOffset + Width * hero->GetHealth() / hero->GetMaxHealth();

				if (damage > hero->GetHealth())
				{
					GRender->DrawTextW(Vec2(barPos.x + xOffset, barPos.y + yOffset - 13), Color, "Killable");
				}

				GRender->DrawLine(Vec2(xPosDamage, yPos), Vec2(xPosDamage, yPos + Height), Color);

				if (Fill)
				{
					float differenceInHP = xPosCurrentHp - xPosDamage;
					float pos1 = barPos.x + 9 + (107 * percentHealthAfterDamage);

					for (int i = 0; i < differenceInHP; i++)
					{
						GRender->DrawLine(Vec2(pos1 + i, yPos), Vec2(pos1 + i, yPos + Height), FillColor);
					}
				}
			}
	}
}
