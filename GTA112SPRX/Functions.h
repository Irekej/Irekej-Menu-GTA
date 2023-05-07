#pragma region Variables
Native_s** g_Natives;
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
int bannerTextFont = 7;
int bannerRectRed = 66;//255
int bannerRectGreen = 149;//87
int bannerRectBlue = 244;//77
int bannerRectOpacity = 200;//255
int backgroundRed = 16;
int backgroundGreen = 16;
int backgroundBlue = 16;
int backgroundOpacity = 160;
int optionsRed = 255;
int optionsGreen = 255;
int optionsBlue = 255;
int optionsOpacity = 255;
int optionsFont = 0;
int scrollerRed = 255;
int scrollerGreen = 255;
int scrollerBlue = 255;
int scrollerOpacity = 255;
int indicatorRed = 255;
int indicatorGreen = 255;
int indicatorBlue = 255;
int indicatorOpacity = 255;
int maxOptions = 8;
int mainTextFont = 1;
float teztYCoord = 0.18f;
float SubTitleXCoord = 0.069f;
float OnOff = 0.800f;
float line1x = .234;
float line2x = .234;
float liney = 0.210f;
float lineheight = 0.040f;
float OnOff0404040 = 0.740f;
float menuXCoord = 0.525f;
float MenuWidth = 0.47f;
float textXCoord = 0.30f;
float subtitley = 0.55f;
float BannerY = 0.185f;
float BannerHeight = 0.068f;
float backgroundy = 0.215f;
float backgroundheight = 0.035f;
float infoy = 0.1960f;
float infoy2 = 0.1760f;
float infoheight = 0.035f;
float titley = 0.15f;
float optioncouuntx = 0.305f;
float HeightCheck = 0.40f;
float WidthCheck = 0.40f;
float infoboxy = 0.2415f;
float infoboxyline = 0.2215f;
float infoboxytext = 0.225f;
float infoboxheight = 0.035f;
bool SelfOptionsBool[50];
bool NetworkOptionsMain[20];
bool SettingsBoolSub[10];
#pragma endregion

#pragma region Need Functions Globals etc
#pragma endregion

#pragma region Self Options
// self options here
#pragma endregion

#pragma region Client Options
void SpectatePlayer(Ped playerped)
{
	Any SpectateCam;

	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerped, false);
	SpectateCam = CAM::CREATE_CAM_WITH_PARAMS1("DEFAULT_SCRIPTED_FLY_CAMERA", playerPosition.x, playerPosition.y, playerPosition.z, 0.0, 0.0, 0.0, 50.0, 0, 2);
	CAM::ATTACH_CAM_TO_ENTITY(SpectateCam, playerped, 0, -5, 1, 1);
	CAM::SET_CAM_ACTIVE(playerped, 1);
}
void SpectateMode(bool Active, Ped selectedPed)
{
	NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(Active, selectedPed);
}
#pragma endregion
