#pragma once
#include "types.h"
#include "natives.h"

Hash joaat(const char* string)
{
	return GAMEPLAY::GET_HASH_KEY(string);
}

void DrawSprite(const char* category, const char* sprite, float x, float y, float scalex, float scaley, float rotation, int r, int g, int b, int a)
{
	float fX = x + scalex / 2;
	float fY = y + scaley / 2;
	if (!TEXTURE::HAS_STREAMED_TEXTURE_DICT_LOADED(sprite))
		TEXTURE::REQUEST_STREAMED_TEXTURE_DICT(sprite, 0);
	GRAPHICS::DRAW_SPRITE(category, sprite, fX, fY, scalex, scaley, rotation, r, g, b, a, 1);
	TEXTURE::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(category);
}

void draw_Text(const char* text, float x, float y, int r, int g, int b, int a, bool centered = false, float sx = 0.342f, float sy = 0.342f)
{
	UI::SET_TEXT_COLOR_RGBA(r, g, b, a);
	UI::SET_TEXT_SCALE(sx, sy);
	UI::SET_TEXT_CENTRE(centered);
	const char* literalString = GAMEPLAY::CREATE_STRING(10, "LITERAL_STRING", text);
	UI::DRAW_TEXT(literalString, x, y);
}

void drawRect(float x, float y, float width, float height, int r, int g, int b, int a)
{
	float fX = x + width / 2;
	float fY = y + height / 2;
	GRAPHICS::DRAW_RECT(fX, fY, width, height, r, g, b, a, true);
}

void PrintSubtitle(const char* text)
{
	const char* literalString = GAMEPLAY::CREATE_STRING(10, "LITERAL_STRING", text);
	UILOG::_0xFA233F8FE190514C(literalString);
	UILOG::_0xE9990552DEC71600();
	UILOG::_0xDFF0D417277B41F8();
}
