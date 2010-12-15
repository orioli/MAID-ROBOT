#include "uEyeCamera.h"
#include <stdio.h>

void MyOutputDebugString( LPCSTR pszFormat, ...)
{
  va_list	argp;
  char pszBuf[ 256];
  va_start(argp, pszFormat);
  vsprintf( pszBuf, pszFormat, argp);
  va_end(argp);
  OutputDebugString(pszBuf);
}

/**
* デフォルトコンストラクタ
*/
uEyeCamera::uEyeCamera()
{
  for(int i=0; i<MAX_CAM; i++) {
    m_hCam[i] = 0;
    m_nDispModeSel[i] = e_disp_mode_bitmap;
    m_nSizeX[i] = 0;
    m_nSizeY[i] = 0;
    m_PosX[i] = 0;
    m_PosY[i] = 0;
    m_hwndDisp[i] = NULL;
    m_opened[i] = IS_NO_SUCCESS;
	m_pcImageMemory[i] = NULL;
  }
  /// カメラ台数の取得
  if(is_GetNumberOfCameras(&m_CamCount) != IS_SUCCESS)
	  m_CamCount = -1;
  open();
}

/**
* カメラ（uEyeCamera）の台数を返す．
* 
* @return 成功すると，カメラの台数を返す．
* カメラの台数取得に失敗すると，-1を返す．
*/
int uEyeCamera::getNumberOfCameras()
{
	if(m_CamCount < 0)
		return -1;
	return m_CamCount;
}

/**
* カメラの設定パラメータをファイルに保存する．
* 
* @param[in] i カメラ番号
* @param[in] filename ファイル名
* @return 成功すると IS_SUCCESS，失敗すると IS_NO_SUCCESS を返す．
*/
int uEyeCamera::saveParameter(int i, char *filename)
{
  return is_SaveParameters(m_hCam[i], filename);
}

/**
* カメラの設定パラメータをファイルから読み込む．
* 
* @param[in] i カメラ番号
* @param[in] filename ファイル名
* @return 成功すると IS_SUCCESS，失敗すると IS_NO_SUCCESS を返す．
* また，別のカメラ用のiniファイルの場合は IS_INVALID_CAMERA_TYPE を返す．
*/
int uEyeCamera::loadParameter(int i, char *filename)
{
  return is_LoadParameters(m_hCam[i], filename);
}

/**
* カメラの自動パラメータに関する設定を行う．
* 
* @param[in] i カメラ番号
* @param[in] param パラメータ名
* @param[in] pval1 パラメータ値1（ポインタ）
* @param[in] pval2 パラメータ値2（ポインタ）
* @return 成功すると IS_SUCCESS，失敗すると IS_NO_SUCCESS を返す．
*/
int uEyeCamera::setAutoParameter(int i, INT param, double *pval1, double *pval2)
{
  return is_SetAutoParameter(m_hCam[i], param, pval1, pval2);
}

/**
* デバイスのオープン，初期化，メモリ確保を行う
* 
* @return 
*/
int uEyeCamera::open()
{
  int nRet, boRet=0;

  for(int i=0; i<m_CamCount; i++) {

    // init camera
    m_hCam[i] = (HCAM)0;                           // open next camera
    nRet = initCamera (&m_hCam[i], m_hwndDisp[i]);    // init camera
	MyOutputDebugString("m_hCam[%d]:%d\n", i, m_hCam[i]);
    if(nRet == IS_SUCCESS) {
      is_GetCameraInfo(m_hCam[i], &m_ci[i]);
      // retrieve original image size
      is_GetSensorInfo(m_hCam[i], &m_si[i]);
      if(m_nSizeX[i]<=0) m_nSizeX[i] = m_MaxWidth[i] = m_si[i].nMaxWidth;
      if(m_nSizeY[i]<=0) m_nSizeY[i] = m_MaxHeight[i] = m_si[i].nMaxHeight;
      MyOutputDebugString("max[%d]:(%d,%d)\n", i, m_nSizeX[i], m_nSizeY[i]);
      // setup the bitmap or directdraw display mode

      if(m_hCam[i] == NULL)
		return IS_NO_SUCCESS;

      // if some image memory exist already then free it
	  if(m_pcImageMemory[i] != NULL ) {
		nRet = is_FreeImageMem(m_hCam[i], m_pcImageMemory[i], m_nMemoryId[i]);
		m_pcImageMemory[i] = NULL;
	  }

	  if(m_si[i].nColorMode == IS_COLORMODE_BAYER ) {
		  // for color camera models use RGB24 mode
		  m_nColorMode[i] = IS_SET_CM_RGB24;
		  m_nBitsPerPixel[i] = 24;
	  } else {
		  // for monochrome camera models use Y8 mode
		  m_nColorMode[i] = IS_SET_CM_Y8;
		  m_nBitsPerPixel[i] = 8;
	  }
	  // allocate an image memory.
	  nRet = is_AllocImageMem(m_hCam[i],
		  m_nSizeX[i],
		  m_nSizeY[i],
		  m_nBitsPerPixel[i],
		  &m_pcImageMemory[i],
		  &m_nMemoryId[i]);
	  
	  m_opened[i] = nRet;
      if(nRet == IS_SUCCESS) {
	// set the image memory only for the bitmap mode when allocated
	if(m_pcImageMemory[i] != NULL)
	  nRet = is_SetImageMem(m_hCam[i], m_pcImageMemory[i], m_nMemoryId[i]);

	// set the binning
	//nRet = is_SetBinning(m_hCam[i], m_binX[i] | m_binY[i]);
	// set the desired color mode
	nRet = is_SetColorMode(m_hCam[i], m_nColorMode[i]);
	// set the image size to capture
	//nRet = is_SetImageSize(m_hCam[i], m_nSizeX[i], m_nSizeY[i]); // size->pos
	//nRet = is_SetImagePos(m_hCam[i], m_PosX[i], m_PosY[i]);
	//
	//nRet = is_SetImageAOI(m_hCam[i], m_PosX[i], m_PosY[i], m_nSizeX[i], m_nSizeY[i]);

      }   // end if(nRet == IS_SUCCESS)

      if(nRet == IS_SUCCESS) {
	// Enable Messages
	nRet = is_EnableMessage(m_hCam[i], IS_DEVICE_REMOVED, m_hwndDisp[i]);
	nRet = is_EnableMessage(m_hCam[i], IS_DEVICE_RECONNECTED, m_hwndDisp[i]);
	nRet = is_EnableMessage(m_hCam[i], IS_FRAME, m_hwndDisp[i]);

	// do the whitebalance once on the first acquisitioned image only on color cameras
	if(m_si[i].nColorMode == IS_COLORMODE_BAYER ) {
	  double dEnable = 1.0;
	  nRet = is_SetAutoParameter(m_hCam[i], IS_SET_AUTO_WB_ONCE, &dEnable, 0);
	}
			
      }   // end if( nRet == IS_SUCCESS )
    }   // end if( nRet == IS_SUCCESS )

    // 	
    //frame[i] = cvCreateImage(cvSize(m_nSizeX[i], m_nSizeY[i]), IPL_DEPTH_8U, 3);
    frame[i] = cv::Mat(m_nSizeY[i], m_nSizeX[i], CV_8UC3);
    
    nRet = is_CaptureVideo(m_hCam[i], IS_DONT_WAIT);
    if(nRet == IS_SUCCESS) boRet &= 0x01<<i;
  }

  return boRet;
}

/**
* カメラがオープンされているか否かを調べる．
* 
* @param[in] i カメラ番号
* @return 
*/
BOOL uEyeCamera::isOpened(int i)
{
	//return (m_opened[i] == IS_SUCCESS);
	return m_hCam>0 ? true : false;
}

/**
* 
* 
* @return 
*/
INT uEyeCamera::initCamera(HIDS *hCam, HWND hWnd)
{
  INT nRet = is_InitCamera (hCam, hWnd);
#if 0
  if(nRet == IS_STARTER_FW_UPLOAD_NEEDED) {
    // Time for the firmware upload = 25 seconds by default
    INT nUploadTime = 25000;
    is_GetDuration (NULL, IS_SE_STARTER_FW_UPLOAD, &nUploadTime);
    
    char Str1[] = { "This camera requires a new firmware. The upload will take about" };
    char Str2[] = { "seconds. Please wait ..." };
    
    // Try again to open the camera. This time we allow the automatic upload of the firmware by
    // specifying "IS_ALLOW_STARTER_FIRMWARE_UPLOAD"
    *hCam = (HIDS) (((INT)*hCam) | IS_ALLOW_STARTER_FW_UPLOAD); 
    nRet = is_InitCamera (hCam, hWnd);   
  }
#endif
  if(nRet != IS_SUCCESS) {
    *m_hCam = NULL;
    fprintf(stderr, "Open camera failed (Code: %d)", nRet);
  }
  return nRet;
}

/**
* カメラのクローズ

@return 
*/
int uEyeCamera::close()
{
  int gRet=0;
  
  for(int i=0; i<m_CamCount; i++) {
	  if(!isOpened(i))
		  continue;
	  // メッセージ無効化（Windows）
	  is_EnableMessage(m_hCam[i], IS_FRAME, NULL);
	  // キャプチャ停止
	  is_StopLiveVideo(m_hCam[i], IS_WAIT);
	  // メモリ解放
	  if(m_pcImageMemory[i] != NULL)
		  is_FreeImageMem(m_hCam[i], m_pcImageMemory[i], m_nMemoryId[i]);
	  m_pcImageMemory[i] = NULL;
	  // デバイスクローズ
	  int ret = is_ExitCamera(m_hCam[i]);
	  m_hCam[i] = NULL;
	  if(ret != IS_SUCCESS)
		  gRet |= 0x01<<i;

	  frame[i].release();
  }
  return gRet;
}

/**
* キャプチャ画像サイズの設定
* @param[in] i カメラ番号
* @param[in] width 画像の幅
* @param[in] height 画像の高さ
*/
int uEyeCamera::setImageSize(int i, int width, int height)
{
  //if(i>=m_CamCount) return IS_NO_SUCCESS;
  if(m_nSizeX[i]==width && m_nSizeY[i]==height) 
    return IS_SUCCESS;
  m_nSizeX[i] = width;
  m_nSizeY[i] = height;
  if(isOpened(i)) {
    if(m_PosX[i]+width > m_MaxWidth[i] || m_PosY[i]+height > m_MaxHeight[i])
      return IS_NO_SUCCESS;
    is_StopLiveVideo(m_hCam[i], IS_WAIT );
    //cvReleaseImage(&frame[i]);
    //frame[i] = cvCreateImage(cvSize(m_nSizeX[i], m_nSizeY[i]), IPL_DEPTH_8U, 3);
    frame[i].release();
    frame[i] = cv::Mat(m_nSizeY[i], m_nSizeX[i], CV_8UC3);
    if(m_pcImageMemory[i] != NULL)
      is_FreeImageMem(m_hCam[i], m_pcImageMemory[i], m_nMemoryId[i]);
    m_pcImageMemory[i] = NULL;
    is_AllocImageMem(m_hCam[i],
		     m_nSizeX[i],
		     m_nSizeY[i],
		     m_nBitsPerPixel[i],
		     &m_pcImageMemory[i],
		     &m_nMemoryId[i]);
    if(m_pcImageMemory[i] != NULL)
      is_SetImageMem(m_hCam[i], m_pcImageMemory[i], m_nMemoryId[i]);
    is_SetImageSize(m_hCam[i], width, height);
    return is_CaptureVideo(m_hCam[i], IS_DONT_WAIT);
  }
  return IS_SUCCESS;
}

/**
* キャプチャ画像位置の設定
*
* @param[in] i カメラ番号
* @param[in] x 画像左上x座標
* @param[in] y 画像左上y座標
*/
int uEyeCamera::setImagePos(int i, int x, int y)
{
  //  if(i>=m_CamCount) return IS_NO_SUCCESS;
  //	if(x+m_nSizeX[i] > m_MaxWidth[i] || y+m_nSizeY[i] > m_MaxHeight[i])
  //		return IS_NO_SUCCESS;
  m_PosX[i] = x;
  m_PosY[i] = y;
  if(isOpened(i)) {
    is_StopLiveVideo(m_hCam[i], IS_WAIT );
    int ret = is_SetImagePos(m_hCam[i], x, y);
    is_CaptureVideo(m_hCam[i], IS_DONT_WAIT);
	return ret;
  }
  return IS_NO_SUCCESS;
}

/**
* キャプチャ画像AOIの設定
*
* @param[in] i カメラ番号
* @param[in] x 画像左上x座標
* @param[in] y 画像左上y座標
* @param[in] width 画像の幅
* @param[in] height 画像の高さ
*/
int uEyeCamera::setImageAOI(int i, int x, int y, int width, int height)
{
  //	if(i>=m_CamCount) return IS_NO_SUCCESS;
  m_PosX[i] = x;
  m_PosY[i] = y;
  m_nSizeX[i] = width;
  m_nSizeY[i] = height;
  if(isOpened(i)) {
    if(x+width > m_MaxWidth[i] || y+height > m_MaxHeight[i])
      return IS_NO_SUCCESS;
    is_StopLiveVideo(m_hCam[i], IS_WAIT );
    //cvReleaseImage(&frame[i]);
    //frame[i] = cvCreateImage(cvSize(m_nSizeX[i], m_nSizeY[i]), IPL_DEPTH_8U, 3);
    frame[i].release();
    frame[i] = cv::Mat(m_nSizeY[i], m_nSizeX[i], CV_8UC3);
    if(m_pcImageMemory[i] != NULL)
      is_FreeImageMem(m_hCam[i], m_pcImageMemory[i], m_nMemoryId[i]);
    m_pcImageMemory[i] = NULL;
    is_AllocImageMem(m_hCam[i],
		     m_nSizeX[i],
		     m_nSizeY[i],
		     m_nBitsPerPixel[i],
		     &m_pcImageMemory[i],
		     &m_nMemoryId[i]);
    if(m_pcImageMemory[i] != NULL)
      is_SetImageMem(m_hCam[i], m_pcImageMemory[i], m_nMemoryId[i]);
    is_SetImageAOI(m_hCam[i], x, y, width, height);
    return is_CaptureVideo(m_hCam[i], IS_DONT_WAIT);
  }
  return IS_SUCCESS;
}

/**
* Binningの設定
*
* @param[in] i カメラ番号
* @param[in] binx x方向設定
* @param[in] biny y方向設定
* @return 成功すると IS_SUCCESS，失敗すると IS_NO_SUCCESS を返す．
*/
int uEyeCamera::setBinning(int i, int binx, int biny)
{
  //	if(i>=m_CamCount) return IS_NO_SUCCESS;
  m_binX[i] = binx;
  m_binY[i] = biny;
  if(isOpened(i)) {
    is_StopLiveVideo(m_hCam[i], IS_WAIT );
	int ret = is_SetBinning(m_hCam[i], m_binX[i] | m_binY[i]);
    is_CaptureVideo(m_hCam[i], IS_DONT_WAIT);
    return ret;
  }

  return IS_NO_SUCCESS;
}

/**
* 画像キャプチャ
*
* @param[in] i カメラ番号
* @return cv::Matオブジェクトの参照を返す
*/
cv::Mat& uEyeCamera::queryFrame(int i)
{
  frame[i].data = (uchar*)m_pcImageMemory[i];

  return frame[i];
}

/**
* 現在のFPSの取得
*
* @param[in] i カメラ番号
* @return 成功するとFPSを，失敗するとIS_NO_SUCCESSを返す．
*/
double uEyeCamera::getFPS(int i)
{
	double fps;
	int ret = is_GetFramesPerSecond (m_hCam[i], &fps);
	if(ret==IS_SUCCESS)
		return fps;
	else
		return IS_NO_SUCCESS;
}

/**
* FPSの設定
*
* @param[in] i カメラ番号
* @param[in] fps Frame per second
* @return 成功すると新たに設定されたFPSを，失敗するとIS_NO_SUCCESSを返す．
*/
double uEyeCamera::setFPS(int i, double fps)
{
	double new_fps;
	int ret = is_SetFrameRate(m_hCam[i], fps, &new_fps);
	if(ret == IS_SUCCESS)
		return new_fps;
	else
		return IS_NO_SUCCESS;
}

/**
* Pixel Clockの設定
*
* @param[in] i カメラ番号
* @param[in] clock ピクセルクロック（MHz）
* @return 成功するとIS_SUCCESS，失敗するとIS_NO_SUCCESSを返す．
*/
int uEyeCamera::setPixelClock(int i, int clock) 
{
	return is_SetPixelClock(m_hCam[i], clock);
}

/**
* SubSamplingの設定
*
* @param[in] i カメラ番号
* @param[in] mode サンプリングモード
* @return 成功するとIS_SUCCESS，失敗するとIS_NO_SUCCESSを返す．
*/
int uEyeCamera::setSubSampling(int i, int modex, int modey)
{
	return is_SetSubSampling(m_hCam[i], modex|modey);
}
