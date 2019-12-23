//Simple RDR2 Menu Base by Raon Hook

#include "inc/types.h"
#include "inc/natives.h"
#include "inc/Menu_Constructor.h"
#include "inc/enums.h"
#include "inc/Game_Functions.h"

void TeleportForward()
{
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0, 0);
	float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
	pos.x += sin(-heading * (PI / 180)) * 10;
	pos.y += cos(heading * (PI / 180)) * 10;
	ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), pos.x, pos.y, pos.z, 1, 0, 1, 0);
}

float playerScale = 1;
void SetPlayerScale() 
{
	PED::_0x25ACFC650B65C538(PLAYER::PLAYER_PED_ID(), playerScale);
}

int stringoptionint = 0;
const char* strings[6] = { "string 1", "string 2", "string 3", "string 4", "string 5", "string 6" };

struct pedModelInfo {
	const char* model;
	const char* name;
};
pedModelInfo Dogs[] = { {"A_C_DOGAMERICANFOXHOUND_01", "American Foxhound"},
{"A_C_DOGAUSTRALIANSHEPERD_01", "Australian Shepherd"},
{"A_C_DOGBLUETICKCOONHOUND_01", "Bluetick Coonhound"},
{"A_C_DOGCATAHOULACUR_01", "Catahoula Cur"},
{"A_C_DOGCHESBAYRETRIEVER_01", "Ches Bay Retriever"},
{"A_C_DOGCOLLIE_01", "Rough Collie"},
{"A_C_DOGHOBO_01", "Hobo"},
{"A_C_DOGHOUND_01", "Hound"},
{"A_C_DOGHUSKY_01", "Husky"},
{"A_C_DOGLAB_01", "Labrador"},
{"A_C_DOGLION_01", "Lion"},
{"A_C_DOGPOODLE_01", "Poodle"},
{"A_C_DOGRUFUS_01", "Rufus"},
{"A_C_DOGSTREET_01", "Street"} };
int CreatePed(Hash model) {
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model)) {
		STREAMING::REQUEST_MODEL(model, 0);
		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
		Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 5, 0);
		int ped = PED::CREATE_PED(model, pos.x, pos.y, pos.z, 0, 1, 0, 0, 0);
		PED::SET_PED_VISIBLE(ped, true);
		return ped;
	}
}

bool Godmode = false;
void GodmodeTick() {
	if (Godmode) {
		PLAYER::SET_PLAYER_INVINCIBLE(0, true);
		ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER::PLAYER_PED_ID(), 0), 0);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), false);
		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
	}
}

//Add functions that need to be called repeatedly here
void FunctionTicks()
{
	GodmodeTick();
}

//Menu Loop | Everything gets called within here
void main()
{
	FunctionTicks();
	ButtonMonitoring();
	switch (submenu)
	{
	case Main_Menu:
		addTitle("Main Menu");
		addHeader("Menu Base by Raon Hook");
		addSubmenuOption("Submenu 1", Submenu1, [] { PrintSubtitle("This subtitle was called before the menu changed\nUseful when needing to initialize something beforehand"); });
		addBoolOption("Godmode", Godmode, [] {Godmode = !Godmode; });
		addBoolOption("Invisibility", !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID()), [] {ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID())); });
		addFloatOption("Set Player Scale", &playerScale, 0.1f, SetPlayerScale);
		addOption("Teleport Forward", TeleportForward);
		addStringOption("String Option", strings[stringoptionint], &stringoptionint, ARRAYSIZE(strings) - 1, [] {PrintSubtitle(strings[stringoptionint]); });
		break;
	case Submenu1:
		addTitle("Submenu 1");
		addOption("Option");
		addSubmenuOption("Dog Spawner", DogSpawner_Menu);
		break;
	case DogSpawner_Menu:
		addTitle("Dog Spawner");
		for (int i = 0; i < ARRAYSIZE(Dogs); i++) //Increase int i until i == element count of Dogs[]
		{
			addOption(Dogs[i].name, [] { //Adds an option for every loop and Iterates through Dogs with value of i
				Hash model = GAMEPLAY::GET_HASH_KEY(Dogs[currentOption - 1].model); //You can't pass i through to the function so you must use currentOption - 1 (must subtract 1, as first option = 1, but element 1 of an array = 0)
				CreatePed(model); //Creates ped										//(If you had added an option before the for loop, you would use currentOption - 2, as optionCount would've Increased by 1)
			});
		}
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

