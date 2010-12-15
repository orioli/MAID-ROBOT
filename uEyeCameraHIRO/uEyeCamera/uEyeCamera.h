#pragma once

#include <uEye.h>
#include <cv.h>
#include <vector>
using namespace std;

#if(defined WIN32 || defined _WIN32)
#define UEYE_EXPORTS __declspec(dllexport)
#define PRAGMA_DIS4251 warning(disable:4251)
#define PRAGMA_DEF4251 warning(default:4251)
#define ISNAN _isnan
#else
#define UEYE_EXPORTS
#define PRAGMA_DIS4251
#define PRAGMA_DEF4251
#define LPCSTR const char*
#define ISNAN isnan
#endif


typedef enum _disp_mode {
	e_disp_mode_bitmap = 0,
	e_disp_mode_directdraw
};

class UEYE_EXPORTS uEyeCamera {
#define MAX_CAM (8)
public:
	uEyeCamera();
	~uEyeCamera(){};
	int close();
	BOOL isOpened(int i);
	int saveParameter(int i, char *filename);
	int loadParameter(int i, char *filename);
	int setAutoParameter(int i, INT param, double *pval1, double *pval2);
	int setImageSize(int i, int width, int height);
	int setImagePos(int i, int x, int y);
	int setImageAOI(int i, int x, int y, int width, int height);
	int setBinning(int i, int binx, int biny);
	int getNumberOfCameras();
	cv::Mat& queryFrame(int i);
	double getFPS(int i);
	double setFPS(int i, double fps);
	int setPixelClock(int i, int clock);
	int setSubSampling(int i, int modex, int modey);
private:
	int open();
	INT initCamera(HIDS *hCam, HWND hWnd);
	int             m_PosX[MAX_CAM], m_PosY[MAX_CAM];
	int             m_nSizeX[MAX_CAM], m_nSizeY[MAX_CAM];
	int             m_MaxWidth[MAX_CAM], m_MaxHeight[MAX_CAM];
	int             m_binX[MAX_CAM], m_binY[MAX_CAM];
	HCAM            m_hCam[MAX_CAM];
	CAMINFO         m_ci[MAX_CAM]; // camera info
	SENSORINFO      m_si[MAX_CAM]; // sensor info
	char*           m_pcImageMemory[MAX_CAM];
	int             m_nMemoryId[MAX_CAM];
	int             m_nColorMode[MAX_CAM];
	int             m_nBitsPerPixel[MAX_CAM];
	int             m_nDispModeSel[MAX_CAM];
	HWND            m_hwndDisp[MAX_CAM];
	BOOL            m_opened[MAX_CAM];
	int             m_CamCount;
protected:
#pragma PRAGMA_DIS4251
	cv::Mat         frame[MAX_CAM];
#pragma PRAGMA_DEF4251
};


#if 0
IS_SET_ENABLE_AUTO_GAIN 
Enables / disables the auto gain function.
Control parameter 
pval1 = 1 enables, 0 disables control

IS_GET_ENABLE_AUTO_GAIN 
Returns the current auto gain setting. 
Control parameter 
pval1 returns the current value

IS_SET_ENABLE_AUTO_SENSOR_GAIN 
Enables / disables the sensor`s internal auto gain function *).
Control parameter 
pval1 = 1 enables, 0 disables control

IS_GET_ENABLE_AUTO_SENSOR_GAIN 
Returns the current setting of the sensor`s internal auto gain function *). 
Control parameter 
pval1 returns the current value

IS_SET_ENABLE_AUTO_SHUTTER
Enables / disables the auto exposure function.
Control parameter 
pval1 = 1 enables, 0 disables control

IS_GET_ENABLE_AUTO_SHUTTER 
Returns the current auto exposure setting. 
Control parameter 
pval1 returns the current value

IS_SET_ENABLE_AUTO_SENSOR_SHUTTER
Enables / disables the sensor`s internal auto exposure function. *). 
Control parameter 
pval1 = 1 enables, 0 disables control

IS_GET_ENABLE_AUTO_SENSOR_SHUTTER
Returns the current setting of the sensor`s internal auto exposure function *). 
Control parameter 
pval1 returns the current value

IS_SET_ENABLE_AUTO_WHITEBALANCE
Enables / disables the auto white balance function.
Control parameter 
pval1 = 1 enables, 0 disables control

IS_GET_ENABLE_AUTO_WHITEBALANCE
Returns the current auto white balance setting.
Control parameter 
pval1 returns the current value

IS_SET_ENABLE_AUTO_FRAMERATE 
Enables / disables the auto frame rate function.
Control parameter 
pval1 = 1 enables, 0 disables control

IS_GET_ENABLE_AUTO_FRAMERATE 
Returns the current auto frame rate setting. 
Control parameter 
pval1 returns the current value

IS_SET_ENABLE_AUTO_SENSOR_FRAMERATE
Enables / disables the sensor`s internal auto frame rate function. *). 
Control parameter 
pval1 = 1 enables, 0 disables control

IS_GET_ENABLE_AUTO_SENSOR_FRAMERATE
Returns the current setting of the sensor`s internal auto frame rate function *). 
Control parameter pval1 returns the current value

IS_SET_AUTO_REFERENCE 
Sets the setpoint value for auto gain / auto shutter.
Control parameter
pval1 the setpoint value (average image brightness). 
Independent pixel bit depth the setpoint range is:
0 = black
128 = 50% grey (default)
255 = white

IS_GET_AUTO_REFERENCE 
Returns the setpoint value for auto gain / auto shutter. 
Control parameter
pval1 returns the current value

IS_SET_AUTO_GAIN_MAX 
Sets the upper limit for auto gain. Control parameter
pval1 valid value for gain (0...100)

IS_GET_AUTO_GAIN_MAX 
Returns the upper limit for auto gain. Control
parameter
pval1 returns the current value

IS_SET_AUTO_SHUTTER_MAX 
Sets the upper limit for auto exposure. Control
parameter
pval1 valid exposure value (0 sets the value continuously to max. exposure)

IS_GET_AUTO_SHUTTER_MAX 
Returns the upper limit for auto exposure. Control
parameter
pval1 returns the current value

IS_SET_AUTO_SPEED 
Sets the speed value for auto gain / auto exposure.
Control parameter
pval1 defines the control speed (0...100)

IS_GET_AUTO_SPEED 
Returns the speed value for auto gain / auto exposure. Control parameter
pval1 returns the current value

IS_SET_AUTO_HYSTERESIS 
Sets the hysteresis for auto gain / auto exposure.
Control parameter
pval1 defines the hysteresis value (default: 2)

IS_GET_AUTO_HYSTERESIS 
Returns the hysteresis for auto gain / auto exposure.
Control parameter
pval1 returns the current value

IS_GET_AUTO_HYSTERESIS_RANGE 
Returns range for the hysteresis value. Control
parameter
pval1 returns the minimum value
pval2 returns the maximum value

IS_SET_AUTO_SKIPFRAMES 
Sets the number of frames to be skipped for auto gain / auto exposure. Control parameter
pval1 defines the number of frames to be skipped
(default: 4)

IS_GET_AUTO_SKIPFRAMES 
Returns the number of frames to be skipped for auto gain / auto exposure. 
Control parameter pval1 returns the current value

IS_GET_AUTO_SKIPFRAMES_RANGE 
Returns range for the number of frames to be skipped. Control parameter
pval1 returns the minimum value
pval2 returns the maximum value

IS_SET_AUTO_BRIGHTNESS_ONCE 
Enables / disables automatic disabling of auto gain / auto exposure **). Control parameter
pval1 = 1 enables, 0 disables control

IS_GET_AUTO_BRIGHTNESS_ONCE 
Returns the automatic disable status of auto gain / auto exposure **). Control parameter
pval1 returns the current value

// Adjust auto white balance
IS_SET_AUTO_WB_OFFSET 
Sets the offset value for the red and blue channels.
Control parameter
pval1 defines the red level offset (-50...50)
pval2 defines the blue level offset (-50...50)

IS_GET_AUTO_WB_OFFSET 
Returns the offset value for the red and blue channels. Control parameter
pval1 returns the red level offset (-50...50)
pval2 returns the blue level offset (-50...50)

IS_SET_AUTO_WB_GAIN_RANGE 
Sets the gain limits for the auto white balance
function. Control parameter
pval1 sets the minimum value
pval2 sets the maximum value

IS_GET_AUTO_WB_GAIN_RANGE 
Returns the gain limits for the auto white balance
function. Control parameter
pval1 returns the minimum value
pval2 returns the maximum value

IS_SET_AUTO_WB_SPEED 
Sets the speed value for the auto white balance.
Control parameter
pval1 defines the control speed (0...100)

IS_GET_AUTO_WB_SPEED 
Returns the speed value for the auto white balance.
Control parameter
pval1 returns the current value

IS_SET_AUTO_WB_HYSTERESIS 
Sets the hysteresis for auto white balance. Control
parameter
pval1 defines the hysteresis value (default: 2)

IS_GET_AUTO_WB_HYSTERESIS 
Returns the hysteresis for auto white balance.
Control parameter
pval1 returns the current value

IS_GET_AUTO_WB_HYSTERESIS_RANGE
Returns range for the hysteresis value. Control
parameter
pval1 returns the minimum value
pval2 returns the maximum value

IS_SET_AUTO_WB_SKIPFRAMES 
Sets the number of frames to be skipped for auto white balance. 
Control parameter
pval1 defines the number of frames to be skipped (default: 4)

IS_GET_AUTO_WB_SKIPFRAMES 
Returns the number of frames to be skipped for auto white balance. Control parameter
pval1 returns the current value

IS_GET_AUTO_WB_SKIPFRAMES_RANGE
Returns range for the number of frames to be skipped. Control parameter
pval1 returns the minimum value
pval2 returns the maximum value

IS_SET_AUTO_WB_ONCE 
Enables / disables automatic disabling of auto white balance **). Control parameter
pval1 = 1 enables, 0 disables control

IS_GET_AUTO_WB_ONCE 
Returns the automatic disable status of auto white balance **). Control parameter
pval1 returns the current value

// Pre-defined values for auto gain/auto exposure
// For parameters pval1 and pval, NULL must be passed.
IS_DEFAULT_AUTO_BRIGHT_REFERENCE 
Default setpoint value for auto gain / exposure

IS_MIN_AUTO_BRIGHT_REFERENCE 
Minimum setpoint value for auto gain / exposure

IS_MAX_AUTO_BRIGHT_REFERENCE 
Maximum setpoint value for auto gain / exposure

IS_DEFAULT_AUTO_SPEED
 Default value for auto speed

IS_MAX_AUTO_SPEED 
Maximum value for auto speed

// Pre-defined values for auto white balance
// For parameters pval1 and pval, NULL must be passed.

IS_DEFAULT_WB_OFFSET 
Default value for auto white balance offset

IS_MIN_WB_OFFSET 
Minimum value for auto white balance offset

IS_MAX_WB_OFFSET 
Maximum value for auto white balance offset

IS_DEFAULT_AUTO_WB_SPEED 
Default value for auto white balance speed

IS_MIN_AUTO_WB_SPEED 
Minimum value for auto white balance speed

IS_MAX_AUTO_WB_SPEED 
Maximum value for auto white balance speed
pval1 Control parameter, can have a variable value depending on the corresponding auto function (see
below)
pval2 Control parameter, can have a variable value depending on the corresponding auto function (see
below)

// Return Values
IS_SUCCESS 
Function executed successfully

IS_NO_SUCCESS 
General error message
#endif
