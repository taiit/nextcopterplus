/*********************************************************************
 * typedefs.h
 ********************************************************************/

#ifndef TYPE_DEFS_H_
#define TYPE_DEFS_H_

/*********************************************************************
 * Type definitions
 ********************************************************************/

#define INPUT 	0
#define OUTPUT 	1
#define MAX_RC_CHANNELS 13				// Maximum input channels
#define MAX_OUTPUTS 8					// Maximum output channels

typedef struct
{
	uint16_t	x;
	uint16_t	y;
} mugui_size16_t;

// Channel mixer definition
// Size = 20 bytes
typedef struct
{
	uint16_t	value;					// Current value
	uint8_t		source;					// Source RC input for calculation
	uint8_t		source_polarity;		// Normal/reverse RC input
	uint8_t		source_volume;			// Percentage of source to pass on
	uint8_t		roll_gyro;				// Use roll gyro
	uint8_t		roll_gyro_polarity;		// Roll gyro normal/reverse
	uint8_t		pitch_gyro;				// Use pitch gyro
	uint8_t		pitch_gyro_polarity;	// Pitch gyro normal/reverse
	uint8_t		yaw_gyro;				// Use yaw gyro
	uint8_t		yaw_gyro_polarity;		// Yaw gyro normal/reverse
	uint8_t		roll_acc;				// Use roll acc
	uint8_t		roll_acc_polarity;		// Roll acc normal/reverse
	uint8_t		pitch_acc;				// Use pitch acc
	uint8_t		pitch_acc_polarity;		// Pitch acc normal/reverse
	uint16_t	min_travel;				// Minimum output value
	uint16_t	max_travel;				// Maximum output value
	uint16_t	Failsafe;				// Failsafe position
} channel_t;

// PID type
// Size = 3 bytes
typedef struct
{
	uint8_t	P_mult;
	uint8_t	I_mult;
	uint8_t	D_mult;
} PID_mult_t;

// Settings structure
// Size = 228 bytes
typedef struct
{
	uint8_t	setup;						// Byte to identify if already setup

	// Menu adjustable items
	// RC settings
	uint8_t		ChannelOrder[9];		// Assign channel numbers to hard-coded channel order
										// OpenAeroEvo uses Thr, Ail, Ele, Rud, Gear, Flap, Aux1, Aux2
										// THROTTLE will always return the correct data for the assigned throttle channel
										// AILERON will always return the correct data for the assigned aileron channel
										// ELEVATOR will always return the correct data for the assigned elevator channel
										// RUDDER will always return the correct data for the assigned rudder channel
										// AUX1 to AUX4 are fixed
	uint8_t		RxMode;					// PWM or CPPM mode
	uint8_t		TxSeq;					// Channel order of transmitter (JR/Futaba etc)
	uint8_t		StabChan;				// Channel number to select stability mode
	uint8_t		AutoChan;				// Channel number for Autolevel switch input
	uint8_t		FlapChan;				// Channel number for second aileron input
	uint8_t		ThreePos;				// Channel number for ThreePos switch
	uint8_t		AileronExpo;			// Amount of expo on Aileron channel
	uint8_t		ElevatorExpo;			// Amount of expo on Elevator channel
	uint8_t		RudderExpo;				// Amount of expo on Rudder channel
	uint8_t		Differential;			// Amount of differential on Aileron channels
	
	// Autolevel settings
	uint8_t		AutoMode;
	uint8_t		AccRollZeroTrim;		// User-set ACC trim (0~255 -> +/-127)
	uint8_t		AccPitchZeroTrim;
	PID_mult_t	G_level;				// Gyro level
	PID_mult_t	A_level;				// Acc level

	// Stability PID settings
	uint8_t		StabMode;				// Stability switch mode
	PID_mult_t	Roll;					// Gyro PID settings
	PID_mult_t	Pitch;
	PID_mult_t	Yaw;

	// Battery settings
	uint16_t	PowerTrigger;			// Trip voltage
	uint8_t		BatteryCells;			// Number of cells (2~5)	
	uint8_t		BatteryType;			// LiPo, NiMh
	uint16_t	MinVoltage;				// Minimum cell voltage in discharge state
	uint16_t	MaxVoltage;				// Maximum cell voltage in charged state
	
	// Mixer modes
	uint8_t		MixMode;				// Aeroplane/Flying Wing/Manual
	uint8_t		CamStab;
	uint8_t		RCMix;
	uint8_t		Orientation;			// Horizontal / vertical
	uint8_t		Contrast;
		
	// Non-menu items 
	// Channel configuration
	channel_t	Channel[MAX_OUTPUTS];	// Channel mixing data	

	// Misc
	uint8_t		Modes;					// Misc flight mode flag
	uint8_t		AutoUpdateEnable;			// Status screen auto-update enable flag

	// RC inputs
	uint16_t 	RxChannelZeroOffset[MAX_RC_CHANNELS];	// RC channel offsets

	// Acc zeros
	uint16_t	AccRollZero;			// Acc calibration results
	uint16_t	AccPitchZero;
	uint16_t	AccZedZero;
	
	// Preset channels
	uint16_t	Preset1;				// RC presets for camstab
	uint16_t	Preset2;
	uint16_t	Preset3;
	uint16_t	Preset4;

	// 
	uint16_t	Dummy;

} CONFIG_STRUCT;

typedef struct
{
	int16_t lower;						// Lower limit for menu item
	int16_t upper;						// Upper limit for menu item
	uint8_t increment;					// Increment for menu item
	uint8_t style;						// 0 = numeral, 1 = text
	uint16_t default_value;				// Default value for this item
} menu_range_t; 


// The following code courtesy of: stu_san on AVR Freaks

typedef struct
{
  unsigned int bit0:1;
  unsigned int bit1:1;
  unsigned int bit2:1;
  unsigned int bit3:1;
  unsigned int bit4:1;
  unsigned int bit5:1;
  unsigned int bit6:1;
  unsigned int bit7:1;
} _io_reg; 

#define REGISTER_BIT(rg,bt) ((volatile _io_reg*)&rg)->bit##bt

#endif
