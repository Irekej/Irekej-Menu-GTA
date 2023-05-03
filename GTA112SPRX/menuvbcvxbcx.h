#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <string.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/process.h>
#include <ppu_intrinsics.h>
#include <stdarg.h>
#include <stdio.h>
#include <cstdlib>

#include "Natives.h"
#include "math.h"
#include "Functions.h"


void set_text_component(char* text)
{
	GRAPHICS::_0x3AC9CB55("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	GRAPHICS::_0x386CE0B8();
}
void instructionsSetup()
{
	mov = GRAPHICS::REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	GRAPHICS::_0x7B48E696(mov, 255, 255, 255, 0);
	GRAPHICS::_0x215ABBE8(mov, "CLEAR_ALL");
	GRAPHICS::_0x02DBF2D7();
	GRAPHICS::_0x215ABBE8(mov, "SET_CLEAR_SPACE");
	GRAPHICS::_0x716777CB(200);
	GRAPHICS::_0x02DBF2D7();
	instructCount = 0;
}
void addInstruction(int button, char* text)
{
	if (!instructionsSetupThisFrame)
	{
		instructionsSetup();
		instructionsSetupThisFrame = true;
	}
	GRAPHICS::_0x215ABBE8(mov, "SET_DATA_SLOT");
	GRAPHICS::_0x716777CB(instructCount);
	GRAPHICS::_0x716777CB(button);
	set_text_component(text);
	GRAPHICS::_0x02DBF2D7();
	instructCount++;
}
void instructionsClose()
{
	GRAPHICS::_0x215ABBE8(mov, "DRAW_INSTRUCTIONAL_BUTTONS");
	GRAPHICS::_0x02DBF2D7();
	GRAPHICS::_0x215ABBE8(mov, "SET_BACKGROUND_COLOUR");
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(0);
	GRAPHICS::_0x716777CB(80);
	GRAPHICS::_0x02DBF2D7();
}
void drawText2(char* text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_CENTRE(center);
	if (currentOption == optionCount)
	{
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
		UI::SET_TEXT_COLOUR(0, 0, 0, 100);
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(text);
	}
	else
	{
		UI::SET_TEXT_COLOUR(r, g, b, a);
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(text);
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scalex, scaley);
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
		UI::SET_TEXT_CENTRE(center);
	}
	UI::_DRAW_TEXT(x, y);
}
char opt[100];
void drawText(char* text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scalex, scaley);
		UI::SET_TEXT_CENTRE(center);
		if (currentOption == optionCount)
		{
			UI::SET_TEXT_WRAP(0.0f, 1.0f);
			UI::SET_TEXT_COLOUR(0, 0, 0, 255);
			snprintf(opt, sizeof(opt), "%s", text);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);
		}
		else
		{
			UI::SET_TEXT_COLOUR(r, g, b, a);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);;
			UI::SET_TEXT_WRAP(0.0f, 1.0f);
		}
		UI::_DRAW_TEXT(x, y);
	}
}
void drawText22(char* text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scalex, scaley);
		UI::SET_TEXT_CENTRE(center);
		if (currentOption == optionCount)
		{
			UI::SET_TEXT_WRAP(0.0f, 1.0f);
			UI::SET_TEXT_COLOUR(255, 255, 255, 255);
			snprintf(opt, sizeof(opt), "%s", text);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);
		}
		else
		{
			UI::SET_TEXT_COLOUR(r, g, b, a);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);;
			UI::SET_TEXT_WRAP(0.0f, 1.0f);
		}
		UI::_DRAW_TEXT(x, y);
	}
}
float Xpage = 0.755f;
void drawTextPage(char* text, int font, float y, float scalex, float scaley)
{
	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(text);
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scalex, scaley);
		UI::SET_TEXT_WRAP(0.1f, Xpage);
		UI::SET_TEXT_RIGHT_JUSTIFY(true);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::_DRAW_TEXT(0.144f, y);
		//UI::_DRAW_TEXT(0.885, y);
	}
}
void drawTextR(char* text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, int vari = 0, bool haha = false)
{
	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scalex, scaley);
		UI::SET_TEXT_RIGHT_JUSTIFY(true);
		UI::SET_TEXT_WRAP(0.1f, .91f - vari);
		if (!haha) {
			if (currentOption == optionCount)
			{
				UI::SET_TEXT_COLOUR(0, 0, 0, 255);
				UI::_SET_TEXT_ENTRY("STRING");
				UI::_ADD_TEXT_COMPONENT_STRING(text);
				snprintf(opt, sizeof(opt), "%s", text);
			}
			else
			{
				UI::SET_TEXT_COLOUR(r, g, b, a);
				UI::_SET_TEXT_ENTRY("STRING");
				UI::_ADD_TEXT_COMPONENT_STRING(text);
			}
		}
		else {
			UI::SET_TEXT_COLOUR(r, g, b, a);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);
		}
		UI::_DRAW_TEXT(x, y);
	}
}
void InfoText(char* text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(center);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x, y);
}
void titleText(char* text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x, y);
	UI::SET_TEXT_OUTLINE();
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
}
void drawCount(char* text, int font, float scaleX, float scaleY, int r, int g, int b, int a, float start, float end, float x, float y, bool otherside)
{
	UI::_SET_TEXT_ENTRY("STRING");
	UI::SET_TEXT_RIGHT_JUSTIFY(otherside);
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scaleX, scaleY);
	UI::SET_TEXT_WRAP(start, end);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x, y);
}
void DrawSprite(char* Streamedtexture, char* textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, r, g, b, a);
	}
}
void drawNotification(char* msg)
{
	if (menuXCoord == 0.845f)
	{
		UI::_0x574EE85C("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(msg);
		UI::_SET_NOTIFICATION_MESSAGE("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", true, 4, "Menu Base", "");
		UI::_DRAW_NOTIFICATION(false, true);
	}
	else
	{
		UI::_0xF42C43C7("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(msg);
		UI::_0x38F82261(3000, 1);
	}
}

bool isNumericChar(char x)
{
	return (x >= '0' && x <= '9') ? true : false;
}
int StoI(char* str)
{
	if (*str == NULL)
		return 0;

	int res = 0,
		sign = 1,
		i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; str[i] != '\0'; ++i)
	{
		if (isNumericChar(str[i]) == false)
			return 0;
		res = res * 10 + str[i] - '0';
	}
	return sign * res;
}

char* FtoS(float input)
{
	char returnvalue[64];
	int wholenumber = (int)input;
	input -= wholenumber;
	input *= 100;
	sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
	return returnvalue;
}
float xmemes = 0.735f;
void drawTextRight2(char* text, int font, float y, float scalex, float scaley)
{
	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(scalex, scaley);
		UI::SET_TEXT_RIGHT_JUSTIFY(true);
		if (currentOption == optionCount)
		{
			UI::SET_TEXT_SCALE(0.38f, 0.38f);
			UI::SET_TEXT_WRAP(0.1f, xmemes);
			UI::SET_TEXT_COLOUR(255, 244, 255, 255);
			snprintf(opt, sizeof(opt), "%s", text);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);
		}
		else
		{
			UI::SET_TEXT_COLOUR(255, 255, 255, 255);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);;
			UI::SET_TEXT_WRAP(0.1f, xmemes);
		}
		UI::_DRAW_TEXT(0.010f, y);
	}
}
float rightexty = 0.1795f;
void RightText(char* option)
{
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		drawTextRight2(option, optionsFont, (optionCount * 0.035f + rightexty), 0.36f, 0.36f);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		drawTextRight2(option, optionsFont, ((optionCount - (currentOption - maxOptions)) * 0.035f + rightexty), 0.36f, 0.36f);
	}
}
void startKeyboard(int action, char* defaultText, int maxLength)
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", defaultText, "", "", "", maxLength);
	keyboardAction = action;
	keyboardActive = true;
}
void changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	submenu = newSubmenu;
	submenuLevel++;
}
void SetupTimer(int tickTime)
{
	if (newTimerTick) {
		maxTimerCount = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick = false;
	}
}
bool IsTimerReady()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount;
}
void ResetTimer()
{
	newTimerTick = true;
}
void SetupTimer2(int tickTime)
{
	if (newTimerTick2) {
		maxTimerCount2 = GAMEPLAY::GET_GAME_TIMER() + tickTime;
		newTimerTick2 = false;
	}
}
bool IsTimerReady2()
{
	return GAMEPLAY::GET_GAME_TIMER() > maxTimerCount2;
}
void ResetTimer2()
{
	newTimerTick2 = true;
}

int gGlareHandle;
float gGlareDir;
float gGlarePosX = 0.625;
float gGlarePosY = 0.58;
float gGlareScaleX = 1.35;
float gGlareScaleY = 1.10;
float conv360(float base, float min, float max)
{
	float fVar0;
	if (min == max) return min;
	fVar0 = max - min;
	base -= round(base - min / fVar0) * fVar0;
	if (base < min) base += fVar0;
	return base;
}
void drawGlare()
{
	gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
	Vector3 rot = CAM::_GET_GAMEPLAY_CAM_ROT(2);
	float dir = conv360(rot.z, 0, 360);
	if ((gGlareDir == 0 || gGlareDir - dir > 0.5) || gGlareDir - dir < -0.5)
	{
		gGlareDir = dir;
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(gGlareHandle, "SET_DATA_SLOT");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(gGlareDir);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
	}
	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE(gGlareHandle, gGlarePosX, gGlarePosY, gGlareScaleX, gGlareScaleY, 255, 255, 255, 255, 0);
	}
}
void drawTextRightJustify(char* text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, int vari = 0)
{
	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		UI::SET_TEXT_FONT(font);//0.4755
		UI::SET_TEXT_SCALE(scalex, scaley);
		UI::SET_TEXT_RIGHT_JUSTIFY(true);
		UI::SET_TEXT_WRAP(0.0f, x);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		if (currentOption == optionCount)
		{
			UI::SET_TEXT_COLOUR(255, 255, 255, 255);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);
			snprintf(opt, sizeof(opt), "%s", text);
		}
		else
		{
			UI::SET_TEXT_COLOUR(r, g, b, a);
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING(text);;
		}
		UI::_DRAW_TEXT(x, y);
	}
}
#pragma endregion

#pragma region Option Helpers
void subTitle(char* title)
{
	drawText(title, bannerTextFont, menuXCoord, titley, 1.0f, 1.0f, 255, 255, 255, 255, true); // Banner Title
}

void addOption(char* option, char* info = NULL)
{
	optionCount++;
	if (currentOption == optionCount)
		infoText = info;
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		drawText(option, optionsFont, textXCoord, (optionCount * 0.035f + teztYCoord), 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		drawText(option, optionsFont, textXCoord, ((optionCount - (currentOption - maxOptions)) * 0.035f + teztYCoord), 0.35f, 0.35f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	}
}
float checky = 0.181f;
void CheckOn()
{
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		DrawSprite("srange_gen", "hits_dot", OnOff0404040, (optionCount * 0.035f + checky), 0.012 - 0.0012, 0.021 - 0.0021, 0, 0, 255, 0, 255);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		DrawSprite("srange_gen", "hits_dot", OnOff0404040, ((optionCount - (currentOption - maxOptions)) * 0.035f + checky), 0.012 - 0.0012, 0.021 - 0.0021, 0, 0, 255, 0, 255);
	}
}
void CheckOff()
{
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		DrawSprite("srange_gen", "hits_dot", OnOff0404040, (optionCount * 0.035f + checky), 0.012 - 0.0012, 0.021 - 0.0021, 0, 255, 103, 106, 255);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		DrawSprite("srange_gen", "hits_dot", OnOff0404040, ((optionCount - (currentOption - maxOptions)) * 0.035f + checky), 0.012 - 0.0012, 0.021 - 0.0021, 0, 255, 103, 106, 255);
	}
}
void spritesubs()
{
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		DrawSprite("mparrow", "mp_arrowxlarge", 0.745f, (optionCount * 0.035f + 0.231f), 0.010 - 0.0010, 0.020 - 0.0020, 0, 255, 255, 255, 255);

	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		DrawSprite("mparrow", "mp_arrowxlarge", 0.745f, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.231f), 0.010 - 0.0010, 0.020 - 0.0020, 0, 255, 255, 255, 255);
	}
}
void addSubmenuOption(char* option, int newSubmenu, char* info = NULL)
{
	spritesubs();
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			changeSubmenu(newSubmenu);
	}
}
/*void addBoolOption(char *right, bool b00l, char *info = NULL)
{
	char buf[30];
	if (b00l)
	{
		snprintf(buf, sizeof(buf), "%s", right);
		addOption(buf, info);
		CheckOn();
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", right);
		addOption(buf, info);
		CheckOff();

	}
}*/
void AddOptionRight(char* Option)
{
	if (currentOption <= maxOptions && optionCount <= maxOptions)
		drawText(Option, optionsFont, OnOff0404040, (optionCount * 0.035f + checky), WidthCheck, HeightCheck, optionsRed, optionsGreen, optionsBlue, optionsOpacity, 2);
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		drawText(Option, optionsFont, OnOff0404040, ((optionCount - (currentOption - maxOptions)) * 0.035f + checky), WidthCheck, HeightCheck, optionsRed, optionsGreen, optionsBlue, optionsOpacity, 2);
}
void addBoolOption(char* option, bool b00l, char* info = NULL)
{
	char buf[30];
	if (b00l)
	{
		snprintf(buf, sizeof(buf), "~g~~h~ON");
		addOption(option, info); AddOptionRight(buf);
	}
	else
	{
		snprintf(buf, sizeof(buf), "~r~~h~OFF");
		addOption(option, info); AddOptionRight(buf);
	}
}
template<typename TYPE>
void addCustomBoolOption(char* right, TYPE value, TYPE match, char* info = NULL)
{
	char buf[30];
	if (value == match)
	{
		snprintf(buf, sizeof(buf), "%s", right);
		addOption(buf, info);
		snprintf(buf, sizeof(buf), "~g~~h~ON");
		addOption(option, info); AddOptionRight(buf);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", right);
		addOption(buf, info);
		snprintf(buf, sizeof(buf), "~r~~h~OFF");
		addOption(option, info); AddOptionRight(buf);
	}
}
void Hud_Color(int r, int g, int b)
{
	UI::_SET_HUD_COLOUR(1, r, g, b, 255);
}
void CharLeftRightSprite(float X)
{
	if (currentOption <= maxOptions && optionCount <= maxOptions)
	{
		DrawSprite("commonmenu", "shop_arrows_upanddown", X, (optionCount * 0.035f + 0.1964f), 0.028 - 0.0028, 0.048 - 0.0048, 90, 100, 100, 100, 190);
	}
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
	{
		DrawSprite("commonmenu", "shop_arrows_upanddown", X, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.1964f), 0.028 - 0.0028, 0.048 - 0.0048, 90, 100, 100, 100, 190);
	}
}
float XChar = 0.745f;
void addChar(char* left, char** right, int* var, int min, int max, char* info = NULL)
{
	char buf[60];
	addOption(left, info);
	if (currentOption == optionCount)
	{
		snprintf(buf, sizeof(buf), "%s ~m~[%i/%i]", right[*var], *var, max);
		RightText(buf);
		CharLeftRightSprite(XChar);
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
	}
}
void addIntOption(char* option, int* var, int min, int max, bool keyboard, char* info = NULL)
{
	char buf[30];
	snprintf(buf, sizeof(buf), "%i", *var);
	addOption(option, info);
	RightText(buf);
	if (currentOption == optionCount)
	{
		CharLeftRightSprite(XChar);
		lrInstruction = true;
		if (rightPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + 1;
		}
		else if (leftPress)
		{
			playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - 1;
		}
		if (keyboard)
		{
			squareInstruction = true;
			if (squarePress)
			{
				startKeyboard(0, "", (strlen(ItoS(max)) + 1));
				keyboardVar = var;
			}
		}
	}
}
void addFloatOption(char* option, float* var, float min, float max, bool holdPress, char* info = NULL)
{
	char buf[30];
	snprintf(buf, sizeof(buf), "%s", FtoS(*var));
	addOption(option, info);
	RightText(buf);
	if (currentOption == optionCount)
	{
		CharLeftRightSprite(XChar);
		if (holdPress)
		{
			if (fastRightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.01f;
			}
			else if (fastLeftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.01f;
			}
		}
		else
		{
			if (rightPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 0.01f;
			}
			else if (leftPress)
			{
				playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 0.01f;
			}
		}
	}
}
void addKeyboardOption(char* option, int action, char* defaultText, int maxLength, char* info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			startKeyboard(action, defaultText, maxLength);
	}
}
bool cstrcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))s1++, s2++;
	if
		(*(const unsigned char*)s1 -
			*(const unsigned char*)s2 == 0)
		return true;
	else return false;
}
int getOption()
{
	xInstruction = true;
	if (optionPress)
		return currentOption;
	else return 0;
}
#pragma endregion

#pragma region Functions
#pragma region Char Options
int BannerInt;
char* BannerChar[] = { "Default", "Red", "Pink", "Orange","Purple","Yellow","Green","Cyan","Blue" };
void BannerColorOption()
{
	if (cstrcmp(BannerChar[BannerInt], "Default"))
	{
		bannerRectRed = 66;
		bannerRectGreen = 149;
		bannerRectBlue = 244;
	}
	if (cstrcmp(BannerChar[BannerInt], "Red"))
	{
		bannerRectRed = 255;
		bannerRectGreen = 0;
		bannerRectBlue = 0;
	}
	if (cstrcmp(BannerChar[BannerInt], "Pink"))
	{
		bannerRectRed = 255;
		bannerRectGreen = 0;
		bannerRectBlue = 148;
	}
	if (cstrcmp(BannerChar[BannerInt], "Orange"))
	{
		bannerRectRed = 255;
		bannerRectGreen = 119;
		bannerRectBlue = 0;
	}
	if (cstrcmp(BannerChar[BannerInt], "Purple"))
	{
		bannerRectRed = 229;
		bannerRectGreen = 0;
		bannerRectBlue = 255;
	}
	if (cstrcmp(BannerChar[BannerInt], "Yellow"))
	{
		bannerRectRed = 255;
		bannerRectGreen = 255;
		bannerRectBlue = 0;
	}
	if (cstrcmp(BannerChar[BannerInt], "Green"))
	{
		bannerRectRed = 55;
		bannerRectGreen = 255;
		bannerRectBlue = 0;
	}
	if (cstrcmp(BannerChar[BannerInt], "Cyan"))
	{
		bannerRectRed = 0;
		bannerRectGreen = 255;
		bannerRectBlue = 255;
	}
	if (cstrcmp(BannerChar[BannerInt], "Blue"))
	{
		bannerRectRed = 0;
		bannerRectGreen = 0;
		bannerRectBlue = 255;
	}
}

int ScrollerInt;
char* ScrollerChar[] = { "Default", "Red", "Pink", "Orange","Purple","Yellow","Green","Cyan","Blue" };
void ScrollerColorOption()
{
	if (cstrcmp(ScrollerChar[ScrollerInt], "Default"))
	{
		scrollerRed = 255;
		scrollerGreen = 255;
		scrollerBlue = 255;
	}
	if (cstrcmp(ScrollerChar[ScrollerInt], "Red"))
	{
		scrollerRed = 255;
		scrollerGreen = 0;
		scrollerBlue = 0;
	}
	if (cstrcmp(ScrollerChar[ScrollerInt], "Pink"))
	{
		scrollerRed = 255;
		scrollerGreen = 0;
		scrollerBlue = 148;
	}
	if (cstrcmp(ScrollerChar[ScrollerInt], "Orange"))
	{
		scrollerRed = 255;
		scrollerGreen = 119;
		scrollerBlue = 0;
	}
	if (cstrcmp(ScrollerChar[ScrollerInt], "Purple"))
	{
		scrollerRed = 229;
		scrollerGreen = 0;
		scrollerBlue = 255;
	}
	if (cstrcmp(ScrollerChar[ScrollerInt], "Yellow"))
	{
		scrollerRed = 255;
		scrollerGreen = 255;
		scrollerBlue = 0;
	}
	if (cstrcmp(ScrollerChar[ScrollerInt], "Green"))
	{
		scrollerRed = 55;
		scrollerGreen = 255;
		scrollerBlue = 0;
	}
	if (cstrcmp(ScrollerChar[ScrollerInt], "Cyan"))
	{
		scrollerRed = 0;
		scrollerGreen = 255;
		scrollerBlue = 255;
	}
	if (cstrcmp(ScrollerChar[ScrollerInt], "Blue"))
	{
		scrollerRed = 0;
		scrollerGreen = 0;
		scrollerBlue = 255;
	}
}

int backgroundInt;
char* backgroundChar[] = { "Default", "Red", "Pink", "Orange","Purple","Yellow","Green","Cyan","Blue" };
void backgroundColorOption()
{
	if (cstrcmp(backgroundChar[backgroundInt], "Default"))
	{
		backgroundRed = 16;
		backgroundGreen = 16;
		backgroundBlue = 16;
	}
	if (cstrcmp(backgroundChar[backgroundInt], "Red"))
	{
		backgroundRed = 255;
		backgroundGreen = 0;
		backgroundBlue = 0;
	}
	if (cstrcmp(backgroundChar[backgroundInt], "Pink"))
	{
		backgroundRed = 255;
		backgroundGreen = 0;
		backgroundBlue = 148;
	}
	if (cstrcmp(backgroundChar[backgroundInt], "Orange"))
	{
		backgroundRed = 255;
		backgroundGreen = 119;
		backgroundBlue = 0;
	}
	if (cstrcmp(backgroundChar[backgroundInt], "Purple"))
	{
		backgroundRed = 229;
		backgroundGreen = 0;
		backgroundBlue = 255;
	}
	if (cstrcmp(backgroundChar[backgroundInt], "Yellow"))
	{
		backgroundRed = 255;
		backgroundGreen = 255;
		backgroundBlue = 0;
	}
	if (cstrcmp(backgroundChar[backgroundInt], "Green"))
	{
		backgroundRed = 55;
		backgroundGreen = 255;
		backgroundBlue = 0;
	}
	if (cstrcmp(backgroundChar[backgroundInt], "Cyan"))
	{
		backgroundRed = 0;
		backgroundGreen = 255;
		backgroundBlue = 255;
	}
	if (cstrcmp(backgroundChar[backgroundInt], "Blue"))
	{
		backgroundRed = 0;
		backgroundGreen = 0;
		backgroundBlue = 255;
	}
}
#pragma


#pragma region Player Information 
float BannerYInfo = 0.6300;
float BannerWidthInfo = 0.4700;
float BannerHeightInfo = 0.0350;

float BackgroundYInfo = 0.7500;
float BackgroundWidthInfo = 0.4700;
float BackgroundHeightInfo = 0.2100;

float BottomYInfo = 0.8570;
float BottomWidthInfo = 0.4700;
float BottomHeightInfo = 0.0050;

float textinfoy = 0.6190;
float textinfox = 0.5200;

float LableXCoord = 0.291;
float XCoordIP = 0.750f;
float IPXCoord = 0.53f;
float YHi = 0.643;
float AnswerScale = 0.35;
#pragma region Misc Info Functions

#pragma region GET MONEY
int Read_Global(int a_uiGlobalID)
{
	int Ptr = *(int*)((0x1E70374 - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
	if (Ptr != 0)
		return *(int*)(Ptr + ((a_uiGlobalID % 0x40000) * 4));
	return 0;
}
int getPlayerStat(int player, int stat)
{
	return Read_Global(1581767 + (player * 306) + stat);
}
int getCash(int player)
{
	return getPlayerStat(selectedPlayer, 182);
}
#pragma endregion

#pragma region GET RANK
int getPlayerRank(int player)
{
	return getPlayerStat(player, 185);
}
#pragma endregion

#pragma region GET HOST
int GetHost()
{
	return NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
}
char* GetHostName()
{
	return PLAYER::GET_PLAYER_NAME(GetHost());
}
void Whose_Host(int client)
{
	char HST[50];
	memset(HST, 0, sizeof(HST));
	char* Host = GetHostName();
	if (strcmp(Host, GetHostName()))
		Host = "";
	snprintf(HST, 100, "%s", GetHostName());
	drawTextRightJustify(HST, 0, XCoordIP, 0.823, 0.6900, 0.3500, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, false);
}
#pragma endregion

#pragma endregion
float ItoF(int input)
{
	float Output = *(float*)&input;
	return Output;
}
void PlayerInfoMenuBase(bool isSelected)
{
	int KD = Read_Global(1581972 + (306 * selectedPlayer));
	float KD_Float = ItoF(KD);
	char* KD_String = FtoS(KD_Float);
	char KD_buf[90], MutedMe[50];
	snprintf(KD_buf, sizeof(KD_buf), "%s", KD_String);
	Vector3 clientCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	//player health
	char playerHealth[50];
	int health = ENTITY::GET_ENTITY_HEALTH(PLAYER::GET_PLAYER_PED(selectedPlayer));
	sprintf(playerHealth, "%d / 328", health);
	//Player Money
	char playerCash[50];
	sprintf(playerCash, "%d", getCash(selectedPlayer));
	//Player Rank
	char playerRank[50];
	sprintf(playerRank, "%d", getPlayerRank(selectedPlayer));
	//X Y Z 
	char XText[60];
	char YText[60];
	char ZText[60];
	int XCoord = clientCoords.x;
	int YCoord = clientCoords.y;
	int ZCoord = clientCoords.z;
	sprintf(XText, "%d", XCoord);
	sprintf(YText, "%d", YCoord);
	sprintf(ZText, "%d", ZCoord);
	//IP pulling :)
	char IPADDR1[4][50];
	char RegionBuffer[2][10];
	for (int i = 0; i < 34; i++)
	{
		int Handle[13];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER2(selectedPlayer, &Handle[0], 13);
		char* RealName = NETWORK::NETWORK_GET_GAMERTAG_FROM_HANDLE(&Handle[0]);
		char* ipName = PS3::ReadBytes(0x40025C80 + (i * 136), 100);
		if (!strcmp(RealName, ipName))
		{
			int ip = *(int*)(0x40025CC8 + (i * 0x88));
			int p1 = (ip & 0xff000000) >> 24;
			int p2 = (ip & 0x00ff0000) >> 16;
			int p3 = (ip & 0x0000ff00) >> 8;
			int p4 = (ip & 0x000000ff) >> 0;

			int internal_ip = *(int*)(0x40025CA8 + (i * 0x88));
			int p5 = (internal_ip & 0xff000000) >> 24;
			int p6 = (internal_ip & 0x00ff0000) >> 16;
			int p7 = (internal_ip & 0x0000ff00) >> 8;
			int p8 = (internal_ip & 0x000000ff) >> 0;

			char* Region = PS3::ReadBytes(0x40025c96 + (i * 0x88), 100);

			int port = *(int*)(0x40025ccd + (i * 0x88));
			int p9 = (port & 0xff000000) >> 24;
			int p10 = (port & 0x00ff0000) >> 16;
			int portToShow = (p9 << 8) | p10;

			sprintf(IPADDR1[0], "%i.%i.%i.%i", p1, p2, p3, p4);
			sprintf(IPADDR1[1], "%i.%i.%i.%i", p5, p6, p7, p8);
			sprintf(IPADDR1[2], "%s", Region);
			sprintf(IPADDR1[3], "%i", portToShow);

			if (strstr(IPADDR1[0], "255.255.255.255") == NULL && strstr(IPADDR1[0], "0.0.0.0") == NULL)
			{
				strcpy(RegionBuffer[0], IPADDR1[2]);
				memcpy(RegionBuffer[1], RegionBuffer[0], strlen(RegionBuffer[0]) - 3);

				drawTextRightJustify(IPADDR1[0], 0, XCoordIP, 0.643, 0.6900, 0.3500, 255, 255, 255, 255); //MAIN IP
				drawTextRightJustify(IPADDR1[1], 0, XCoordIP, 0.673, 0.6900, 0.3500, 255, 255, 255, 255); //PS3 IP
				drawTextRightJustify(IPADDR1[2], 0, XCoordIP, 0.703, 0.6900, 0.3500, 255, 255, 255, 255); //REGION
				drawTextRightJustify(IPADDR1[3], 0, XCoordIP, 0.733, 0.6900, 0.3500, 255, 255, 255, 255); //PORT

			}
			else
			{

			}
		}
	}

	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		for (int i = 1; i < 17; i++)
		{
			if (i % 2)
			{

			}
			else
			{
				GRAPHICS::DRAW_RECT(menuXCoord, BannerYInfo, BannerWidthInfo, BannerHeightInfo, bannerRectRed, bannerRectGreen, bannerRectBlue, 60); //Banner
				GRAPHICS::DRAW_RECT(menuXCoord, BackgroundYInfo, BackgroundWidthInfo, BackgroundHeightInfo, backgroundRed, backgroundGreen, backgroundBlue, 40); //Background
				GRAPHICS::DRAW_RECT(menuXCoord, 0.753f, 0.0019, 0.2, 150, 150, 150, 255); //mid line
				GRAPHICS::DRAW_RECT(menuXCoord, BottomYInfo, BottomWidthInfo, BottomHeightInfo, bannerRectRed, bannerRectGreen, bannerRectBlue, 60); //Bottom Bar
			}
		}
		drawText22(PLAYER::GET_PLAYER_NAME(selectedPlayer), 7, textinfox, textinfoy, 0.40f, 0.40f, 255, 255, 255, 255, true); // Title Text
		//health
		drawText22("Health:", 0, LableXCoord, 0.643, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawTextRightJustify(playerHealth, 0, 0.52, 0.643, 0.6900, 0.3500, 255, 255, 255, 255);
		//cash
		drawText22("Money:", 0, LableXCoord, 0.673, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawTextRightJustify(playerCash, 0, 0.52, 0.673, 0.6900, 0.3500, 255, 255, 255, 255);
		//Dead/Alive
		drawText22("State:", 0, LableXCoord, 0.703, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawTextRightJustify(PED::_IS_PED_DEAD(PLAYER::GET_PLAYER_PED(selectedPlayer), true) ? (char*)"Dead" : (char*)"Alive", 0, 0.52, 0.703, 0.6900, 0.3500, 255, 255, 255, 255, false);
		//Player armed
		drawText22("Armed:", 0, LableXCoord, 0.733, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawTextRightJustify(WEAPON::IS_PED_ARMED(PLAYER::GET_PLAYER_PED(selectedPlayer), 7) ? (char*)"Yes" : (char*)"No", 0, 0.52, 0.733, 0.6900, 0.3500, 255, 255, 255, 255, false);
		//X Coord
		drawText22("X:", 0, LableXCoord, 0.763, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawTextRightJustify(XText, 0, 0.52, 0.763, 0.6900, 0.3500, 255, 255, 255, 255);
		//Y Coord
		drawText22("Y:", 0, LableXCoord, 0.793, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawTextRightJustify(YText, 0, 0.52, 0.793, 0.6900, 0.3500, 255, 255, 255, 255);
		//Z Coord
		drawText22("Z:", 0, LableXCoord, 0.823, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawTextRightJustify(ZText, 0, 0.52, 0.823, 0.6900, 0.3500, 255, 255, 255, 255);
		//Player IP Lables
		drawText22("IP:", 0, IPXCoord, 0.643, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawText22("Internal IP:", 0, IPXCoord, 0.673, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawText22("Port:", 0, IPXCoord, 0.703, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawText22("Region:", 0, IPXCoord, 0.733, 0.6900, 0.3500, 255, 255, 255, 255, false);

		//kd
		drawText22("KD:", 0, IPXCoord, 0.763, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawTextRightJustify(KD_buf, 4, XCoordIP, 0.763, 0.6900, 0.3500, 255, 255, 255, 255);

		//muted
		sprintf(MutedMe, "%s", NETWORK::NETWORK_AM_I_MUTED_BY_PLAYER(selectedPlayer) ? "Yes" : "No");
		drawText22("Muted You:", 0, IPXCoord, 0.793, 0.6900, 0.3500, 255, 255, 255, 255, false);
		drawTextRightJustify(MutedMe, 0, XCoordIP, 0.793, 0.6900, 0.3500, 255, 255, 255, 255);

		//mandem
		Whose_Host(selectedPlayer);
		drawText22("Host:", 0, IPXCoord, 0.823, 0.6900, 0.3500, 255, 255, 255, 255, false);
	}
}
#pragma endregion

#pragma endregion

#pragma region Monitor
void monitorButtons()
{
	SetupTimer(20);
	if (submenu == Closed)
	{
		if (IsTimerReady())
		{
			if (CONTROLS::IS_CONTROL_PRESSED(0, BUTTON_R1) && CONTROLS::IS_CONTROL_PRESSED(0, BUTTON_L1))
			{
				submenu = Main_Menu;
				submenuLevel = 0;
				currentOption = 1;
				playSound("YES");
			}
			ResetTimer();
		}
	}
	else {
		if (IsTimerReady())
		{
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, BUTTON_CIRCLE))
			{
				if (submenu == Main_Menu)
				{
					submenu = Closed;
				}
				else
				{
					submenu = lastSubmenu[submenuLevel - 1];
					currentOption = lastOption[submenuLevel - 1];
					submenuLevel--;
				}
				playSound("Back");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, BUTTON_X))
			{
				optionPress = true;
				playSound("SELECT");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, DPAD_UP))
			{
				currentOption--;
				if (currentOption < 1)
				{
					currentOption = optionCount;
				}
				playSound("NAV_UP_DOWN");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, DPAD_DOWN))
			{
				currentOption++;
				if (currentOption > optionCount)
				{
					currentOption = 1;
				}
				playSound("NAV_UP_DOWN");
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, DPAD_RIGHT))
			{
				rightPress = true;
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, DPAD_LEFT))
			{
				leftPress = true;
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, DPAD_RIGHT))
			{
				fastRightPress = true;
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, DPAD_LEFT))
			{
				fastLeftPress = true;
			}
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, BUTTON_SQUARE))
			{
				squarePress = true;
			}
			ResetTimer();
		}
	}
}
int normalMenuActions()
{
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 19);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 20);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 21);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 27);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 54);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 123);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 124);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 125);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 126);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 138);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 139);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 140);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 177);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 178);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 179);
	CONTROLS::DISABLE_CONTROL_ACTION(0, 207);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 166);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 167);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 177);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 178);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 193);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 194);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 195);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 202);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 203);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 204);
	CONTROLS::SET_INPUT_EXCLUSIVE(2, 205);

	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		if (optionCount > maxOptions)
		{
			GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions + 1) * 0.035f) + infoy), MenuWidth, infoheight, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); // info
			DrawSprite("commonmenu", "shop_arrows_upanddown", menuXCoord, (((maxOptions + 1) * 0.035f) + infoy), 0.02f, 0.04f, 0, 255, 255, 255, 255); //Info Box
			GRAPHICS::DRAW_RECT(menuXCoord, BannerY, MenuWidth, BannerHeight, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); // Banner
			GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions * 0.035f) / 2) + backgroundy), MenuWidth, (maxOptions * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); // Background
			if (currentOption > maxOptions)
			{
				GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.197f), MenuWidth, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); // Scroller
				DrawSprite("commonmenu", "header_gradient_script", menuXCoord, ((maxOptions * 0.035f) + 0.197f), MenuWidth, 0.035f, 90, 255, 255, 255, 255);
			}
			else
			{
				GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.197f), MenuWidth, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); // Scroller
				DrawSprite("commonmenu", "header_gradient_script", menuXCoord, ((currentOption * 0.035f) + 0.197f), MenuWidth, 0.035f, 90, 255, 255, 255, 255);
			}
			char buffer[30];
			sprintf(buffer, "%i/%i", currentOption, optionCount);
			drawText22(buffer, 4, optioncouuntx, (((maxOptions + 1) * 0.035f) + infoy2), 0.60f, 0.60f, 255, 255, 255, 255, true);
			drawTextPage("Version 1.0", 7, ((maxOptions + 1) * 0.035f + 0.1787f), 0.47f, 0.47f);
			GRAPHICS::DRAW_RECT(menuXCoord - line1x, (((maxOptions * 0.035f) / 2) + liney), .002, (maxOptions * lineheight), bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
			GRAPHICS::DRAW_RECT(menuXCoord + line2x, (((maxOptions * 0.035f) / 2) + liney), .002, (maxOptions * lineheight), bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
		}
		else
		{
			GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount + 1) * 0.035f) + infoy), MenuWidth, infoheight, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); // info
			DrawSprite("commonmenu", "shop_arrows_upanddown", menuXCoord, (((optionCount + 1) * 0.035f) + infoy), 0.02f, 0.04f, 0, 255, 255, 255, 255); //Info Box
			GRAPHICS::DRAW_RECT(menuXCoord, BannerY, MenuWidth, BannerHeight, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); // Banner
			GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount * 0.035f) / 2) + backgroundy), MenuWidth, (optionCount * backgroundheight), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); // Background
			GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.197f), MenuWidth, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); // Scroller
			DrawSprite("commonmenu", "header_gradient_script", menuXCoord, ((currentOption * 0.035f) + 0.197f), MenuWidth, 0.035f, 90, 255, 255, 255, 255);

			char buffer[30];
			sprintf(buffer, "%i/%i", currentOption, optionCount);
			drawText22(buffer, 4, optioncouuntx, (((optionCount + 1) * 0.035f) + infoy2), 0.60f, 0.60f, 255, 255, 255, 255, true);
			drawTextPage("Version 1.0", 7, ((optionCount + 1) * 0.035f + 0.1787f), 0.47f, 0.47f);
			GRAPHICS::DRAW_RECT(menuXCoord - line1x, (((optionCount * 0.035f) / 2) + liney), .002, (optionCount * lineheight), bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
			GRAPHICS::DRAW_RECT(menuXCoord + line2x, (((optionCount * 0.035f) / 2) + liney), .002, (optionCount * lineheight), bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
		}
		if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
		{
			if (optionCount > maxOptions)
			{
				drawText22(infoText, optionsFont, menuXCoord, ((maxOptions + 1) * 0.035f + infoboxytext), 0.4f, 0.4f, 255, 255, 255, bannerTextOpacity, true);
				GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions + 1) * 0.035f) + infoboxyline), MenuWidth, .003, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box line
				GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions + 1) * 0.035f) + infoboxy), MenuWidth, 0.035f, 0, 0, 0, 180); //Info Box
			}
			else
			{
				drawText22(infoText, optionsFont, menuXCoord, ((optionCount + 1) * 0.035f + infoboxytext), 0.4f, 0.4f, 255, 255, 255, bannerTextOpacity, true);
				GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount + 1) * 0.035f) + infoboxyline), MenuWidth, .003, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box line
				GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount + 1) * 0.035f) + infoboxy), MenuWidth, infoboxheight, 0, 0, 0, 180); //Info Bo
			}
		}
	}
}
void resetVars()
{
	if (submenu != Closed)
		normalMenuActions();
	optionPress = false;
	rightPress = false;
	leftPress = false;
	fastRightPress = false;
	fastLeftPress = false;
	squarePress = false;
	infoText = NULL;
	instructionsSetupThisFrame = false;
	squareInstruction = false;
	xInstruction = false;
	lrInstruction = false;
	if (submenu == Closed)
	{
		GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&gGlareHandle);
	}
}
#pragma endregion

#pragma region Other Loop
void otherLoop()
{
	if (keyboardActive)
	{
		if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 1)
		{
			keyboardActive = false;
			switch (keyboardAction)
			{
			case 0:
				*keyboardVar = StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				break;
			}
		}
		else if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 3)
		{
			keyboardActive = false;
		}
	}
	if (SettingsBoolSub[0])
	{
		static int MenuColor[] = { 255, 0, 0 };
		static int MenuColourStage = 0;
		if (MenuColourStage == 0)
		{
			MenuColor[2]++;
			if (MenuColor[2] == 255)
				MenuColourStage = 1;
		}
		else if (MenuColourStage == 1)
		{
			MenuColor[0]--;
			if (MenuColor[0] == 0)
				MenuColourStage = 2;
		}
		else if (MenuColourStage == 2)
		{
			MenuColor[1]++;
			if (MenuColor[1] == 255)
				MenuColourStage = 3;
		}
		else if (MenuColourStage == 3)
		{
			MenuColor[2]--;
			if (MenuColor[2] == 0)
				MenuColourStage = 4;
		}
		else if (MenuColourStage == 4)
		{
			MenuColor[0]++;
			if (MenuColor[0] == 255)
				MenuColourStage = 5;
		}
		else if (MenuColourStage == 5)
		{
			MenuColor[1]--;
			if (MenuColor[1] == 0)
				MenuColourStage = 0;
		}
		bannerRectRed = MenuColor[0];
		bannerRectGreen = MenuColor[1];
		bannerRectBlue = MenuColor[2];
	}
}
void SelfOptionsLoop()
{
	if (SelfOptionsBool[0])
	{
		PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), true);
		SelfOptionsBool[0] = true;
	}
	else
	{
		PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
		SelfOptionsBool[0] = false;
	}

	if (SelfOptionsBool[1])
	{
		if (CONTROLS::IS_CONTROL_PRESSED(2, BUTTON_X))
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), true, 0.0f, 0.5f, 0.0, 0.0f, 0.0f, 0.0f, true, true, true, true, false, true);
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
		}
	}
	if (SelfOptionsBool[2])
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
		SelfOptionsBool[2] = true;
	}
	else
	{
		SelfOptionsBool[2] = false;
	}
	if (SelfOptionsBool[3])
	{
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER::PLAYER_ID());
	}
	if (SelfOptionsBool[4])
	{
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, true);
	}
	else
	{
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, false);
	}
}
void NetworkOptionsLoop()
{

}
void VehicleOptionsLoop()
{

}
#pragma endregion

int draw_menu()
{
	monitorButtons();
	SelfOptionsLoop();
	NetworkOptionsLoop();
	otherLoop();
	VehicleOptionsLoop();
	optionCount = 0;
	switch (submenu)
	{
#pragma region Main Menu
	case Main_Menu:
		subTitle("Menu Base");
		addSubmenuOption("Network Options", NetworkOptions);
		addSubmenuOption("Self Options", Self_Options);
		addSubmenuOption("Vehicle Options", Self_Options);
		addSubmenuOption("Ped Options", Self_Options, "add ped info");
		addSubmenuOption("Object Options", Self_Options, "add object info");
		addSubmenuOption("Weapon Options", Self_Options);
		addSubmenuOption("Object Options", Self_Options);
		addSubmenuOption("Teleport Options", Self_Options, "add teleport info");
		addSubmenuOption("World Options", Self_Options);
		addSubmenuOption("Settings", Settings);
		break;

	case Settings:
		subTitle("Settings");
		addSubmenuOption("Rainbow Mode", RainbowModeSub);
		addChar("Banner", BannerChar, &BannerInt, 0, 8);
		addChar("Scroller", ScrollerChar, &ScrollerInt, 0, 8);
		addChar("Background", backgroundChar, &backgroundInt, 0, 8);
		addBoolOption("Sounds", menuSounds, "Menu Sounds, Navigation etc..");
		switch (getOption())
		{
		case 2: BannerColorOption(); break;
		case 3: ScrollerColorOption(); break;
		case 4: backgroundColorOption(); break;
		case 5: menuSounds = !menuSounds; break;
		}
		break;

	case RainbowModeSub:
		subTitle("Raubviw Mode");
		addBoolOption("Activate", SettingsBoolSub[0]);
		addIntOption("~r~Red", &bannerRectRed, 0, 255, true);
		addIntOption("~g~Green", &bannerRectGreen, 0, 255, true);
		addIntOption("~b~Blue", &bannerRectBlue, 0, 255, true);

		switch (getOption())
		{
		case 1: SettingsBoolSub[0] = !SettingsBoolSub[0]; break;
		}
		break;
#pragma endregion

#pragma region Players List
	case Players_List:
		subTitle("Network Players");
		for (int i = 0; i < 16; i++)
		{
			addOption(PLAYER::GET_PLAYER_NAME(i));
		}
		if (optionPress && PLAYER::IS_PLAYER_PLAYING(currentOption - 1))
		{
			selectedPlayer = currentOption - 1;
			changeSubmenu(Player_Options);
		}
		if (currentOption == optionCount)
		{
			PlayerInfoMenuBase(true);
		}
		else
		{
			PlayerInfoMenuBase(false);
		}
		break;

#pragma region Network Options
	case NetworkOptions:
		subTitle("NETWORK OPTIONS");
		addSubmenuOption("Network Clients", Players_List);
		addSubmenuOption("All Clients", AllClients);
		break;
#pragma endregion

#pragma region Network Options
	case Player_Options:
		PlayerInfoMenuBase(true);
		subTitle("NETWORK OPTIONS");
		addSubmenuOption("Nice Options", Self_Options);
		addSubmenuOption("Naughty Options", Self_Options);
		addSubmenuOption("Message Options", Self_Options);
		addSubmenuOption("Vehicle Options", Self_Options);
		addSubmenuOption("Teleport Options", Self_Options);
		addSubmenuOption("Animation Options", Self_Options);
		switch (getOption())
		{
		}
		break;
#pragma endregion
#pragma endregion

#pragma region Self Options
	case Self_Options:
		subTitle("Self Options");
		addBoolOption("God Mode", SelfOptionsBool[0], "Makes You Invinsible");
		addBoolOption("Invisibility", !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID()));
		addBoolOption("Super Run", SelfOptionsBool[1], "Press X");
		addBoolOption("Super Jump", SelfOptionsBool[2]);
		addBoolOption("Super Punch", SelfOptionsBool[3]);
		addBoolOption("Shrink", SelfOptionsBool[4], "Makes Your Character Smaller (Only Visible To You)");

		switch (getOption())
		{
		case 1: SelfOptionsBool[0] = !SelfOptionsBool[0]; break;
		case 2: ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID())); break;
		case 3: SelfOptionsBool[1] = !SelfOptionsBool[1]; break;
		case 4: SelfOptionsBool[2] = !SelfOptionsBool[2]; break;
		case 5: SelfOptionsBool[3] = !SelfOptionsBool[3]; break;
		case 6: SelfOptionsBool[4] = !SelfOptionsBool[4]; break;
		}
		break;
#pragma endregion
	}
	resetVars();
	return true;
}

int is_player_online_hook()
{
	if (!strncmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "freemode", strlen("freemode")) || !strncmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud", strlen("ingamehud")))
	{
		draw_menu();
	}
	return true;
}