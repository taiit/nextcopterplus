//***********************************************************
//* menu_battery.c
//***********************************************************

//***********************************************************
//* Includes
//***********************************************************

#include <avr/pgmspace.h> 
#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include "..\inc\io_cfg.h"
#include "..\inc\init.h"
#include "..\inc\mugui.h"
#include "..\inc\glcd_menu.h"
#include "..\inc\menu_ext.h"
#include "..\inc\glcd_driver.h"
#include "..\inc\main.h"
#include "..\inc\eeprom.h"

//************************************************************
// Prototypes
//************************************************************

// Menu items
void menu_battery(void);

//************************************************************
// Defines
//************************************************************

#define BATTITEMS 5 	// Number of menu items
#define BATTSTART 66 	// Start of Menu text items
#define BATTTEXT 71 	// Start of value text items
#define BATTOFFSET 92	// Value offsets

#define	NIMH_MAX 125	// Alternate default for max cell voltage for NiMh
#define	NIMH_MIN 110	// Alternate default for max cell voltage for NiMh

//************************************************************
// Battery menu items
//************************************************************

const uint8_t BattMenuText[BATTITEMS] PROGMEM = {BATTTEXT, 0, 0, 0, 0};
const menu_range_t batt_menu_ranges[] PROGMEM = 
{
	{0,1,1,1,LIPO}, 	// Min, Max, Increment, Style, Default
	{1,12,1,0,3},
	{0,2000,1,0,108},
	{120,430,1,0,42},
	{80,400,1,0,36}
};

//************************************************************
// Main menu-specific setup
//************************************************************

void menu_battery(void)
{
	uint8_t cursor = LINE0;
	uint8_t top = BATTSTART;
	uint8_t temp = 0;
	int16_t values[BATTITEMS];
	menu_range_t range;
	uint8_t text_link = 0;
	uint8_t temp_cells = 0;
	uint16_t temp_minvoltage = 0;
	
	while(button != BACK)
	{
		// Load values from eeprom
		memcpy(&values[0],&Config.BatteryType,sizeof(int16_t) * BATTITEMS);

		// Save pre-edited values
		temp_cells = Config.BatteryCells;
		temp_minvoltage = Config.MinVoltage;

		// Print menu
		print_menu_items_16(top, BATTSTART, &values[0], (prog_uchar*)batt_menu_ranges, BATTOFFSET, (prog_uchar*)BattMenuText, cursor);

		// Handle menu changes
		update_menu(BATTITEMS, BATTSTART, button, &cursor, &top, &temp);
		range = get_menu_range ((prog_uchar*)batt_menu_ranges, temp - BATTSTART);

		// Modify defaults for NiMh if NiMh selected (really ugly)
		if (Config.BatteryType == NIMH)
		{
			if ((temp - BATTSTART) == 3) // MaxVoltage
			{
				range.default_value = NIMH_MAX;
			}

			if ((temp - BATTSTART) == 4) // MinVoltage
			{
				range.default_value = NIMH_MIN;
			}
		}

		if (button == ENTER)
		{
			text_link = pgm_read_byte(&BattMenuText[temp - BATTSTART]);
			values[temp - BATTSTART] = do_menu_item(temp, values[temp - BATTSTART], range, 0, text_link);
		}

		// See if cell number or min_volts has changed
		if ((temp_cells != values[1]) || (temp_minvoltage != values[4]))
		{
			values[2] = values[1] * values[4];
			Config.PowerTrigger = values[2];
		}

		// Update value in config structure
		memcpy(&Config.BatteryType,&values[0],sizeof(int16_t) * BATTITEMS);

		if (button == ENTER)
		{
			Save_Config_to_EEPROM(); // Save value and return
		}
	}
	menu_beep(1);
	_delay_ms(200);
}
