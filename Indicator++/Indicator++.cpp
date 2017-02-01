// Indicator++.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "PluginSDK.h"
#include "Indicator.h"

PluginSetup("Indicator++ - xSlapppz");

IMenu* MainMenu;
IMenu* Options;

IMenuOption* Q;
IMenuOption* W;
IMenuOption* E;
IMenuOption* R;
IMenuOption* IG;
IMenuOption* ColorR;
IMenuOption* ColorG;
IMenuOption* ColorB;
IMenuOption* AA;

ISpell* Qspell, *Wspell, *Espell, *Rspell, *Ignite;

Indicator HB = Indicator();

void Menu()
{
	MainMenu = GPluginSDK->AddMenu("Indicator++");
	Options = MainMenu->AddMenu("Options");
	AA = Options->AddInteger("Add Auto Attacks",0,15,0);
	Q = Options->CheckBox("Q",true);
	W = Options->CheckBox("W", true);
	E = Options->CheckBox("E", true);
	R = Options->CheckBox("R", true);
	IG = Options->CheckBox("Ignite", true);
	ColorR = Options->AddInteger("Red", 0, 255, 67);
	ColorG = Options->AddInteger("Green", 0, 255, 80);
	ColorB = Options->AddInteger("Blue", 0, 255, 233);
}

void Spells()
{
	Qspell = GPluginSDK->CreateSpell(kSlotQ, 999);
	Wspell = GPluginSDK->CreateSpell(kSlotW, 999);
	Espell = GPluginSDK->CreateSpell(kSlotE, 999);
	Rspell = GPluginSDK->CreateSpell(kSlotR, 999);
	Ignite = GPluginSDK->CreateSpell(GEntityList->Player()->GetSpellSlot("summonerdot"), 999);
}

double CalculateComboDamage(IUnit* enemy)
{
	double dmg = 0;
	
	if (Q->Enabled() && Qspell->IsReady())
		dmg += GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotQ);
	if (W->Enabled() && Wspell->IsReady())
		dmg += GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotW);
	if (E->Enabled() && Espell->IsReady())
		dmg += GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotE);
	if (R->Enabled() && Rspell->IsReady())
		dmg += GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotR);
	if (Ignite->GetSpellSlot() != kSlotUnknown && Ignite->IsReady())
		dmg += GDamage->GetSummonerSpellDamage(GEntityList->Player(), enemy, kSummonerSpellIgnite);
	if (AA->GetInteger() > 0)
		dmg += (GDamage->GetAutoAttackDamage(GEntityList->Player(), enemy, true) * AA->GetInteger());
	
	return dmg;
}

PLUGIN_EVENT(void) OnRender()
{
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && enemy->IsVisible() && !enemy->IsDead())
		{
			HB.setHero(enemy);
			HB.drawDmg(CalculateComboDamage(enemy), Vec4(ColorR->GetInteger(), ColorG->GetInteger(), ColorB->GetInteger(), 255));
		}
	}
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	// Initializes global interfaces for core access
	PluginSDKSetup(PluginSDK);
	Menu();
	Spells();
	GGame->PrintChat("Indicator++ Loaded!");

	GEventManager->AddEventHandler(kEventOnRender, OnRender);

}

// Called when plugin is unloaded
PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);

}