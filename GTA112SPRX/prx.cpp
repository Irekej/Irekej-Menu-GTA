#include "stdafx.h"

//ANY OTHER HARDCODED ADDRESSES ARE ON 1.12 BLES
int G_NATIVES;
int GLOBALS_PTR;
int TOC;
int MAIN_HOOK_ADDRESS;

//#include <libpsutil.h> https://github.com/skiff/libpsutil requires sdk 4.75
#include <cellstatus.h>
#include <sys/prx.h>
#include <ppu_asm_intrinsics.h> 
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <string.h> 
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/process.h>
#include <ppu_intrinsics.h>
#include <stdarg.h>
#include <cell/cell_fs.h>
#include <stdio.h>
#include <sysutil\sysutil_msgdialog.h>
#include <sysutil\sysutil_oskdialog.h>
#include <sysutil\sysutil_oskdialog_ext.h>

#include <cell/pad.h>
#include <cell/padfilter.h> 

#include <cstdlib>
#include <math.h>


void debug_write(char *str);

#include "types.h"
#include "utils.h"
#include "GTAStructs.h"
#include "Natives.h"
#include "gtaCode.h"
#include "menu.h"

void main_hook(int r3) {
	*(int*)(*(int*)(r3)+0x0) = 1;//set IS_PLAYER_ONLINE to true
	draw_menu();
}

sys_ppu_thread_t ThreadModuleID;
uint64_t main_hook_original_opd;
void init(uint64_t threadinfo) {
	char *str = "SPRX started!\n";
	createFile("/dev_hdd0/tmp/debugfile.txt");
	writeToFile("/dev_hdd0/tmp/debugfile.txt",str,strlen(str));

	debug_append("Loading... if you do not see success after this line, then the sprx has crashed...\n");

	//for disabling the business update so jobs work
	PatchInJump(findEdatPatchPointer(), (int)testHookEdat, true);

	//patchStatsHooking();//this is outdated because it didn't work well for some reason so I gave up and used the code below instead because it's much simpler

	//UNCOMMENT THIS TO KEEP STATS LOADED! MAKE SURE TO HAVE THE 3 XML FILES IN THE PS3_DEBUG FOLDER IN YOUR PS3'S TMP FOLDER. CURRENTLY THIS WILL CAUSE ISSUES IF YOU SAVE YOUR GAME AND RELOAD IT, BUT THIS WILL ALLOW YOU TO EXIT TO SP AND GO BACK TO MP. WE NEED TO FIND OUT WHAT STUFF TO PATCH IN THE SCRIPT FILES TO MAKE THIS WORK AFTER A WHOLE GAME RELOAD! LOOK AT THE GLOBAL RESEARCH DONE IN GTACODE.H
	//strcpy((char*)findDefaultXMLPointer()/*0x174C4B4*/,"/dev_hdd0/tmp/default");//"commoncrc:/data/default"  easier just to tell it to load the file from tmp


	//wait for natives table to be initialized
	sleep(30000);

	//find values
	G_NATIVES = findNativesPointer();// 1.12 BLES 0x1DA7BB0
	GLOBALS_PTR = findGlobalsPointer();// 1.12 BLES 0x1DA7FF0;
	MAIN_HOOK_ADDRESS = getOPDOfNative(0x6E5BDCE2); // NETWORK_IS_SIGNED_ONLINE opd struct 1.12 BLES 0x1B68080
	TOC = *(int*)(MAIN_HOOK_ADDRESS+0x4);

	//create main hook
	main_hook_original_opd = *(uint64_t*)MAIN_HOOK_ADDRESS;
	*(uint64_t*)MAIN_HOOK_ADDRESS = *(uint64_t*)((int)main_hook);

	//create other things
	setup_textmessage_fix();
	setup_stats_fix();


	//debug info if setup was successful
	debug_append("Success!\n");

	sys_ppu_thread_exit(threadinfo);
}

void deinit() {
	//undo main hook
	*(uint64_t*)MAIN_HOOK_ADDRESS = main_hook_original_opd;
}

// Important PRX info
SYS_MODULE_INFO( GTA112SPRX, 0, 1, 1);
SYS_MODULE_START( _GTA112SPRX_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _GTA112SPRX_export_function, LIBNAME );

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _GTA112SPRX_export_function(void)
{
	deinit();
    return CELL_OK;
}

extern "C" int _GTA112SPRX_prx_entry(void)
{
	sys_ppu_thread_create(&ThreadModuleID, init, 0, 0x5AA, 4096*5, 0, "gopro_2027's Mod Menu");
			
    return SYS_PRX_RESIDENT;
}
