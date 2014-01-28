/*********************************************************************
 * gyros.h
 ********************************************************************/

//***********************************************************
//* Externals
//***********************************************************

extern void ReadGyros(void);
extern void CalibrateGyrosFast(void);
extern void CalibrateGyrosSlow(void);
extern void get_raw_gyros(void);

extern int16_t gyroADC[3];		// Holds 16-bit gyro values
