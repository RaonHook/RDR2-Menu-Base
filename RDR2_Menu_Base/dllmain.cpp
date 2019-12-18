//Simple RDR2 Menu Base by Raon Hook

#include "inc/types.h"
#include "inc/natives.h"
#include "inc/Menu_Constructor.h"
#include "inc/enums.h"
#include "inc/Game_Functions.h"

float playerScale = 1;
void SetPlayerScale() 
{
	PED::_0x25ACFC650B65C538(PLAYER::PLAYER_PED_ID(), playerScale);
}

void TeleportForward()
{
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0, 0);
	float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	pos.x += sin(-heading * (PI / 180)) * 10;
	pos.y += cos(heading * (PI / 180)) * 10;
	ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), pos.x, pos.y, pos.z, 1, 0, 1, 0);
}

bool ExampleBool = false;

//Menu Loop | Everything gets called within here
void main()
{
	ButtonMonitoring();
	switch (submenu)
	{
	case Main_Menu:
		addTitle("Main Menu");
		addHeader("Menu Base by Raon Hook");
		addSubmenuOption("Submenu 1", Submenu1, [] { PrintSubtitle("This subtitle was called before the menu changed\nUseful when needing to initialize something beforehand"); });
		addBoolOption("Invincible", PLAYER::GET_PLAYER_INVINCIBLE(0), [] {PLAYER::SET_PLAYER_INVINCIBLE(0, !PLAYER::GET_PLAYER_INVINCIBLE(0)); });
		addBoolOption("Invisibility", !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID()), [] {ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID())); });
		addFloatOption("Set Player Scale", &playerScale, 0.1f, SetPlayerScale);
		addOption("Teleport Forward", TeleportForward);
		addBoolOption("Example Bool", ExampleBool, [] {ExampleBool = !ExampleBool; });
		break;
	case Submenu1:
		addTitle("Submenu 1");
		addOption("Option");
		addSubmenuOption("Submenu 2", Submenu2);
		break;
	case Submenu2:
		addTitle("Submenu 2");
		addOption("Option");
		break;
	}
	resetVars();
}

void scriptMain() {
	srand(GetTickCount());
	while (true) {
		main();
		WAIT(0);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		scriptRegister(hModule, scriptMain);
		break;
	case DLL_PROCESS_DETACH:
		scriptUnregister(hModule);
		break;
	}
	return TRUE;
}

