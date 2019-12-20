#pragma once
#include "Game_Functions.h"
#include "enums.h"

int submenu = 0;
int submenuLevel;
int lastSubmenu[20];
int lastOption[20];
int lastSubmenuMinOptions[20];
int lastSubmenuMaxOptions[20];
int currentOption;
int optionCount;
int maxOptions = 8;
bool optionPress = false;
int currentMenuMaxOptions = maxOptions;
int currentMenuMinOptions = 1;
bool leftPress = false;
bool rightPress = false;
bool fastLeftPress = false;
bool fastRightPress = false;
float menuX = 0.052f;
bool menuHeader = false;

void NULLVOID() {}

void CloseMenu()
{
	submenu = Closed;
	submenuLevel = 0;
	currentOption = 1;
}

void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	lastSubmenuMinOptions[submenuLevel] = currentMenuMinOptions;
	lastSubmenuMaxOptions[submenuLevel] = currentMenuMaxOptions;
	currentOption = 1;
	currentMenuMinOptions = 1;
	currentMenuMaxOptions = maxOptions;
	submenu = newSubmenu;
	submenuLevel++;
	optionPress = false;
}

void addTitle(const char* title) {
	optionCount = 0;
	draw_Text(title, menuX + 0.13f, 0.076f, 255, 255, 255, 255, true, 0.5f, 0.5f);
	drawRect(menuX, 0.073f, 0.260f, 0.104f, 0, 0, 0, 190);
	DrawSprite("generic_textures", "menu_header_1a", menuX, 0.058f, 0.260f, 0.074f, 0, 255, 255, 255, 255);
	DrawSprite("generic_textures", "hud_menu_4a", menuX, 0.131f + 0.027f, 0.260f, 0.002f, 0, 255, 255, 255, 255);
}

void addHeader(const char* header) 
{
	menuHeader = true;
	draw_Text(header, menuX + 0.13f, 0.076f + 0.0575f, 255, 255, 255, 255, true, 0.3f, 0.3f);
}

float bodyOffset = 0;

void addOption(const char* option, void (func)() = NULLVOID) {
	optionCount++;
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		draw_Text(option, menuX + 0.007f, 0.131f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 255, 255, 255, 255);
		drawRect(menuX, 0.124f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.260f, 0.038f, 0, 0, 0, 190);
		if (currentOption == optionCount) {
			DrawSprite("generic_textures", "selection_box_bg_1d", menuX, 0.124f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.260f, 0.038f, 0, 255, 0, 0, 190);
			if (optionPress)
				func();
		}
	}
}

void addSubmenuOption(const char* option, int submenu) {
	addOption(option);
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		DrawSprite("menu_textures", "selection_arrow_right", menuX + 0.235f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.01125f, 0.02f, 0, 255, 255, 255, 255);
		if(currentOption == optionCount)
			if (optionPress)
				changeSubmenu(submenu);
	}
}
void addSubmenuOption(const char* option, int submenu, void (func)()) {
	addOption(option);
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		DrawSprite("menu_textures", "selection_arrow_right", menuX + 0.235f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.01125f, 0.02f, 0, 255, 255, 255, 255);
		if(currentOption == optionCount){
			if (optionPress) {
				func();
				changeSubmenu(submenu);
			}
		}
	}
}

void addBoolOption(const char* option, bool var, void (func)() = NULLVOID) {
	addOption(option);
	if (currentOption <= currentMenuMaxOptions && optionCount <= currentMenuMaxOptions && currentOption >= currentMenuMinOptions && optionCount >= currentMenuMinOptions) {
		if (var) {
			DrawSprite("generic_textures", "tick_box", menuX + 0.232f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.0140625f, 0.025f, 0, 255, 255, 255, 255);
			DrawSprite("generic_textures", "tick", menuX + 0.232f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.0140625f, 0.025f, 0, 255, 255, 255, 255);
		}
		else {
			DrawSprite("generic_textures", "tick_box", menuX + 0.232f, 0.132f + (0.038f * ((optionCount - currentMenuMinOptions) + 1)), 0.0140625f, 0.025f, 0, 255, 255, 255, 255);
		}
		if (currentOption == optionCount)
			if (optionPress)
				func();
	}
}

void addIntOption(const char* option, int* var, int step = 1, bool fastPress = false, int min = -2147483647, int max = 2147483647) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %i >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (fastRightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		else
		{
			if (leftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (rightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
	}
}
void addIntOption(const char* option, int* var, void (func)(), int step = 1, bool fastPress = false, int min = -2147483647, int max = 2147483647) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %i >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (fastRightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		else
		{
			if (leftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (rightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		if (optionPress)
			func();
	}
}

void addFloatOption(const char* option, float* var, float step, bool fastPress = false, float min = -3.4028235e38, float max = 3.4028235e38) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %.03f >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (fastRightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		else
		{
			if (leftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (rightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
	}
}
void addFloatOption(const char* option, float* var, float step, void (func)(), bool fastPress = false, float min = -3.4028235e38, float max = 3.4028235e38) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %.03f >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (fastRightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		else
		{
			if (leftPress) {
				if (*var == min)
					*var = max;
				else
					*var -= step;
			}
			else if (rightPress) {
				if (*var == max)
					*var = min;
				else
					*var += step;
			}
		}
		if (optionPress)
			func();
	}
}

void addStringOption(const char* option, const char* var, int* intvar, int elementCount, bool fastPress = false) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %s >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*intvar == 0)
					*intvar = elementCount;
				else
					*intvar--;
			}
			else if (fastRightPress) {
				if (*intvar == elementCount)
					*intvar = 0;
				else
					*intvar++;
			}
		}
		else
		{
			if (leftPress) {
				if (*intvar == 0)
					*intvar = elementCount;
				else
					*intvar--;
			}
			else if (rightPress) {
				if (*intvar == elementCount)
					*intvar = 0;
				else
					*intvar++;
			}
		}
	}
}
void addStringOption(const char* option, const char* var, int* intvar, int elementCount, void (func)(), bool fastPress = false) {
	char buffer[64];
	snprintf(buffer, 64, "%s < %s >", option, *var);
	addOption(buffer);
	if (currentOption == optionCount) {
		if (fastPress) {
			if (fastLeftPress) {
				if (*intvar == 0)
					*intvar = elementCount;
				else
					*intvar--;
			}
			else if (fastRightPress) {
				if (*intvar == elementCount)
					*intvar = 0;
				else
					*intvar++;
			}
		}
		else
		{
			if (leftPress) {
				if (*intvar == 0)
					*intvar = elementCount;
				else
					*intvar--;
			}
			else if (rightPress) {
				if (*intvar == elementCount)
					*intvar = 0;
				else
					*intvar++;
			}
		}
		if (optionPress)
			func();
	}
}

void displayOptionIndex() {
	char buffer[32];
	snprintf(buffer, 32, "%i of %i", currentOption, optionCount);
	if (optionCount >= maxOptions) {
		draw_Text(buffer, menuX + 0.13f, 0.131f + (0.038f * (maxOptions + 1)), 255, 255, 255, 255, true);
		drawRect(menuX, 0.124f + (0.038f * (maxOptions + 1)), 0.260f, 0.038f, 0, 0, 0, 190);
		DrawSprite("generic_textures", "hud_menu_4a", menuX, 0.126f + (0.038f * (maxOptions + 1)), 0.260f, 0.002f, 0, 255, 255, 255, 255);
	} else {
		draw_Text(buffer, menuX + 0.13f, 0.131f + (0.038f * (optionCount + 1)), 255, 255, 255, 255, true);
		drawRect(menuX, 0.124f + (0.038f * (optionCount + 1)), 0.260f, 0.038f, 0, 0, 0, 190);
		DrawSprite("generic_textures", "hud_menu_4a", menuX, 0.126f + (0.038f * (optionCount + 1)), 0.260f, 0.002f, 0, 255, 255, 255, 255);
	}
}

void resetVars() 
{
	if (submenu != Closed) {
		displayOptionIndex();
	}
	optionPress = false;
	rightPress = false;
	leftPress = false;
	fastRightPress = false;
	fastLeftPress = false;
	menuHeader = false;
}

void ButtonMonitoring()
{
	if (submenu == Closed)
	{
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_LT")) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_LT")))
		{
			submenu = Main_Menu;
			submenuLevel = 0;
			currentOption = 1;
			currentMenuMinOptions = 1;
			currentMenuMaxOptions = maxOptions;
		}
	}
	else
	{
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_RDOWN"))) { //Enter
			optionPress = true;
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_RRIGHT"))) //Backspace
		{
			if (submenu == Main_Menu) {
				CloseMenu();
			}
			else
			{
				submenu = lastSubmenu[submenuLevel - 1];
				currentOption = lastOption[submenuLevel - 1];
				currentMenuMinOptions = lastSubmenuMinOptions[submenuLevel - 1];
				currentMenuMaxOptions = lastSubmenuMaxOptions[submenuLevel - 1];
				submenuLevel--;
			}
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_UP"))) //Scroll Up
		{
			if (currentOption == 1)
			{
				currentOption = optionCount;
				currentMenuMaxOptions = optionCount;
				if (optionCount > maxOptions)
					currentMenuMinOptions = optionCount - maxOptions + 1;
				else
					currentMenuMinOptions = 1;
			}
			else
			{
				currentOption--;
				if (currentOption < currentMenuMinOptions) {
					currentMenuMinOptions = currentOption;
					currentMenuMaxOptions = currentOption + maxOptions - 1;
				}
			}
		}

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_DOWN"))) //Scroll Down
		{
			if (currentOption == optionCount)
			{
				currentOption = 1;
				currentMenuMinOptions = 1;
				currentMenuMaxOptions = maxOptions;
			}
			else
			{
				currentOption++;
				if (currentOption > currentMenuMaxOptions) {
					currentMenuMaxOptions = currentOption;
					currentMenuMinOptions = currentOption - maxOptions + 1;
				}
			}
		}

		if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_LEFT"))) //Scroll Left
		{
			leftPress = true;
		}
		if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, joaat("INPUT_FRONTEND_RIGHT"))) //Scroll Right
		{
			rightPress = true;
		}

		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, joaat("INPUT_FRONTEND_LEFT"))) { 
			fastLeftPress = true;
		}
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, joaat("INPUT_FRONTEND_RIGHT"))) {
			fastRightPress = true;
		}
	}
}
