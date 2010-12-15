#include "uEyeCamera.h" /* uEyeCameraキャプチャ用ヘッダ */
#include <cv.h> /* openCV */
#include <highgui.h> /* openCV */
#define _USE_ROBOT
#ifdef _USE_ROBOT
#include "Robot.hpp"


#ifndef IPADDR
#define IPADDR "192.168.128.3"
#endif
#endif
#include "camShiftDemo.h" /* デモ用ヘッダ */


#include <windows.h>
#include <mmsystem.h>
#include <time.h>


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

// imitate ot janken game
void
CamshiftDemo::game(void* param)
{

	CamshiftDemo *camshift = (CamshiftDemo*)param;

	if (camshift->firstime)
		{

			time (&(camshift->start));
			camshift->firstime = false;
			PlaySound("C:\\Documents and Settings\\hrpuser\\デスクトップ\\jkp.wav", NULL,  (SND_SYNC|SND_FILENAME));

		}


	// TALK every tt seconds ----
	double tt = 5.0;
	time (&camshift->end);
	double dif = difftime (camshift->end,camshift->start);
	std::string jkp ="";
	if (dif > tt ) 
	{
		// play RESPONSE again
		time (&camshift->start);
		//std::string song = "C:\\Documents and Settings\\hrpuser\\デスクトップ\\";
		//song.append(jkp);
		//song.append(".wav");
		
		//PlaySound(song.c_str(), NULL,  (SND_ASYNC|SND_FILENAME));
		//PlaySound(song.c_str(), NULL,  (SND_SYNC|SND_FILENAME));

		int speed = 23;
		camshift->robot.rarm.moveFore(1,3,0,speed);
		fingermoveABC("18884444","33334444","19884344",camshift->port_a,camshift->port_b,camshift->port_c);
		camshift->robot.rarm.moveFore(0,-2,0,speed * 2);
		PlaySound("C:\\Documents and Settings\\hrpuser\\デスクトップ\\jkp.wav", NULL,  (SND_ASYNC|SND_FILENAME));
		
		

		camshift->robot.rarm.moveFore(0,2,0,speed);
		camshift->robot.rarm.moveFore(-1,-3,0,speed * 2);
		camshift->robot.rarm.moveFore(0,2,0,speed);	
		camshift->robot.rarm.moveFore(0,-2,0,speed * 2);
		camshift->robot.wait();

		//encoder_data_get_fnc(camshift->port_c);

		// LOOP WAIT UNTIL POI IS SAID
		//Wait until number of fingers is stabilized
		Sleep(170);// <-- KOKO WA POINTO!!

		findfingers(camshift);
		int fingers = camshift->fingers;

		if (  fingers < 1  )
			jkp = "gu";
		else
		{
			if ( fingers >=4 )
				jkp = "pa";
			else
				jkp = "choki";
		}
	

		cout << "human: " << jkp << " fingers: " << camshift->fingers << endl;
		int lose_mode = camshift->lose_mode;

		if (jkp.compare("pa")==0 )
		{
			//PA
			if (lose_mode==0)
				fingermoveABC("18883333","85557fff","7fffafaf",camshift->port_a,camshift->port_b,camshift->port_c);
			else
				fingermoveABC("18883333","33334444","18883333",camshift->port_a,camshift->port_b,camshift->port_c);

			Sleep(300);
		}
		
		if (jkp.compare("choki")==0 )
		{
			// CHOKI
			if (lose_mode==0)
				fingermoveABC("18883333","33334444","18883333",camshift->port_a,camshift->port_b,camshift->port_c);
			else
				fingermoveABC("7fff7fff","7fff7fff","7fff7fff",camshift->port_a,camshift->port_b,camshift->port_c);
				
			Sleep(300);

		}
		
		if (jkp.compare("gu")==0 )
		{
			//GU
			if(lose_mode ==0)
				fingermoveABC("7fff7fff","7fff7fff","7fff7fff",camshift->port_a,camshift->port_b,camshift->port_c);
			else
				fingermoveABC("18883333","85557fff","7fffafaf",camshift->port_a,camshift->port_b,camshift->port_c);

			Sleep(300);

		}
		// ---------------------------------------------

		// Some miliseconds later....
		// CHECK WIN OR LOOSE
		findfingers(camshift);
		fingers = camshift->fingers;

		std::string jkp2 = "";

		if (  fingers < 1  )
			jkp2 = "gu";
		else
		{
			if ( fingers >=4 )
				jkp2 = "pa";
			else
				jkp2 = "choki";
		}
		cout << "human: " << jkp << " fingers: " << camshift->fingers << endl;


		if (jkp2.compare(jkp)==0 )
		{
			if(lose_mode ==0)
			{
					PlaySound("C:\\Documents and Settings\\hrpuser\\デスクトップ\\make.wav", NULL,  (SND_ASYNC|SND_FILENAME));
					cout << "jkp1 = jkp " << "hiro win" << endl;
			}
			else
			{
					PlaySound("C:\\Documents and Settings\\hrpuser\\デスクトップ\\kachi.wav", NULL,  (SND_ASYNC|SND_FILENAME));
					cout << "jkp1 = jkp " << "human win" << endl;
			
			}
		}
		else
		{
			cout << "jkp != jkp2 " << endl;;
			if(
				(jkp2.compare("pa")==0 && jkp.compare("pa")== 0) ||
				(jkp2.compare("gu")==0 && jkp.compare("gu")== 0) ||
				(jkp2.compare("choki")==0 && jkp.compare("choki")== 0) 
			  )
			{
				cout << "same" << endl;
			}

			if(
				(jkp2.compare("pa")==0 && jkp.compare("choki")== 0) ||
				(jkp2.compare("gu")==0 && jkp.compare("pa")== 0) ||
				(jkp2.compare("choki")==0 && jkp.compare("gu")== 0) 
			  )
			{
				cout << "huma win " << endl;
				PlaySound("C:\\Documents and Settings\\hrpuser\\デスクトップ\\kachi.wav", NULL,  (SND_ASYNC|SND_FILENAME));

			}

		
		
		}//　WIN OR LOOSE CHECK END




	}// make janken moves

		

}

// find fingers function
void
CamshiftDemo::findfingers(void* param)
{
	
	int fingers = 0;
	CamshiftDemo *camshift = (CamshiftDemo*)param;
	cv::Mat &image = camshift->image;
	cv::Mat &image2 = camshift->image2;

	cv::Mat *frame;
	//cv::Mat image; 
	//cv::Mat image2;

	frame = &(camshift->ucam)->queryFrame(0);
    if(!frame)
	{
        cout << " no frame available" << endl;
		//image = camshift->image;
		//image2 = camshift->image2;
	}
	else
	{
		frame->copyTo(image);
		frame->copyTo(image2);
	}

	cv::Mat currentYCrCbFrame(cv::Size(640, 480), CV_8UC3);
	cv::cvtColor(image,currentYCrCbFrame,CV_BGR2YCrCb);
	cv::Mat skin = cv::Mat(cv::Size(640, 480), CV_8UC1);

	// ----- CODE TONGO STARTS
	int y, cr, cb, x1, y1, value;
	int rows = skin.rows;
	int cols = skin.cols;
	int step =currentYCrCbFrame.step;

	//fprintf(stderr,"skin.rows : %d  skin.rows  %d\n", skin.rows,skin.cols);

	// 1 . SKIN DETECTS ---------------------------------------------------------------
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			y  = (int)currentYCrCbFrame.at<cv::Vec3b>(i,j)[0];
			cr = (int)currentYCrCbFrame.at<cv::Vec3b>(i,j)[1];
			cb = (int)currentYCrCbFrame.at<cv::Vec3b>(i,j)[2];

            cb -= 109;
	        cr -= 152;
		    x1 = (819 * cr - 614 * cb) / 32 + 51;
			y1 = (819 * cr + 614 * cb) / 32 + 77;
	        x1 = x1 * 41 / 1024;
		    y1 = y1 * 73 / 1024;
			value = x1 * x1 + y1 * y1;
	        if (y < 100)
				skin.at<uchar>(i,j) = (value < 700) ? (byte)255 : (byte)0;
			else
				skin.at<uchar>(i,j) = (value < 850) ? (byte)255 : (byte)0;

			//test
			//skin.data[i, j, 0] = (value < 850) ? 100 : 200;
			//if (j== 200 && i == 200) {
				//fprintf(stderr,"value : %d  skin  %d\n", value,skin.data[i,j,0]);
			//}
		}
	}
			
	// 2 . OPENING --------------------------------------------------------------------
	cv::Size strel_size;
	strel_size.width = 6;
	strel_size.height = 6;
	cv::Mat strel = cv::getStructuringElement(cv::MORPH_RECT,strel_size,cv::Point(-1,-1));
	cv::erode(skin, skin, strel,cv::Point(-1,-1),1);
	cv::dilate(skin, skin, strel,cv::Point(-1,-1),2);
	skin = skin > 128;
	//cv::cvtColor(skin, image, CV_GRAY2BGR);	

	// 3 . CONTOUR ---------------------------------------------------------------------
	std::vector<std::vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;
	cv::findContours(skin, contours,hierarchy,cv::RETR_LIST,cv::CHAIN_APPROX_SIMPLE, cv::Point(0,0) ); 

	//fprintf(stderr,"contour size area ...%d  \n",contours.size());

	if( !contours.empty()) 
	{
		// find max size contour
		vector<cv::Point> max_con;
		vector<cv::Point> approx;
		unsigned int max_index =0;
		int max_size = -1;
		//cout << " size of countour " << contours.size() << endl;
		for(int k=0; k< contours.size(); k++)
		{	
			if (max_size < (int)contours.at(k).size() )
			{
				max_size = contours.at(k).size();
				max_index = k;
			}	
			//fprintf(stderr,"contour %d size  %d  area = %d  \n",k,contours.at(k).size(),area1 );
		}
		for (int h=0; h< contours.at(max_index).size(); h++)
			max_con.push_back(cv::Point(contours.at(max_index).at(h).x,contours.at(max_index).at(h).y));
		
		//fprintf(stderr,"max index is . . . %d  \n",max_index );

		// 4 . POLYLINE SIMPLYFY -------------------------------------------------------
		cv::approxPolyDP(max_con, approx, (double)5.055, true);
		cv::Scalar color2( (20), 255, 55 );

		int npts = max_con.size();        
		for (int i=0; i<npts-1; i++)    
			cv::line(image2, max_con[i], max_con[i+1], color2,3);      

		if (max_size == -1 ) 
			cout << "error index max is -1.";
		if (max_con.empty() ) 
			cout << "error max_con empty.";
	
		// 5 . FIND HULL OUTER SHELL ---------------------------------------------------------
		vector<cv::Point> hull;
		cv::convexHull(max_con,hull,true);
		if (hull.empty() ) 
			cout << "error hull empty.";
		
		npts = hull.size();
		for (int i=0; i<npts-1; i++)          
			cv::line(image2, hull[i], hull[i+1], color2,3);      

		npts = hull.size();
		if (npts >2)
		{
			// calculate geometric center
			double sumx = 0;
			double sumy = 0;
			for (int i=0; i<npts; i++)
			{
				sumx = sumx + hull[i].x;
				sumy = sumy + hull[i].y;
			}
			// calc hulls max and min points to geometirc center of shape
			double d = 0;
			double dmax = 0;
			double dmin = 1000000000;
			int maxi= -1;
			int mini= -1;

			for (int i=0; i<hull.size(); i++)
			{
				d = sqrt(pow(hull[i].x - sumx/npts, 2) + pow(hull[i].y - sumy/npts, 2));
				if (dmax < d)
				{
					dmax = d;
					maxi = i;
				}
				if (dmin > d)
				{
					dmin = d;
					mini = i;
				}

			}
			
			if (maxi ==-1 )
				cout << " maxi es -1";
			if (mini ==-1 )
				cout << " mini es -1";

			//track_box.center.x = sumx/npts;
			//track_box.center.y = sumy/npts;
			
			// 6 . FILTER HULL ------------------------------------------------------------
			vector<cv::Point> filteredHull;
			for (int i = 0; i < npts -1; i++)
			{
				if (sqrt( pow(double(hull[i].x - hull[i + 1].x), 2) +
					pow(double(hull[i].y - hull[i + 1].y), 2) ) > 20);
				{
					filteredHull.push_back(hull[i]);
				}
			}
			
			//cout << " fhull = " << filteredHull.size() <<endl;
			cv::Scalar color3( 20, 55, 255 );

			//for (int i=0; i<filteredHull.size()-1; i++)          
			//	cv::line(image, filteredHull[i], filteredHull[i+1], color3,2); 

			// !! calc filteredhulls max and min points to geometirc center of shape
			d = 0;
			dmax = 0;
			dmin = 10000000000;
			maxi= -1;
			mini= -1;

			for (int i=0; i<filteredHull.size(); i++)
			{
				d = sqrt(pow(filteredHull[i].x - sumx/npts, 2) + pow(filteredHull[i].y - sumy/npts, 2));
				if (dmax < d)
				{
					dmax = d;
					maxi = i;
				}
				if (dmin > d)
				{
					dmin = d;
					mini = i;
				}

			}
			if (maxi ==-1 )
				cout << " maxi es -1";
			if (mini ==-1 )
				cout << " mini es -1";
			
			//cout << "  dmax=" << dmax << "   maxi =   "  << maxi;
			//cout << "  dmin= " << dmin << "  mini =   " << mini;

			cv::Point pcenter;
			cv::Scalar color5( 250, 55, 55 );
			pcenter = cv::Point((int)(sumx/npts),(int)(sumy/npts));
			//if (maxi !=-1 )
			//	cv::line(image, pcenter, filteredHull[maxi], color5,3);
			//if (mini!=-1)
			//	cv::line(image, pcenter, filteredHull[mini], color5,3);
		

		
			// 7 . CALC DEFECTS ----------------------------------------------------------------------
			// Generate hull + midpoints vector 
			vector<cv::Point> midpoints;
			for (int i = 0; i < filteredHull.size() -1; i++)
            {
				midpoints.push_back(
					cv::Point((filteredHull[i].x + filteredHull[i + 1].x)/2,
					(filteredHull[i].y + filteredHull[i + 1].y)/2));

				midpoints.push_back(filteredHull[i]);


			}
			midpoints.push_back(
					cv::Point((filteredHull[0].x + filteredHull[filteredHull.size() -1].x)/2,
					(filteredHull[0].y + filteredHull[filteredHull.size() -1].y)/2));

			midpoints.push_back(filteredHull[filteredHull.size() -1]);

			//for (int i=0; i < midpoints.size() ; i++)
			//{
			//	cv::circle(image,midpoints[i],5,CV_RGB(255,0,0),3,8,0);
			//	//cv::line(image,midpoints[i],pcenter,CV_RGB(255,0,0),1,8,0);
			//}

			// 8 . Calculate defectes with contour -------------------------------------------
			vector<double> defects;
			d = -1;
			double maxdmin = +10000000;
			for (int i = 0; i < max_con.size() -1; i++)
            {
				//for each contour point find nearest midpoint to contour point
				double d = -1;
				double dmin = +10000000;
				int jmin = -1;
				for (int j = 0; j < midpoints.size() ; j++)
                {
					d = sqrt(
								pow(double(max_con[i].x - midpoints[j].x), 2) + 
								pow(double(max_con[i].y - midpoints[j].y), 2)
								);
					if (d<dmin)
					{
						dmin = d;
						jmin = j; 
					}
				}
				if (d == -1 )
					cout << " d == -1 errror" << endl;

				defects.push_back(dmin);

			}

			// 9 . FIND FINGERS -------------------------------------------------------

			double thr = camshift->fingersensitivity; //_fingersensitivity;
			fingers = 0;	
			double top = 0;
			//int thr = (dmax+dmin/2);
			//cout << "dmax + dmin = " << (dmin+dmax)/2 <<  "thr " << thr <<endl;
			
			// count each finger once
			
				
			bool counting = false;
			for (int i = 0; i < defects.size() ; i++)
			{
				if (!counting)
				{
					if (defects[i] > thr )  // && defects[i] > top/2									
					{
						counting =true;
						fingers ++;
						top = defects[i];
					}
				}
				else
				{
					//reset?
					if(defects[i]> top )
					{
						top = defects[i];
						counting =true;
					
					}
					else
					{
						//stop counting?
						if (1.0*defects[i]/top < 0.5 || defects[i] < 0.7*thr )
							counting = false;
					}
				}
			}
			//cout << "fingers .... " << fingers;

		}//npts <2

	} //!contours.empty()


	// 10 . DRAW

		std::string s;
		std::string msg;
		std::stringstream out;
		out << fingers;
		s = out.str();
		msg.append( "Yonezawa University");
		cv::putText(image2,msg,cv::Point(20,45),cv::FONT_HERSHEY_SCRIPT_SIMPLEX,double(1.4),CV_RGB(200,200,200),2,8,false);
		msg ="";
		
		msg.append( "Tadakuma+Tsumaki Lab");
		cv::putText(image2,msg,cv::Point(20,100),cv::FONT_HERSHEY_PLAIN,double(1.6),CV_RGB(200,200,200),2,8,false);
		msg ="";
		msg.append( "Jose Berengueres");
		cv::putText(image2,msg,cv::Point(20,125),cv::FONT_HERSHEY_PLAIN,double(1.2),CV_RGB(200,200,200),2,8,false);
		msg ="";
		msg.append( "Maid Robo 1.0");
		cv::putText(image2,msg,cv::Point(20,150),cv::FONT_HERSHEY_PLAIN,double(1.2),CV_RGB(200,200,200),2,8,false);
		msg ="";
		msg.append("f: ");
		msg.append( s );
		msg.append( " " );
		//msg.append( jkp );
		cv::putText(image2,msg,cv::Point(20,175),cv::FONT_HERSHEY_PLAIN,double(1.2),CV_RGB(200,200,200),2,8,false);

		//cv::cvtColor(image2, image,1);	
		cv::cvtColor(image2, image,1);	
		camshift->fingers = (int)fingers;
	
}





/**
* マウスイベント処理（コールバック関数）
*/


void
CamshiftDemo::onMouse(int event, int x, int y, int flags, void* param)
{
	IplImage *iplimg;
	CamshiftDemo *camshift = (CamshiftDemo*)param;
	int &select_object = camshift->select_object;
	int &track_object = camshift->track_object;
	cv::Rect &selection = camshift->selection;

	if(camshift->image.empty()) {
		return;
	}

	iplimg = &IplImage(camshift->image);
	cv::Point2i &origin = camshift->origin;
	if(iplimg->origin)
		y = iplimg->height - y;

	/// 選択領域計算（左ドラッグ中）
	if(select_object) {
		selection.x = CV_IMIN(x, origin.x);
        selection.y = CV_IMIN(y, origin.y);
        selection.width = selection.x + CV_IABS(x - origin.x);
        selection.height = selection.y + CV_IABS(y - origin.y);

        selection.x = CV_IMAX(selection.x, 0);
        selection.y = CV_IMAX(selection.y, 0);
        selection.width = CV_IMIN( selection.width, iplimg->width );
        selection.height = CV_IMIN( selection.height, iplimg->height );
        selection.width -= selection.x;
        selection.height -= selection.y;
    }

	/// マウスイベント（左ドラッグによる領域選択）開始・終了
	switch(event) {
    case CV_EVENT_LBUTTONDOWN: // 選択開始
		origin = cv::Point2i(x,y);
		selection = cv::Rect(x,y,0,0);
		select_object = 1;
        break;
    case CV_EVENT_LBUTTONUP: // 選択終了
        select_object = 0;
        if(selection.width > 0 && selection.height > 0)
            track_object = -1;
        break;
    }
}

/**
* コンストラクタ
*/
CamshiftDemo::CamshiftDemo()
#ifdef _USE_ROBOT
:dEnable(1.0), fingersensitivity(45), vmin(10), vmax(256), smin(30), robot(IPADDR),
pan_min(-60), pan_max(60), tilt_min(-30), tilt_max(20)
#else
:dEnable(1.0), vmin(10), vmax(256), smin(30)
#endif
{
	ucam = new uEyeCamera;
	cam_num = ucam->getNumberOfCameras();
	select_object = 0;
	track_object = 0;
	backproject_mode = 0;
	mirror_mode = 0;
	p_mode = 0;
	lose_mode = 0;

}

CamshiftDemo::~CamshiftDemo()
{
#ifdef _USE_ROBOT
  robot.wait();
  robot.servoOFF();
#endif
  ucam->close();
}

/** 
*  画面の表示
*/
void
CamshiftDemo::showImage()
{
	cv::Mat *frame;
	cv::namedWindow("CamShiftDemo", 1);
	cvSetMouseCallback("CamShiftDemo", (CvMouseCallback)(&CamshiftDemo::onMouse), this);
	cv::createTrackbar( "fs", "CamShiftDemo", &fingersensitivity, 256, 0 );
	cv::createTrackbar( "Vmin", "CamShiftDemo", &vmin, 256, 0 );
	cv::createTrackbar( "Vmax", "CamShiftDemo", &vmax, 256, 0 );
	cv::createTrackbar( "Smin", "CamShiftDemo", &smin, 256, 0 );

	cv::Mat hsv(cv::Size(640, 480), CV_8UC3);
	cv::Mat mask(cv::Size(640, 480), CV_8UC1), backproject(cv::Size(640, 480), CV_8UC1);
	cv::Mat histimg = cv::Mat::zeros(cv::Size(320, 200), CV_8UC3);
	cv::MatND hist;
	vector<cv::Mat> planes;
	image = cv::Mat(cv::Size(640, 480), CV_8UC3);
	image2 = cv::Mat(cv::Size(640, 480), CV_8UC3);



	cv::RotatedRect track_box;
#ifdef _USE_ROBOT
	robot.servoON();
#endif

	while(1) {
		// キャプチャ
		frame = &ucam->queryFrame(0);
        if(!frame)
            break;

		frame->copyTo(image);
		frame->copyTo(image2);

		cv::cvtColor(image, hsv, CV_BGR2HSV);

		// トラッキング中 or 選択中
		if(track_object) {
			int _vmin = vmin, _vmax = vmax;
			cv::inRange(hsv, cv::Scalar(0, smin, CV_IMIN(_vmin,_vmax),0),
				cv::Scalar(180, 256, CV_IMAX(_vmin, _vmax), 0), mask);
			cv::split(hsv, planes);

			// 選択終了直後
			if(track_object < 0) {
				// 選択領域のヒストグラム作成
				double min_val = 0.f;
				double max_val = 0.f;
				const int channels[] = {0};
				//int histSize[] = {180};
				int hdims = 180;
				float hranges[] = {0,180};
				const float* ranges[] = {hranges};
				cv::Mat hue_roi(planes[0], selection);
				cv::Mat mask_roi(mask, selection);
				cv::calcHist(&hue_roi, 1, channels, mask_roi, hist, 1, &hdims, ranges, true, false);
				cv::minMaxLoc(hist, &min_val, &max_val);
				//cv::convertScaleAbs(hist, cv::Mat(hist), max_val?255./max_val:0., 0);
				hist.convertTo(hist, hist.type(), max_val?255./max_val:0.,0);
				track_window = selection;
				track_object = 1;

				// ヒストグラム描画
				for(int i=0; i<histimg.cols; i++) {
					int j = static_cast<int>(i*180.0/histimg.cols);
					int val = cv::saturate_cast<int>(hist.at<float>(j)*histimg.rows/255);
					//MyOutputDebugString("hist: depth=%d channels=%d, elemSize=%d, size[0]=%d, val[%d]=%d, rows=%d\n", 
					//hist.depth(), hist.channels(), hist.elemSize(), hist.size[0], 
					//j, cv::saturate_cast<int>(hist.at<float>(j)), histimg.rows);
					int h = int((i*180.0)/(320-1));
					cv::rectangle(histimg, cv::Point(i, 0), cv::Point(i, histimg.rows-val),
						cvScalar(h,255,64,0), -1);
					cv::rectangle(histimg, cv::Point(i, histimg.rows-val), cv::Point(i, histimg.rows),
						cvScalar(h,255,255,0), -1);
				}
				cv::cvtColor(histimg, histimg, CV_HSV2BGR);
			} /* track_object<0 */

			// back-projection
			const int channels[] = {0};
			float hranges[] = {0,180};
			const float* ranges[] = {hranges};
			cv::calcBackProject(&hsv, 1, channels, hist, backproject, ranges);
			cv::bitwise_and(backproject, mask, backproject);
			// camshift
			track_box = cv::CamShift(backproject, track_window, cv::TermCriteria(CV_TERMCRIT_EPS|CV_TERMCRIT_ITER, 10, 1));
			track_box.boundingRect() = track_box.boundingRect() & cv::Rect(0, 0, 640, 480);
			if(ISNAN(track_box.size.width)!=0) track_box.size.width=0;
			if(ISNAN(track_box.size.height)!=0) track_box.size.height=0;
			
			if(backproject_mode)
				cv::cvtColor(backproject, image, CV_GRAY2BGR);			
			// ellipse
			cv::ellipse(image, track_box, CV_RGB(255,0,0), 3, CV_AA);
			// 
			if(mirror_mode)
				cv::flip(image, image, 1);


			if (p_mode)
			{
				game(this);
				findfingers(this);
			}



#ifdef _USE_ROBOT
			// robot
			if((int(track_box.size.width)|int(track_box.size.height))==0) {
				robot.faceTo(0, 0, 60);
				track_window.x = 320;
				track_window.y = 240;
			} else {
				double pan, tilt;
				robot.getNeckAngles(pan, tilt, true);
				int rx = -static_cast<int>((track_box.center.x-320)/20);
				int ry =  static_cast<int>((track_box.center.y-240)/20);
				//robot.faceTo(-rx, ry, 60);
				if(pan>pan_max && rx>0) rx = 0;
				else if(pan<pan_min && rx<0) rx=0;
				if(tilt>tilt_max && ry>0) ry = 0;
				else if(tilt<tilt_min && ry<0) ry = 0;
				//fprintf(stderr,"pan:%.1f, tilt:%.1f, (%d,%d)[%d,%d]\n", pan,tilt,rx,ry, track_box.size.x,track_box.size.y);
				//robot.turnNeck(rx, ry, 50);
			}
#endif

		} /* tracK_object */

		// 選択領域のネガポジ反転
		if(select_object && selection.width > 0 && selection.height > 0) {
			cv::Mat roi(image, selection);
			cv::bitwise_xor(roi, cv::Scalar::all(255), roi);
		}

		if (p_mode)
			cv::imshow("CamShiftDemo", image2);
		else
			cv::imshow("CamShiftDemo", image);
		cv::imshow("Histogram", histimg);
		char key = cv::waitKey(10);
		if(key==27)
			break;
		switch(key) {
			case 'b':
				backproject_mode ^= 1;
				break;
			case 'm':
				mirror_mode ^= 1;
				break;
			case 'p':
				p_mode ^= 1;
				break;
			case 'l':
				lose_mode ^= 1;
				break;


				
		}
	}
	ucam->close();
	PlaySound("C:\\Documents and Settings\\hrpuser\\デスクトップ\\asobo.wav", NULL,  (SND_SYNC|SND_FILENAME));

	cvDestroyWindow("CamShiftDemo");
	cvDestroyWindow("Histogram");
}

/**
* デモプログラムの実行
*/
void
CamshiftDemo::run()
{

// INI
	fingers = 0;
	firstime = true;

// PORT INIT -------------------------------------------------------------
	port_a = open_port_a("COM");
	if(port_a < 0)
		cout << "return -1";
	
	port_b = open_port_b("COM");
	if(port_b < 0)
		cout << "return -1";

	port_c = open_port_c("COM");
	if(port_c < 0)
		cout << "return -1";

	// ポートの設定
	serial_port_a_params(port_a,115200, 8, ONESTOPBIT, NOPARITY);
	serial_port_b_params(port_b,115200, 8, ONESTOPBIT, NOPARITY);
	serial_port_c_params(port_c,115200, 8, ONESTOPBIT, NOPARITY);

	// カメラパラメータの設定
	for(int i=0; i<cam_num; i++) {
		//ucam->setBinning(i, IS_BINNING_4X_VERTICAL, IS_BINNING_4X_HORIZONTAL);		
		//ucam->setImageAOI(i, 0, 0, 640, 480);
		//ucam->setAutoParameter(i, IS_SET_ENABLE_AUTO_GAIN, &dEnable, NULL);
		//ucam->setAutoParameter(i, IS_SET_ENABLE_AUTO_SHUTTER, &dEnable, NULL);
		//ucam->setAutoParameter(i, IS_SET_AUTO_WB_ONCE, &dEnable, NULL);
		//ucam->setAutoParameter(i, IS_SET_ENABLE_AUTO_WHITEBALANCE, &dEnable, NULL);
		ucam->setBinning(i, IS_BINNING_4X_VERTICAL, IS_BINNING_4X_HORIZONTAL);		
		ucam->setImageAOI(i, 0, 0, 640, 480);
		//ucam->setAutoParameter(i, IS_SET_ENABLE_AUTO_GAIN, &dEnable, NULL);
		//ucam->setAutoParameter(i, IS_SET_ENABLE_AUTO_SHUTTER, &dEnable, NULL);
		ucam->setAutoParameter(i, IS_SET_ENABLE_AUTO_WHITEBALANCE, &dEnable, NULL);
		int pr = ucam->setPixelClock(i, 30*2);
		double fps = ucam->setFPS(i, 30.0);
	}
	showImage();
}


/**
* main 関数
*/
int
main(int argc, char *argv[])
{
	CamshiftDemo demo = CamshiftDemo();
	demo.run();

	return 0;
}




// PORTS -----------------------------------

// ポートAに1byte書き込む関数の定義
int CamshiftDemo::port_a_putc(char c, HANDLE port_a){
  char buf = c;

  CamshiftDemo::port_a_write(port_a, &buf, 1);

  return c;
}

// ポートBに1byte書き込む関数の定義
int CamshiftDemo::port_b_putc(char c, HANDLE port_b){
  char buf = c;

  port_b_write(port_b, &buf, 1);

  return c;
}
// ポートCに1byte書き込む関数の定義
int CamshiftDemo::port_c_putc(char c, HANDLE port_c){
  char buf = c;

  port_c_write(port_c, &buf, 1);

  return c;
}

int CamshiftDemo::serial_port_a_params (HANDLE port_a,
			int baudrate, int byte_size,
			int stop_bits, int parity){
  DCB dcb;

  dcb.DCBlength = sizeof(DCB);
  // 設定を読み込む
  GetCommState(port_a, &dcb);
  dcb.BaudRate = baudrate;  // ボーレート
  dcb.ByteSize = byte_size; // ビット長
  dcb.StopBits = stop_bits; // ストップビット
  dcb.Parity = parity; 		// パリティ
  // 設定する
  SetCommState(port_a, &dcb);

  return 1;
}
// ポートBを設定する関数の定義
int CamshiftDemo::serial_port_b_params (HANDLE port_b,
			int baudrate, int byte_size,
			int stop_bits, int parity){
  DCB dcb;

  dcb.DCBlength = sizeof(DCB);
  // 設定を読み込む
  GetCommState(port_b, &dcb);
  dcb.BaudRate = baudrate;  // ボーレート
  dcb.ByteSize = byte_size; // ビット長
  dcb.StopBits = stop_bits; // ストップビット
  dcb.Parity = parity; 		// パリティ
  // 設定する
  SetCommState(port_b, &dcb);

  return 1;
}
// ポートCを設定する関数の定義
int CamshiftDemo::serial_port_c_params (HANDLE port_c,
			int baudrate, int byte_size,
			int stop_bits, int parity){
  DCB dcb;

  dcb.DCBlength = sizeof(DCB);
  // 設定を読み込む
  GetCommState(port_c, &dcb);
  dcb.BaudRate = baudrate;  // ボーレート
  dcb.ByteSize = byte_size; // ビット長
  dcb.StopBits = stop_bits; // ストップビット
  dcb.Parity = parity; 		// パリティ
  // 設定する
  SetCommState(port_c, &dcb);

  return 1;
}



// ポートAから1byte読み込む関数の定義
extern "C" int CamshiftDemo::port_a_getc(HANDLE port_a){
	unsigned char buf;
	size_t s;

	do{
		s = port_a_read(port_a, &buf, 1);
	} while(s < 1);

  return (int)buf;
}


// ポートBから1byte読み込む関数の定義
int CamshiftDemo::port_b_getc(HANDLE port_b){
	unsigned char buf;
	size_t s;

	do{
		s = port_b_read(port_b, &buf, 1);
	} while(s < 1);

  return (int)buf;
}
// ポートCから1byte読み込む関数の定義
int CamshiftDemo::port_c_getc(HANDLE port_c){
	unsigned char buf;
	size_t s;

	do{
		s = port_c_read(port_c, &buf, 1);
	} while(s < 1);

  return (int)buf;
}



size_t CamshiftDemo::port_a_write(HANDLE port_a, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port_a, buf, nbytes, &num, NULL);
    return (size_t)num;
}

// ポートBに書き込む関数の定義
size_t CamshiftDemo::port_b_write(HANDLE port_b, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port_b, buf, nbytes, &num, NULL);
    return (size_t)num;
}
// ポートCに書き込む関数の定義
size_t CamshiftDemo::port_c_write(HANDLE port_c, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port_c, buf, nbytes, &num, NULL);
    return (size_t)num;
}


// ポートAから読み込む関数の定義
size_t CamshiftDemo::port_a_read(HANDLE port_a, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port_a, buf, nbytes, &num, NULL);
  return (size_t)num;
}
// ポートBから読み込む関数の定義
size_t CamshiftDemo::port_b_read(HANDLE port_b, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port_b, buf, nbytes, &num, NULL);
  return (size_t)num;
}
// ポートCから読み込む関数の定義
size_t CamshiftDemo::port_c_read(HANDLE port_c, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port_c, buf, nbytes, &num, NULL);
  return (size_t)num;
}

extern "C" HANDLE CamshiftDemo::open_port_a(char name[]){
	HANDLE port_a;

	const char* c = name;

	// ポートを開く
	port_a = CreateFileA(
	  "COM9",								// 通信デバイスの名前のアドレス //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//アクセス (読み取りおよび書き込み) モード //
	  0,								// 共有モード //
	  NULL,								// セキュリティ記述子のアドレス //
	  OPEN_EXISTING,					// 作成方法 //
	  0,								// ファイル属性 //
	  NULL);							// コピーする属性付きファイルのハンドル //
	if(port_a == INVALID_HANDLE_VALUE){
		// ポートが開けなかった
		fprintf(stderr, "Serial port 9 (%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_a;
}

extern "C" HANDLE CamshiftDemo::open_port_b(char name[]){
	HANDLE port_b;

	const char* c = name;

	// ポートを開く
	port_b = CreateFileA(
	  "\\\\.\\COM12",								// 通信デバイスの名前のアドレス //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//アクセス (読み取りおよび書き込み) モード //
	  0,								// 共有モード //
	  NULL,								// セキュリティ記述子のアドレス //
	  OPEN_EXISTING,					// 作成方法 //
	  0,								// ファイル属性 //
	  NULL);							// コピーする属性付きファイルのハンドル //
	if(port_b == INVALID_HANDLE_VALUE){
		// ポートが開けなかった
		fprintf(stderr, "Serial port 12 (%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_b;
}

extern "C" HANDLE CamshiftDemo::open_port_c(char name[]){
	HANDLE port_c;

	const char* c = name;

	// ポートを開く
	port_c = CreateFileA(
	  "\\\\.\\COM10",								// 通信デバイスの名前のアドレス //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//アクセス (読み取りおよび書き込み) モード //
	  0,								// 共有モード //
	  NULL,								// セキュリティ記述子のアドレス //
	  OPEN_EXISTING,					// 作成方法 //
	  0,								// ファイル属性 //
	  NULL);							// コピーする属性付きファイルのハンドル //
	if(port_c == INVALID_HANDLE_VALUE){
		// ポートが開けなかった
		fprintf(stderr, "Serial port10 (%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_c;
}



extern "C" void CamshiftDemo::fingermoveABC(char ma[],char mb[],char mc[], HANDLE port_a, HANDLE port_b, HANDLE port_c)
{

	char tx = 'a';
	port_a_putc(tx, port_a);

	port_a_putc(ma[0], port_a);
	port_a_putc(ma[1], port_a);
	port_a_putc(ma[2], port_a);
	port_a_putc(ma[3], port_a);
	port_a_putc(ma[4], port_a);
	port_a_putc(ma[5], port_a);
	port_a_putc(ma[6], port_a);
	port_a_putc(ma[7], port_a);


	//TX[0] = ;
	port_b_putc('a', port_b);
	
	port_b_putc(mb[0], port_b);
	port_b_putc(mb[1], port_b);
	port_b_putc(mb[2], port_b);
	port_b_putc(mb[3], port_b);
	port_b_putc(mb[4], port_b);
	port_b_putc(mb[5], port_b);
	port_b_putc(mb[6], port_b);
	port_b_putc(mb[7], port_b);

	
	//TX[0] = ;
	port_c_putc('a', port_c);
	
	port_c_putc(mc[0], port_c);
	port_c_putc(mc[1], port_c);
	port_c_putc(mc[2], port_c);
	port_c_putc(mc[3], port_c);
	port_c_putc(mc[4], port_c);
	port_c_putc(mc[5], port_c);
	port_c_putc(mc[6], port_c);
	port_c_putc(mc[7], port_c);

    //encoder_data_get_fnc(port_c);

return;
}



extern "C" void CamshiftDemo::encoder_data_get_fnc(HANDLE port){
	//HANDLE port;
	char encoder_data_TX[32];
	char encoder1_data_RX[32];
	char encoder2_data_RX[32];

	//データ送信//
	encoder_data_TX[0] = 'e';
	port_putc(encoder_data_TX[0], port);
	//printf("TX[0]=%c\r\n",TX[0]);

	//データ受信//
	//if((char)port_getc(port)==)
	encoder1_data_RX[0] = (char)CamshiftDemo::port_getc(port);
	encoder1_data_RX[1] = (char)CamshiftDemo::port_getc(port);
	encoder1_data_RX[2] = (char)CamshiftDemo::port_getc(port);
	encoder1_data_RX[3] = (char)CamshiftDemo::port_getc(port);
	unsigned int enc_1 = (unsigned int)strtol(encoder1_data_RX, 0, 16);
	//printf("encoder1=%c%c%c%c\n", encoder_data_RX[0], encoder_data_RX[1],encoder_data_RX[2],encoder_data_RX[3]);
	printf("encoder1=%x ", enc_1);

	encoder2_data_RX[0] = (char)CamshiftDemo::port_getc(port);
	encoder2_data_RX[1] = (char)CamshiftDemo::port_getc(port);
	encoder2_data_RX[2] = (char)CamshiftDemo::port_getc(port);
	encoder2_data_RX[3] = (char)CamshiftDemo::port_getc(port);
	unsigned int enc_2 = (unsigned int)strtol(encoder2_data_RX, 0, 16);
	//printf("encoder1=%c%c%c%c\n", encoder_data_RX[0], encoder_data_RX[1],encoder_data_RX[2],encoder_data_RX[3]);
	printf("encoder2=%x \n", enc_2);



}

extern "C" void CamshiftDemo::encoder_re_init_fnc(char init_1[8],char init_2[8],HANDLE port){
	char encoder_init_TX[32];
//	char encoder_init_RX[32];

	//mode data 送信//
	encoder_init_TX[0] = 'i';
	port_putc(encoder_init_TX[0], port);

	// 初期化用 encoder1 data 送信 //
	encoder_init_TX[1] = init_1[0];
	encoder_init_TX[2] = init_1[1];
	encoder_init_TX[3] = init_1[2];
	encoder_init_TX[4] = init_1[3];
	port_putc(encoder_init_TX[1], port);
	port_putc(encoder_init_TX[2], port);
	port_putc(encoder_init_TX[3], port);
	port_putc(encoder_init_TX[4], port);

	// 初期化用 encoder2 data 送信 //
	encoder_init_TX[5] = init_2[0];
	encoder_init_TX[6] = init_2[1];
	encoder_init_TX[7] = init_2[2];
	encoder_init_TX[8] = init_2[3];
	port_putc(encoder_init_TX[5], port);
	port_putc(encoder_init_TX[6], port);
	port_putc(encoder_init_TX[7], port);
	port_putc(encoder_init_TX[8], port);
}

extern "C" int CamshiftDemo::port_putc(char c, HANDLE port){
  char buf = c;

  CamshiftDemo::port_write(port, &buf, 1);

  return c;
}

extern "C" int CamshiftDemo::port_getc(HANDLE port){
	unsigned char buf;
	size_t s;

	do{
		s = CamshiftDemo::port_read(port, &buf, 1);
	} while(s < 1);

  return (int)buf;
}

extern "C" size_t CamshiftDemo::port_write(HANDLE port, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port, buf, nbytes, &num, NULL);
    return (size_t)num;
}

// ポートから読み込む関数の定義
extern "C" size_t CamshiftDemo::port_read(HANDLE port, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port, buf, nbytes, &num, NULL);
  return (size_t)num;
}