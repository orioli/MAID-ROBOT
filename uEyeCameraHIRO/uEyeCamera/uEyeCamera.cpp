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
* �f�t�H���g�R���X�g���N�^
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
  /// �J�����䐔�̎擾
  if(is_GetNumberOfCameras(&m_CamCount) != IS_SUCCESS)
	  m_CamCount = -1;
  open();
}

/**
* �J�����iuEyeCamera�j�̑䐔��Ԃ��D
* 
* @return ��������ƁC�J�����̑䐔��Ԃ��D
* �J�����̑䐔�擾�Ɏ��s����ƁC-1��Ԃ��D
*/
int uEyeCamera::getNumberOfCameras()
{
	if(m_CamCount < 0)
		return -1;
	return m_CamCount;
}

/**
* �J�����̐ݒ�p�����[�^���t�@�C���ɕۑ�����D
* 
* @param[in] i �J�����ԍ�
* @param[in] filename �t�@�C����
* @return ��������� IS_SUCCESS�C���s����� IS_NO_SUCCESS ��Ԃ��D
*/
int uEyeCamera::saveParameter(int i, char *filename)
{
  return is_SaveParameters(m_hCam[i], filename);
}

/**
* �J�����̐ݒ�p�����[�^���t�@�C������ǂݍ��ށD
* 
* @param[in] i �J�����ԍ�
* @param[in] filename �t�@�C����
* @return ��������� IS_SUCCESS�C���s����� IS_NO_SUCCESS ��Ԃ��D
* �܂��C�ʂ̃J�����p��ini�t�@�C���̏ꍇ�� IS_INVALID_CAMERA_TYPE ��Ԃ��D
*/
int uEyeCamera::loadParameter(int i, char *filename)
{
  return is_LoadParameters(m_hCam[i], filename);
}

/**
* �J�����̎����p�����[�^�Ɋւ���ݒ���s���D
* 
* @param[in] i �J�����ԍ�
* @param[in] param �p�����[�^��
* @param[in] pval1 �p�����[�^�l1�i�|�C���^�j
* @param[in] pval2 �p�����[�^�l2�i�|�C���^�j
* @return ��������� IS_SUCCESS�C���s����� IS_NO_SUCCESS ��Ԃ��D
*/
int uEyeCamera::setAutoParameter(int i, INT param, double *pval1, double *pval2)
{
  return is_SetAutoParameter(m_hCam[i], param, pval1, pval2);
}

/**
* �f�o�C�X�̃I�[�v���C�������C�������m�ۂ��s��
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
* �J�������I�[�v������Ă��邩�ۂ��𒲂ׂ�D
* 
* @param[in] i �J�����ԍ�
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
* �J�����̃N���[�Y

@return 
*/
int uEyeCamera::close()
{
  int gRet=0;
  
  for(int i=0; i<m_CamCount; i++) {
	  if(!isOpened(i))
		  continue;
	  // ���b�Z�[�W�������iWindows�j
	  is_EnableMessage(m_hCam[i], IS_FRAME, NULL);
	  // �L���v�`����~
	  is_StopLiveVideo(m_hCam[i], IS_WAIT);
	  // ���������
	  if(m_pcImageMemory[i] != NULL)
		  is_FreeImageMem(m_hCam[i], m_pcImageMemory[i], m_nMemoryId[i]);
	  m_pcImageMemory[i] = NULL;
	  // �f�o�C�X�N���[�Y
	  int ret = is_ExitCamera(m_hCam[i]);
	  m_hCam[i] = NULL;
	  if(ret != IS_SUCCESS)
		  gRet |= 0x01<<i;

	  frame[i].release();
  }
  return gRet;
}

/**
* �L���v�`���摜�T�C�Y�̐ݒ�
* @param[in] i �J�����ԍ�
* @param[in] width �摜�̕�
* @param[in] height �摜�̍���
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
* �L���v�`���摜�ʒu�̐ݒ�
*
* @param[in] i �J�����ԍ�
* @param[in] x �摜����x���W
* @param[in] y �摜����y���W
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
* �L���v�`���摜AOI�̐ݒ�
*
* @param[in] i �J�����ԍ�
* @param[in] x �摜����x���W
* @param[in] y �摜����y���W
* @param[in] width �摜�̕�
* @param[in] height �摜�̍���
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
* Binning�̐ݒ�
*
* @param[in] i �J�����ԍ�
* @param[in] binx x�����ݒ�
* @param[in] biny y�����ݒ�
* @return ��������� IS_SUCCESS�C���s����� IS_NO_SUCCESS ��Ԃ��D
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
* �摜�L���v�`��
*
* @param[in] i �J�����ԍ�
* @return cv::Mat�I�u�W�F�N�g�̎Q�Ƃ�Ԃ�
*/
cv::Mat& uEyeCamera::queryFrame(int i)
{
  frame[i].data = (uchar*)m_pcImageMemory[i];

  return frame[i];
}

/**
* ���݂�FPS�̎擾
*
* @param[in] i �J�����ԍ�
* @return ���������FPS���C���s�����IS_NO_SUCCESS��Ԃ��D
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
* FPS�̐ݒ�
*
* @param[in] i �J�����ԍ�
* @param[in] fps Frame per second
* @return ��������ƐV���ɐݒ肳�ꂽFPS���C���s�����IS_NO_SUCCESS��Ԃ��D
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
* Pixel Clock�̐ݒ�
*
* @param[in] i �J�����ԍ�
* @param[in] clock �s�N�Z���N���b�N�iMHz�j
* @return ���������IS_SUCCESS�C���s�����IS_NO_SUCCESS��Ԃ��D
*/
int uEyeCamera::setPixelClock(int i, int clock) 
{
	return is_SetPixelClock(m_hCam[i], clock);
}

/**
* SubSampling�̐ݒ�
*
* @param[in] i �J�����ԍ�
* @param[in] mode �T���v�����O���[�h
* @return ���������IS_SUCCESS�C���s�����IS_NO_SUCCESS��Ԃ��D
*/
int uEyeCamera::setSubSampling(int i, int modex, int modey)
{
	return is_SetSubSampling(m_hCam[i], modex|modey);
}
