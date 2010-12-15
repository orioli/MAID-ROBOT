#pragma once

class StereoCaptureDemo {
public:
	StereoCaptureDemo();
	~StereoCaptureDemo();
	void run();
private:
	uEyeCamera *ucam;
	int cam_num;
	double dEnable;
	void showImage();
};
