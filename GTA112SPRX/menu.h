//#include <libpsutil.h> https://github.com/skiff/libpsutil requires sdk 4.75
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/memory.h>
#include <sys/process.h>
#include <sys/ppu_thread.h>
#include <stdint.h>
#include <string.h>
#include <sys/timer.h>

#include "mods.h"
#include "utils2.h"

#pragma region Variables
int submenu = 0;
int submenuLevel;
int lastSubmenu[20];
int lastOption[20];
int currentOption;
int optionCount;
bool optionPress = false;
bool rightPress = false;
bool leftPress = false;
bool fastRightPress = false;
bool fastLeftPress = false;
bool squarePress = false;
int selectedPlayer;
bool menuSounds = true;
bool keyboardActive = false;
int keyboardAction;
int* keyboardVar = 0;
char* infoText;

//BOOLS
bool loop40K_;
bool NoCops = false;
bool Shrink = false;
int wantedlevel = 0;
bool SuperJump = false;
bool SuperSpeed = false;
bool SuperRun = false;
bool slowmotion = false;
int spawnedped;
int SpawnedVeh;
uint32_t hash_veh;
bool SpawnVehicle;
bool PedSpawnVehicle;
bool SlingShot;
bool lel = false;
bool carinvstext;
bool TeleportToMe = false;
int TeleportVehicle = 0;
bool spawnsetswat;
bool frezzeplayer;
bool toogleesp_;
bool looprainbow_;
bool _lower;
bool SlingShot2;
bool hasNoCollision;
bool r3boost;
bool l3break;
bool l2bboost;
bool leftfix;

bool newTimerTick = true;
int maxTimerCount;
bool newTimerTick2 = true;
int maxTimerCount2;

bool instructions = true;
int instructCount;
int mov;
bool instructionsSetupThisFrame;
bool xInstruction;
bool squareInstruction;
bool lrInstruction;

int bannerTextRed = 255;
int bannerTextGreen = 255;
int bannerTextBlue = 255;
int bannerTextOpacity = 255;
int bannerTextFont = 1;
int bannerRectRed = 0;
int bannerRectGreen = 255;
int bannerRectBlue = 255;
int bannerRectOpacity = 255;
int backgroundRed = 16;
int backgroundGreen = 16;
int backgroundBlue = 16;
int backgroundOpacity = 70;
int optionsRed = 255;
int optionsGreen = 255;
int optionsBlue = 255;
int optionsOpacity = 255;
int optionsFont = 0;
int scrollerRed = 255;
int scrollerGreen = 255;
int scrollerBlue = 255;
int scrollerOpacity = 50;
int indicatorRed = 255;
int indicatorGreen = 255;
int indicatorBlue = 255;
int indicatorOpacity = 255;
int subr = 0;
int subb = 0;
int subg = 0;
int suba = 20;
float menuXCoord = 0.845f;
float textXCoord = 0.76f;
float Cunt = 0.080;
float Cunt2 = 0.225;
float Checkbox = 0.225;
float ScrollX = 0.0525f;
float titlebox3 = 0.928f;
int maxOptions = 18;
bool SelfOptionsBool[50];
#pragma endregion

#pragma region Internals

int sceKernelWrite(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	return_to_user_prog(int);
}

int32_t sceKernelHenWrite(void* destination, const void* source, size_t size)
{
	system_call_6(8, 30583, 50, (uint64_t)sys_process_getpid(), (uint64_t)destination, (uint64_t)source, (uint64_t)size);
	return_to_user_prog(int32_t);
}

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
void drawText(char* text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(x, y);
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
void addTitle(char* title)
{
	drawText(title, bannerTextFont, menuXCoord, 0.1f, 0.75f, 0.75f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
	GRAPHICS::DRAW_RECT(menuXCoord, 0.1175f, 0.19f, 0.083f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity);
}
void addSubTitle(char* texting)
{
	drawText(texting, 6, Cunt, 0.125, 0.40, 0.40f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
	GRAPHICS::DRAW_RECT(menuXCoord, 0.1410f, 0.190f, 0.034f, subr, subg, subb, suba);
}
void DrawSprite1(char* Streamedtexture, char* textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
	if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture));
	GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, r, g, b, a);
}
#pragma region Option Helpers
void addOption(char* option, char* info = NULL)
{
	optionCount++;
	if (currentOption == optionCount)
		infoText = info;
	if (currentOption <= maxOptions && optionCount <= maxOptions)
		drawText(option, optionsFont, textXCoord, (optionCount * 0.035f + 0.125f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		drawText(option, optionsFont, textXCoord, ((optionCount - (currentOption - maxOptions)) * 0.035f + 0.125f), 0.4f, 0.4f, optionsRed, optionsGreen, optionsBlue, optionsOpacity, false);
}
void addSubmenuOption(char* option, int newSubmenu, char* info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount)
	{
		xInstruction = true;
		if (optionPress)
			changeSubmenu(newSubmenu);
	}
}
void addBoolOption(char* option, bool b00l, char* info = NULL)
{
	char buf[30];
	if (b00l)
	{
		snprintf(buf, sizeof(buf), "%s: On", option);
		addOption(buf, info);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s: Off", option);
		addOption(buf, info);
	}
}
void addCheckBool(char* option, bool b00l1, char* info = NULL)
{
	char buf[30];
	if (b00l1)
	{
		snprintf(buf, sizeof(buf), "%s", option);
		DrawSprite1("commonmenu", "shop_box_tick", Checkbox, (optionCount * 0.035f + 0.175f), 0.03, 0.04, 0, 255, 255, 255, 255);
		addOption(buf, info);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", option);
		DrawSprite1("commonmenu", "shop_box_blank", Checkbox, (optionCount * 0.035f + 0.175f), 0.03, 0.04, 0, 255, 255, 255, 255);
		addOption(buf, info);

	}
}
template<typename TYPE>
void addCustomBoolOption(char* option, TYPE value, TYPE match, char* info = NULL)
{
	char buf[30];
	if (value == match)
	{
		snprintf(buf, sizeof(buf), "%s: On", option);
		addOption(buf, info);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s: Off", option);
		addOption(buf, info);
	}
}
void addIntOption(char* option, int* var, int min, int max, bool keyboard, char* info = NULL)
{
	char buf[30];
	snprintf(buf, sizeof(buf), "%s: < %i >", option, *var);
	addOption(buf, info);
	if (currentOption == optionCount)
	{
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
	snprintf(buf, sizeof(buf), "%s: < %s >", option, FtoS(*var));
	addOption(buf, info);
	if (currentOption == optionCount)
	{
		lrInstruction = true;
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
#pragma endregion
int getOption()
{
	xInstruction = true;
	if (optionPress)
		return currentOption;
	else return 0;
}
void monitorButtons()
{
	SetupTimer(20);
	if (submenu == Closed)
	{
		if (IsTimerReady())
		{
			if (CONTROLS::IS_CONTROL_PRESSED(0, BUTTON_L1) && CONTROLS::IS_CONTROL_PRESSED(0, BUTTON_R1))
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
				else {
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
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, DPAD_RIGHT))
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
			else if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, BUTTON_X))
			{
				squarePress = true;
			}
			ResetTimer();
		}
	}
}
void normalMenuActions()
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
	if (optionCount > maxOptions)
	{
		GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions * 0.035f) / 2) + 0.159f), 0.19f, (maxOptions * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		if (currentOption > maxOptions)
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.1415f), 0.19f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
			GRAPHICS::DRAW_RECT(menuXCoord, 0.156f, 0.19f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Up Indicator
		}
		else
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.1415f), 0.19f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
		}
		if (currentOption != optionCount)
		{
			GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.161f), 0.19f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Down Indicator
		}
	}
	else
	{
		GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount * 0.035f) / 2) + 0.159f), 0.19f, (optionCount * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.1415f), 0.19f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
	}
	if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(infoText))
	{
		if (optionCount > maxOptions)
		{
			drawText(infoText, optionsFont, menuXCoord, ((maxOptions + 1) * 0.035f + 0.125f), 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions + 1) * 0.035f) + 0.1415f), 0.19f, 0.035f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box
		}
		else
		{
			drawText(infoText, optionsFont, menuXCoord, ((optionCount + 1) * 0.035f + 0.125f), 0.4f, 0.4f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity, true);
			GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount + 1) * 0.035f) + 0.1415f), 0.19f, 0.035f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box
		}
	}
	SetupTimer2(20);
	if (instructions)
	{
		if (IsTimerReady2())
		{
			if (squareInstruction)
				addInstruction(BUTTON_X, "Keyboard");
			instructionsClose();
			ResetTimer2();
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
			case 0: //addIntOption
				*keyboardVar = StoI(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
				break;
			}
		}
		else if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 2 || GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 3)
		{
			keyboardActive = false;
		}
	}
	if (NoCops) { PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()); }
	if (SuperJump) { GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID()); }
	if (Shrink) { PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, true); }
	if (l2bboost) {
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, BUTTON_L2)) VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), -100);
	}
	if (r3boost) { if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, BUTTON_R2)) VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 100); }
	if (l3break) { if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, BUTTON_X)) VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0); }
	if (leftfix) { if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, DPAD_LEFT)) VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())); }
}
#pragma endregion

namespace Mods
{
	void slingshot()
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true));
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true)));
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
		}
	}
	void DeleteVehicle(int VehicleHandle)
	{

	}
};

void addPlayerVeh(char* option, char* model, char* notifcation, char* info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount && optionPress)
	{
		//CREATE_VEHL(model);
		hash_veh = GAMEPLAY::GET_HASH_KEY(model);
		PedSpawnVehicle = true;
		spawnVehicleOnMe(model);
		drawNotification(notifcation);
	}
}

void addVehOption(char* option, char* model, char* notifcation, char* info = NULL)
{
	addOption(option, info);
	if (currentOption == optionCount && optionPress)
	{
		//CREATE_VEHL(model);
		hash_veh = GAMEPLAY::GET_HASH_KEY(model);
		SpawnVehicle = true;
		drawNotification(notifcation);
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

int draw_menu()
{
	UI::DISPLAY_RADAR(true);
	monitorButtons();
	otherLoop();
	optionCount = 0;
	switch (submenu)
	{
#pragma region Main Menu
	case Main_Menu:
		addTitle("Irekej's Menu");
		addSubTitle("Main Menu");
		addSubmenuOption("Players Options", Players_List, "Players in the session");
		addSubmenuOption("Online Options", Online_Options, "Options for character");
		addSubmenuOption("Self Options", Self_Options, "Your private options");
		addSubmenuOption("Community Mods", funnyshit, "Other Stuff");
		addSubmenuOption("Spawn Vehicle", spawnv, "Vehicle spawner");
		addSubmenuOption("Vehicle Options", editcunt, "Tuning your vehicle");
		addSubmenuOption("Settings", Settings, "Customize the menu");
		break;
#pragma endregion
#pragma region Online Options
	case Online_Options:
		addTitle("Irekej's Menu");
		addSubTitle("Online Options");
		addOption("Give 5 MLN", " ");
		addOption("Give 300 LVL", " ");
		switch (getOption())
		{
		case 1: NETWORKCASH::NETWORK_EARN_FROM_ROCKSTAR(5000000); break;
		case 2: 
			int hash = GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM");
			int prev = 0;
			STATS::STAT_GET_INT(hash, &prev, 1);
			STATS::STAT_SET_INT(hash, prev + 10000000, 1); break;
		}
		break;
#pragma endregion
#pragma region Players List
	case Players_List:
		addTitle("Irekej's Menu");
		addSubTitle("Players List");
		for (int i = 0; i < 18; i++)
		{
			addOption(PLAYER::GET_PLAYER_NAME(i));
		}
		if (optionPress && PLAYER::IS_PLAYER_PLAYING(currentOption - 1))
		{
			selectedPlayer = currentOption - 1;
			changeSubmenu(Player_Options);
		}
		break;
#pragma endregion
#pragma region Player Options
	case Player_Options:
		addTitle("Irekej's Menu");
		addSubTitle(PLAYER::GET_PLAYER_NAME(selectedPlayer));
		addSubmenuOption("Trolling", trolling, " ");
		addSubmenuOption("Vehicle", pvehcile, " ");
		addSubmenuOption("Attachments", pattch, " ");
		addSubmenuOption("Weapons", pweapons, " ");
		addSubmenuOption("Drops", pdrops, " ");
		addSubmenuOption("Spawn Vehicle", psvehicle, " ");
		addOption("Teleport To Player", " ");
		switch (getOption())
		{
		case 7: TeleportToClient(selectedPlayer); break;
		}
		break;
	case trolling:
		addTitle("Irekej's Menu");
		addSubTitle("Trolling Options");
		addOption("Clone", " ");//done
		addOption("Attach to Player", " ");//done
		addOption("Explode", " ");//done
		addOption("SWAT Player", " ");//not working
		addCheckBool("Freeze Player", frezzeplayer, " ");//not working
		addOption("Kick Player", " ");//done
		addOption("Clear Tasks", " ");//done
		addCheckBool("Draw Arrow On Player", toogleesp_, " ");//not working
		switch (getOption())
		{
		case 1: ClonePed(PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		case 2: AttachToPlayer(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED(selectedPlayer)); break;
		case 3: Vector3 Pos1 = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true); FIRE::ADD_EXPLOSION(Pos1.x, Pos1.y, Pos1.z, 29, 0.5f, true, false, 5.0f); break;
		case 4: break;
		case 5: break;
		case 6: NETWORK::NETWORK_SESSION_KICK_PLAYER(selectedPlayer); break;
		case 7: stopTasks(selectedPlayer); break;
		case 8: break;
		}
		break;
	case pvehcile:
		Vehicle VehicleHandle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
		addTitle("Irekej's Menu");
		addSubTitle("Vehicle Options");
		addOption("Teleport Car To Me", " ");
		addOption("Max Upgrade", " ");//done
		addOption("Fix Vehicle", " ");//done
		addOption("Delete Vehicle", " ");//done
		addOption("Stop Car", " ");//done
		addOption("Flip Vehicle Upright", " ");//done
		addOption("Paint Random", " ");//done
		addOption("Car Jump", " ");//done
		addOption("Kick Out Of Vehicle", " ");//done
		addCheckBool("Undriveable Car", doUndriveableCar, " ");//done
		switch (getOption())
		{
		case 1: if (PED::IS_PED_IN_ANY_VEHICLE(selectedPlayer, true))
		{
			TeleportToMe = true;
		}
			  else
			drawNotification("~w~Player is not in a vehicle."); break;
		case 2: NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehicleHandle);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehicleHandle))
			{
				MaxUpgrades(selectedPlayer);
			}
			break;
		case 3: NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehicleHandle);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehicleHandle))
			{
				VEHICLE::SET_VEHICLE_FIXED(VehicleHandle);
			}
			break;
		case 4: if (ENTITY::DOES_ENTITY_EXIST(VehicleHandle))
		{
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(VehicleHandle, 1, 1);
			VEHICLE::DELETE_VEHICLE(&VehicleHandle);
		} break;
		case 5: NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehicleHandle);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehicleHandle))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true), -0);
			}
			break;
		case 6: NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehicleHandle);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehicleHandle))
			{
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true));
			}
			break;
		case 7: NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehicleHandle);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehicleHandle))
			{
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehicleHandle, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehicleHandle, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
			}
			break;
		case 8: Mods::slingshot(); break;
		case 9: KickFromCar(selectedPlayer); break;
		case 10: undriveablePlayersCar(selectedPlayer); break;
		}
		break;
	case pattch:
		addTitle("Irekej's Menu");
		addSubTitle("Attachments");
		addOption("");
		switch (getOption())
		{

		}
		break;
	case pweapons:
		addTitle("Irekej's Menu");
		addSubTitle("Weapon Options");
		addOption("Take all Weapons", " ");
		switch (getOption())
		{
		case 1: TakeWeaponsClient(selectedPlayer); break;
		}
		break;
	case pdrops:
		addTitle("Irekej's Menu");
		addSubTitle("Drop Options");
		addCheckBool("Money Drop", loop40K_, " ");
		switch (getOption())
		{
		case 1: loop40K_ = !loop40K_; break;
		}
		break;
	case psvehicle:
		addTitle("Irekej's Menu");
		addSubTitle("Spawn Vehicle");
		addPlayerVeh("Adder", "adder", "Adder Spawned", "1");//weird
		switch (getOption())
		{

		}
		break;
#pragma endregion
#pragma region Self Options
	case Self_Options:
		addTitle("Irekej's Menu");
		addSubTitle("Self Options");
		addCheckBool("Godmode", PLAYER::GET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID()));
		addCheckBool("Never Wanted", NoCops, " ");;//done
		addCheckBool("Reveal Players", revealPeople, " ");
		addOption("Change Model", " ");//submenu
		addOption("Animations", " ");//submenu
		addOption("Scenarios", " ");//submenu
		addCheckBool("Invisible", !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID()), " ");//done
		addOption("Change Name", " ");//done
		addCheckBool("Super Jump", SuperJump, " ");//done
		addCheckBool("Super Run", Speed, " ");
		addCheckBool("Super Punch", slowmotion, " ");//done
		addOption("Clone Player", " ");//done
		addCheckBool("Shrink", Shrink, " ");
		addOption("Explode", " ");//done
		addCheckBool("Mobile Radio", Radioing, " ");//done
		switch (getOption())
		{
		case 1: PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), !PLAYER::GET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID())); break;
		case 2: NoCops = !NoCops; break;
		case 3: RevealPlayers();
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !ENTITY::IS_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID())); break;
		case 8: startKeyboard(9, "Change Name", 15); GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "PM_NAME_CHALL", "", "", "", "", "", 40); keyboardActive = true; break;
		case 9: SuperJump = !SuperJump; break;
		case 10: playerMovementSpeed(); break;
		case 11: slowmotion = !slowmotion; break;
		case 12: ClonePed(PLAYER::PLAYER_PED_ID()); break;
		case 13: Shrink = !Shrink; break; //break;
		case 14: Vector3 Pos1 = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_PED_ID()), true); FIRE::ADD_EXPLOSION(Pos1.x, Pos1.y, Pos1.z, 29, 0.5f, true, false, 5.0f); break;
		case 15: Radio(); break;
		}
		break;
	case ANIMATIONS:
		addTitle("Irekej's Menu");
		addSubTitle("Animations");
		addOption("Nothing", " ");
		switch (getOption())
		{
		case 1: break;
		}
		break;
#pragma endregion
#pragma region Fun Shit
	case funnyshit:
		addTitle("Irekej's Menu");
		addSubTitle("Community Mods");
		addCheckBool("First Person", fPerson, " ");
		switch (getOption())
		{
		case 1: FirstPerson(); break;
		}
		break;
#pragma endregion
#pragma region Edit Carz
	case editcunt:
		addTitle("Irekej's Menu");
		addSubTitle("Edit Vehicle");
		addCheckBool("Godmode", invinciblecar, " ");
		addCheckBool("Invisibility", carinvstext, " ");
		addOption("Max Upgrade", " ");
		addOption("Fix Vehicle", " ");
		addOption("Paint Random", " ");
		addCheckBool("Rainbow Car", looprainbow_, " ");
		addOption("Flip Vehicle", " ");
		addOption("Open/Close Doors", " ");
		addCheckBool("Lower Vehicle", _lower, " ");
		addOption("Jump Car", " ");
		addSubmenuOption("Vehicle Binds", vebindsm, " ");
		addCheckBool("No Collision", hasNoCollision, " ");
		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		switch (getOption())
		{
		case 1: invinciblecar = !invinciblecar; break;
		case 2: carinvstext = !carinvstext; vinval_ = !vinval_; NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehID);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehID)) {
				ENTITY::SET_ENTITY_VISIBLE(VehID, vinval_);
			}
			break;
		case 3: NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehID);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehID))
			{
				MaxUpgradesMe(VehID, true);
			}
			break;
		case 4: NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehID);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehID)) {
				VEHICLE::SET_VEHICLE_FIXED(VehID);
			}
			break;
		case 5: PaintVehRan(); break;
		case 6: looprainbow_ = !looprainbow_; break;
		case 7: NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehID);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehID)) {
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true));
			}
			break;
		case 8: NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(VehID);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(VehID))
			{
				OpenDoors(VehID);
			}
			break;
		case 9: _lower = !_lower; break;
		case 10: SlingShot2 = !SlingShot2; break;
		case 11: break;
		case 12: if (hasNoCollision)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			ENTITY::SET_ENTITY_COLLISION1(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
			hasNoCollision = false;
		}
			   else
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			ENTITY::SET_ENTITY_COLLISION1(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false);
			hasNoCollision = true;
		}
			   break;
		}
		break;
#pragma endregion
#pragma region Settings
	case Settings:
		addTitle("Irekej's Menu");
		addSubTitle("Settings");
		addSubmenuOption("Banners", Settings_Banners);
		addSubmenuOption("Body", Settings_Body);
		addSubmenuOption("Scroller", Settings_Scroller);
		addSubmenuOption("Indicators", Settings_Indicators);
		addBoolOption("Sounds", menuSounds);
		addBoolOption("Instructions", instructions);
		addCustomBoolOption("Right Sided", menuXCoord, 0.145f);
		addIntOption("Max Options", &maxOptions, 1, 20, false);
		switch (getOption())
		{
		case 5: menuSounds = !menuSounds; break;
		case 6: instructions = !instructions; break;
		case 7:
			if (menuXCoord == 0.145f)
			{
				menuXCoord = 0.845f;
				textXCoord = 0.76f;
			}
			else
			{
				menuXCoord = 0.145f;
				textXCoord = 0.06f;
			}
			break;
		}
		break;
	case Settings_Banners:
		addTitle("Irekej's Menu");
		addSubTitle("Banners");
		addIntOption("Text Red", &bannerTextRed, 0, 255, true);
		addIntOption("Text Green", &bannerTextGreen, 0, 255, true);
		addIntOption("Text Blue", &bannerTextBlue, 0, 255, true);
		addIntOption("Text Opacity", &bannerTextOpacity, 0, 255, true);
		addIntOption("Text Font", &bannerTextFont, 0, 7, false);
		addIntOption("Rect Red", &bannerRectRed, 0, 255, true);
		addIntOption("Rect Green", &bannerRectGreen, 0, 255, true);
		addIntOption("Rect Blue", &bannerRectBlue, 0, 255, true);
		addIntOption("Rect Opacity", &bannerRectOpacity, 0, 255, true);
		break;
	case Settings_Body:
		addTitle("Irekej's Menu");
		addSubTitle("Body");
		addIntOption("Text Red", &optionsRed, 0, 255, true);
		addIntOption("Text Green", &optionsGreen, 0, 255, true);
		addIntOption("Text Blue", &optionsBlue, 0, 255, true);
		addIntOption("Text Opacity", &optionsOpacity, 0, 255, true);
		addIntOption("Text Font", &optionsFont, 0, 7, false);
		addIntOption("Rect Red", &backgroundRed, 0, 255, true);
		addIntOption("Rect Green", &backgroundGreen, 0, 255, true);
		addIntOption("Rect Blue", &backgroundBlue, 0, 255, true);
		addIntOption("Rect Opacity", &backgroundOpacity, 0, 255, true);
		break;
	case Settings_Scroller:
		addTitle("Irekej's Menu");
		addSubTitle("Scroller");
		addIntOption("Red", &scrollerRed, 0, 255, true);
		addIntOption("Green", &scrollerGreen, 0, 255, true);
		addIntOption("Blue", &scrollerBlue, 0, 255, true);
		addIntOption("Opacity", &scrollerOpacity, 0, 255, true);
		break;
	case Settings_Indicators:
		addTitle("Irekej's Menu");
		addSubTitle("Indicators");
		addIntOption("Red", &indicatorRed, 0, 255, true);
		addIntOption("Green", &indicatorGreen, 0, 255, true);
		addIntOption("Blue", &indicatorBlue, 0, 255, true);
		addIntOption("Opacity", &indicatorOpacity, 0, 255, true);
		break;
#pragma endregion
#pragma region Vehicle Binds
	case vebindsm:
		addTitle("Irekej's Menu");
		addSubTitle("Vehicle Binds");
		addCheckBool("Boost(RR)", r3boost);
		addCheckBool("Back Boost(L2)", l2bboost);
		addCheckBool("Insta Stop (L3)", l3break);
		addCheckBool("Fix (D-Left)", leftfix);
		addCheckBool("Drift (R1)", drift);
		switch (getOption())
		{
		case 1: r3boost = !r3boost; break;
		case 2: l2bboost = !l2bboost; break;
		case 3: l3break = !l3break; break;
		case 4: leftfix = !leftfix; break;
		case 5: drift = !drift; break;
		}
		break;
#pragma endregion
#pragma region Spawn Vehicle
	case spawnv:
		addTitle("Irekej's Menu");
		addSubTitle("Spawn Vehicle");
		addOption("Adder", "adder");
		addOption("Adder", "adder");
		addOption("Adder", "adder");
		switch (getOption())
		{
		case 1: {
			spawnVehicleOnMe("adder");
		}
		case 2: spawnVehicleOnMe("adder");
		case 3: spawnVehicleOnMe("adder"); break;
		}
		break;
	}
#pragma endregion
	resetVars();
	return true;
}