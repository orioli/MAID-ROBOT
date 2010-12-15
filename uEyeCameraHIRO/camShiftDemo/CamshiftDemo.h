#pragma once
#include "../../HiroClassLib/Robot.hpp"

#include <uEye.h>
#include <cv.h>
#include <vector>

#include <time.h>

class CamshiftDemo {
public:
	CamshiftDemo();
	~CamshiftDemo();
	static void onMouse(int event, int x, int y, int flags, void* param);
	void run();

	static void findfingers(void* param);
	static void game(void* param);

	static size_t port_write(HANDLE port, void *buf, size_t nbytes);
	static size_t port_read(HANDLE port, void *buf, size_t nbytes);
	static void encoder_re_init_fnc(char init_1[8],char init_2[8],HANDLE port);
	static void encoder_data_get_fnc(HANDLE port);
	static int port_putc(char c, HANDLE port);
	static int port_getc(HANDLE port);

private:




	uEyeCamera *ucam;
	HANDLE port_a, port_b, port_c;
	char TX[16];
	char RX_a[16], RX_b[16], RX_c[16];
	char math[16];

	double dEnable;
	int cam_num;
	int vmin, vmax, smin, fingersensitivity;
	int select_object, track_object;
	int backproject_mode, mirror_mode,opening_mode,p_mode,lose_mode;
	cv::Rect selection;
	cv::Rect track_window;
	cv::Point_<int> origin;
	cv::Mat image;
	cv::Mat image2;
	cv::Mat *histimg;
	cv::Mat currentYCrCbFrame;
	cv::Mat skin;
	int fingers;
	bool firstime;
	void showImage();
	time_t start,end;
	//void draw_hull(cv::Mat im, const vector<cv::Point> hull_points, cv::Scalar color);

	void fingermove(char abc, char m[]);
	static void fingermoveABC(char ma[],char mb[],char mc[],HANDLE port_a,HANDLE port_b,HANDLE port_c);
	HANDLE open_port_a(char name[]);
	HANDLE open_port_b(char name[]);
    HANDLE open_port_c(char name[]);
	static int port_a_putc(char a, HANDLE port_a);
	static int port_b_putc(char b, HANDLE port_b);
	static int port_c_putc(char c, HANDLE port_c);

	int serial_port_a_params (HANDLE port_a,
			int baudrate, int byte_size,
			int stop_bits, int parity);

	int serial_port_b_params (HANDLE port_b,
			int baudrate, int byte_size,
			int stop_bits, int parity);

	int serial_port_c_params (HANDLE port_c,
			int baudrate, int byte_size,
			int stop_bits, int parity);

	int port_a_getc(HANDLE port_a);
	int port_b_getc(HANDLE port_b);
	int port_c_getc(HANDLE port_c);
	static size_t port_a_write(HANDLE port_a, void *buf, size_t nbytes);
	static size_t port_b_write(HANDLE port_b, void *buf, size_t nbytes);
	static size_t port_c_write(HANDLE port_c, void *buf, size_t nbytes);
	size_t port_a_read(HANDLE port_a, void *buf, size_t nbytes);
	size_t port_b_read(HANDLE port_b, void *buf, size_t nbytes);
	size_t port_c_read(HANDLE port_c, void *buf, size_t nbytes);



#ifdef _USE_ROBOT
	KSP::Robot robot;
	const int pan_min, pan_max, tilt_min, tilt_max;
#endif
};

