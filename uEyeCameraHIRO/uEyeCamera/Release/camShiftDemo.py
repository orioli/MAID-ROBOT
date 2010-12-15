#!/usr/bin/env python
#-*- coding: utf-8 -*-

import cv
import uEyeCam as uc
import sys
import KSP

def is_rect_nonzero(r):
    (_,_,w,h) = r
    return (w > 0) and (h > 0)
        
class CamShiftDemo:
    vmin, vmax, smin = 10, 256, 40
    drag_start, track_window, selection = None, None, None

    @classmethod
    def track_vmin(cls, p):
        cls.vmin = p
    @classmethod
    def track_vmax(cls, p):
        cls.vmax = p
    @classmethod
    def track_smin(cls, p):
        cls.smin = p
    @classmethod
    def on_mouse(cls, event, x, y, flags, param):
        """ マウスイベント """
        if event == cv.CV_EVENT_LBUTTONDOWN:
            cls.drag_start = (x, y)
        if event == cv.CV_EVENT_LBUTTONUP:
            cls.drag_start = None
            cls.track_window = cls.selection
        if cls.drag_start:
            xmin = min(x, cls.drag_start[0])
            ymin = min(y, cls.drag_start[1])
            xmax = max(x, cls.drag_start[0])
            ymax = max(y, cls.drag_start[1])
            cls.selection = (xmin, ymin, xmax - xmin, ymax - ymin)

    def __init__(self):
        """ コンストラクタ """
        self.robot = KSP.Robot("192.168.128.3")
        self.neck = KSP.dblArray(2)
        self.move = False
        ## ウィンドウ作成
        cv.NamedWindow( "CamShiftDemo", 1 )
        cv.NamedWindow( "Histogram", 1 )
        cv.SetMouseCallback( "CamShiftDemo", self.on_mouse)
        cv.CreateTrackbar("Vmin", "CamShiftDemo", self.vmin, 256, self.track_vmin)
        cv.CreateTrackbar("Vmax", "CamShiftDemo", self.vmax, 256, self.track_vmax)
        cv.CreateTrackbar("Smin", "CamShiftDemo", self.smin, 256, self.track_smin)

        ## キャプチャパラメータ設定
        self.cams = [0]
        self.width, self.height = 320, 240
        self.cap = uc.CaptureFromUEYE()
        uc.SetBinning(self.cap, self.cams, (uc.IS_BINNING_4X_VERTICAL, uc.IS_BINNING_4X_HORIZONTAL))
        uc.SetImageAOI(self.cap, self.cams, (160, 120, self.width, self.height))
        #uc.SetAutoParameter(self.cap, self.cams, (uc.IS_SET_ENABLE_AUTO_GAIN, 1.0, 0.0))
        #uc.SetAutoParameter(self.cap, self.cams, (uc.IS_SET_ENABLE_AUTO_SHUTTER, 1.0, 0.0))
        #uc.SetAutoParameter(self.cap, self.cams, (uc.IS_SET_AUTO_WB_ONCE, 1.0, 0.0))
        uc.SetAutoParameter(self.cap, self.cams, (uc.IS_SET_ENABLE_AUTO_WHITEBALANCE, 1.0, 0.0))

        print( "Keys:\n"
            "    ESC - quit the program\n"
            "    b - switch to/from backprojection view\n"
            "To initialize tracking, drag across the object with the mouse\n" )

    def hue_histogram_as_image(self, hist):
        """ 色相のヒストグラム->ヒストグラム画像 """
        histimg_hsv = cv.CreateImage((320,200), 8, 3)
        mybins = cv.CloneMatND(hist.bins)
        cv.Log(mybins, mybins)
        (_, hi, _, _) = cv.MinMaxLoc(mybins)
        cv.ConvertScale(mybins, mybins, 255. / hi) ## ビンの値を0-255に正規化

        w, h = cv.GetSize(histimg_hsv)
        hdims = cv.GetDims(mybins)[0]
        for x in range(w):
            xh = (180 * x) / (w - 1)  ## x軸を0-180[deg]に正規化
            val = int(mybins[int(hdims * x / w)] * h / 255)
            cv.Rectangle( histimg_hsv, (x, 0), (x, h-val), (xh,255,64), -1)
            cv.Rectangle( histimg_hsv, (x, h-val), (x, h), (xh,255,255), -1)

        histimg = cv.CreateImage((320,200), 8, 3)
        cv.CvtColor(histimg_hsv, histimg, cv.CV_HSV2BGR)
        return histimg

    def run(self):
        """ デモ実行 """
        ## ヒストグラム作成
        hist = cv.CreateHist([180], cv.CV_HIST_ARRAY, [(0,180)], 1)
        backproject_mode = False
        ## widthStep の計算
        frame1 = uc.QueryFrame(self.cap, self.cams)
        widthStep = len(frame1)/self.height
        frame = cv.CreateImage((self.width, self.height), cv.IPL_DEPTH_8U, 3)
        self.robot.servoON()
        
        while 1:
            ## 画像キャプチャ
            frame1 = uc.QueryFrame(self.cap, self.cams)
            cv.SetData(frame, frame1, widthStep)

            ## HSVに変換後，H（色相）だけ取り出す
            _vmin, _vmax, _smin = self.vmin, self.vmax, self.smin
            hsv = cv.CreateImage(cv.GetSize(frame), 8, 3)
            cv.CvtColor(frame, hsv, cv.CV_BGR2HSV)
            self.hue = cv.CreateImage(cv.GetSize(frame), 8, 1)
            mask = cv.CreateImage(cv.GetSize(frame), 8, 1)
            cv.InRangeS(hsv, (0, _smin, min(_vmin,_vmax),0),
                        (180,256, max(_vmin,_vmax),0), mask)
            cv.Split(hsv, self.hue, None, None, None)

            ## back-projection   
            backproject = cv.CreateImage(cv.GetSize(frame), 8, 1)
            cv.CalcArrBackProject([self.hue], backproject, hist)
            cv.And(backproject, mask, backproject)
            ## cam-shift
            if self.track_window and is_rect_nonzero(self.track_window):
                crit = (cv.CV_TERMCRIT_EPS | cv.CV_TERMCRIT_ITER, 30, 0.2)
                (iters, (area, value, rect), track_box) = cv.CamShift(backproject, self.track_window, crit)
                self.track_window = rect

            ## マウスドラッグ：矩形のハイライト，ヒストグラムの再計算
            if self.drag_start and is_rect_nonzero(self.selection):
                sub = cv.GetSubRect(frame, self.selection)
                sub_mask = cv.GetSubRect(mask, self.selection)
                save = cv.CloneMat(sub)
                cv.ConvertScale(frame, frame, 0.5)
                cv.Copy(save, sub)
                x,y,w,h = self.selection
                cv.Rectangle(frame, (x,y), (x+w,y+h), (255,255,255))

                sel = cv.GetSubRect(self.hue, self.selection)
                cv.CalcArrHist( [sel], hist, 0, sub_mask)
                (_, max_val, _, _) = cv.GetMinMaxHistValue(hist)
                if max_val != 0:
                    cv.ConvertScale(hist.bins, hist.bins, 255. / max_val)
            ## トラッキング：楕円描画，ロボット頭部動作        
            elif self.track_window and is_rect_nonzero(self.track_window):
                if track_box[0][0]!=track_box[0][0]:track_box[0][0]=0
                if track_box[0][1]!=track_box[0][1]:track_box[0][1]=0
                if track_box[1][0]!=track_box[1][0]:track_box[1][0]=0
                if track_box[1][1]!=track_box[1][1]:track_box[1][1]=0
                #print track_box
                self.robot.getNeckAngles(self.neck)
                cv.EllipseBox( frame, track_box, cv.CV_RGB(255,0,0), 3, cv.CV_AA, 0 )
                pan, tilt = self.neck[0], self.neck[1]
                rx, ry = -(track_box[0][0]/2-80)/20, (track_box[0][1]/2-60)/20
                self.robot.faceTo(x, y, 50)
                if pan>60 and rx>0:     rx=0
                elif pan<-60 and rx<0:  rx=0
                if tilt>20 and ry>0:    ry=0
                elif tilt<-50 and ry<0: ry=0
                #self.robot.turnNeck(rx, ry, 50)
                if rx!=0 or ry!=0: self.move = True
                else: self.move = False

            ## 画像の表示（キャプチャ画像 or backprojection）
            if not backproject_mode:
                cv.ShowImage("CamShiftDemo", frame)
            else:
                cv.ShowImage("CamShiftDemo", backproject)
            cv.ShowImage("Histogram", self.hue_histogram_as_image(hist))
            if self.move: 
                self.robot.turnNeck(rx, ry, 50)

            ## キーイベントの処理
            c = cv.WaitKey(10)
            c = c&~0x100000 ## ...
            if c == 27:
                cv.DestroyWindow("CamShiftDemo")
                cv.DestroyWindow("Histogram")
                self.robot.servoOFF()
                break
            elif c == ord('b'):
                backproject_mode = not backproject_mode

if __name__=="__main__":
    demo = CamShiftDemo()
    demo.run()
