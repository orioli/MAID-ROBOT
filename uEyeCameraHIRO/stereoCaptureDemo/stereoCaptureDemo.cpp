#include "uEyeCamera.h" /* uEyeCamera�L���v�`���p�w�b�_ */
#include "stereoCaptureDemo.h" /* �f���p�w�b�_ */
#include <cv.h> /* openCV */
#include <highgui.h> /* openCV */

using namespace std;

void MyOutputDebugString( LPCSTR pszFormat, ...)
{
  va_list	argp;
  char pszBuf[256];
  va_start(argp, pszFormat);
  vsprintf(pszBuf, pszFormat, argp);
  va_end(argp);
  OutputDebugString(pszBuf);
}

/**
* �R���X�g���N�^
*/
StereoCaptureDemo::StereoCaptureDemo():dEnable(1.0)
{
	ucam = new uEyeCamera;
	cam_num = ucam->getNumberOfCameras();
}

/**
* �f�X�g���N�^
*/
StereoCaptureDemo::~StereoCaptureDemo()
{
   ucam->close();
}

/** 
* ��ʂ̕\��
*/
void
StereoCaptureDemo::showImage()
{
	// �E�B���h�E�쐬�iopencv�j
	cv::namedWindow("StereoCaptureDemo-1", 1);
	cv::namedWindow("StereoCaptureDemo-2", 1);
	cv::Mat mat1, mat2;
	while(1) {
		// �L���v�`��
		mat1 = ucam->queryFrame(0);
		mat2 = ucam->queryFrame(1);

		// �摜�����C���{�b�g�̐��䏈���C�ʃX���b�h�ւ̃A�N�Z�X��
		// ...
		double fps = ucam->setFPS(0, 30.0);
		MyOutputDebugString("newFPS:%.2f\n", fps);
		// �摜�\���iopencv�j
		cv::imshow("StereoCaptureDemo-1", mat1);
		cv::imshow("StereoCaptureDemo-2", mat2);
		// �L�[�C�x���g�����iopencv�j
		char key = cv::waitKey(10);
		if(key==27) {
			break;
		}
	}
}

/**
* �f���v���O�����̎��s
*/
void
StereoCaptureDemo::run()
{
	// �J�����p�����[�^�̐ݒ�
	for(int i=0; i<cam_num; i++) {
		ucam->setBinning(i, IS_BINNING_4X_VERTICAL, IS_BINNING_4X_HORIZONTAL);		
		ucam->setImageAOI(i, 0, 0, 640, 480);
		//ucam->setAutoParameter(i, IS_SET_ENABLE_AUTO_GAIN, &dEnable, NULL);
		//ucam->setAutoParameter(i, IS_SET_ENABLE_AUTO_SHUTTER, &dEnable, NULL);
		ucam->setAutoParameter(i, IS_SET_ENABLE_AUTO_WHITEBALANCE, &dEnable, NULL);
		int pr = ucam->setPixelClock(i, 30*2);
		double fps = ucam->setFPS(i, 30.0);
		MyOutputDebugString("pr:%d, newFPS:%.2f\n", pr, fps);
	}
	showImage();
}

/**
* ���C���֐�
*/
int
main(int argc, char *argv[])
{
	StereoCaptureDemo demo = StereoCaptureDemo();
	demo.run();

	return 0;
}
