/*
 *   This file is part of open_agb_firm
 *   Copyright (C) 2024 profi200
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include "types.h"
#include "arm11/oaf_osd.h"
#include "arm11/fmt.h"
#include "arm11/console.h"
#include "arm11/drivers/mcu.h"
#include "drivers/gfx.h"
#include "drivers/cache.h"
#include "drivers/lgy_common.h"


static char s_gameTitle[13];
static char s_gameCode[5];
static u32 s_romSize;


// Flush only the bottom screen framebuffer.
// GFX_flushBuffers() flushes both screens and races with gbaGfxHandler on the top screen.
static void flushBotScreen(void)
{
	const u32 size = LCD_WIDTH_BOT * LCD_HEIGHT_BOT * 2; // BGR565 = 2 bytes per pixel.
	flushDCacheRange(GFX_getBuffer(GFX_LCD_BOT, GFX_SIDE_LEFT), size);
}

void OAF_osdInit(const u32 romSize)
{
	const char *const romHeader = (const char*)LGY_ROM_LOC;

	memcpy(s_gameTitle, &romHeader[0xA0], 12);
	s_gameTitle[12] = '\0';

	memcpy(s_gameCode, &romHeader[0xAC], 4);
	s_gameCode[4] = '\0';

	s_romSize = romSize;

	consoleClear();
	ee_printf("Game: %.12s [%.4s]\n", s_gameTitle, s_gameCode);
	ee_printf("ROM:  %u KiB\n", s_romSize / 1024);
	flushBotScreen();
}

void OAF_osdUpdate(void)
{
	RtcTimeDate td;
	MCU_getRtcTimeDate(&td);

	const u8 battery = MCU_getBatteryLevel();

	ee_printf("\x1b[0;0H");
	ee_printf("==open_agb_firm OSD==\n\n");
	ee_printf("Game: %.12s [%.4s]\n", s_gameTitle, s_gameCode);
	ee_printf("ROM:  %u KiB\n\n", s_romSize / 1024);
	ee_printf("Time: 20%02X-%02X-%02X %02X:%02X:%02X\n", td.year, td.mon, td.day, td.hour, td.min, td.sec);
	ee_printf("Battery: %u%%\n", battery);

	flushBotScreen();
}
