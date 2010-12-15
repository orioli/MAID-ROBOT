#include "uEyeCamera.h" /* uEyeCameraキャプチャ用ヘッダ */
#include "stereoCaptureDemo.h" /* デモ用ヘッダ */
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
* コンストラクタ
*/
StereoCaptureDemo::StereoCaptureDemo():dEnable(1.0)
{
	ucam = new uEyeCamera;
	cam_num = ucam->getNumberOfCameras();
}

/**
* デストラクタ
*/
StereoCaptureDemo::~StereoCaptureDemo()
{
   ucam->close();
}

/** 
* 画面の表示
*/
void
StereoCaptureDemo::showImage()
{
	// ウィンドウ作成（opencv）
	cv::namedWindow("StereoCaptureDemo-1", 1);
	cv::namedWindow("StereoCaptureDemo-2", 1);
	cv::Mat mat1, mat2;
	while(1) {
		// キャプチャ
		mat1 = ucam->queryFrame(0);
		mat2 = ucam->queryFrame(1);

		// 画像処理，ロボットの制御処理，別スレッドへのアクセス等
		// ...
		double fps = ucam->setFPS(0, 30.0);
		MyOutputDebugString("newFPS:%.2f\n", fps);
		// 画像表示（opencv）
		cv::imshow("StereoCaptureDemo-1", mat1);
		cv::imshow("StereoCaptureDemo-2", mat2);
		// キーイベント処理（opencv）
		char key = cv::waitKey(10);
		if(key==27) {
			break;
		}
	}
}

/**
* デモプログラムの実行
*/
void
StereoCaptureDemo::run()
{
	// カメラパラメータの設定
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
* メイン関数
*/
int
main(int argc, char *argv[])
{
	StereoCaptureDemo demo = StereoCaptureDemo();
	demo.run();

	return 0;
}
