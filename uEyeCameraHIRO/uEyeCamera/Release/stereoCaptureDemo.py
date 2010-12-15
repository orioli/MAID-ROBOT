#!/usr/bin/env python
#-*- coding: utf-8 -*-

import uEyeCam as uc
import cv
import sys

class StereoCaptureDemo:

    def __init__(self, r=[0,0,640,480], l=[0,0,640,480]):
        """ コンストラクタ """
        self.cap = uc.CaptureFromUEYE()
        self.cams = [0,1]
        cv.NamedWindow("img_win1",1)
        cv.NamedWindow("img_win2",1)
        self.right = {"x":r[0], "y":r[1], "width":r[2], "height":r[3]}
        self.left  = {"x":l[0], "y":l[1], "width":l[2], "height":l[3]}
        
    def setImageAOI(self, x, y, w, h):
        """ AOI設定 """
        self.x, self.y, self.width, self.height = x, y, w, h
        uc.SetImageAOI(self.cap, self.cams, (x, y, w, h))
        self.imgR = cv.CreateImage((w, h), cv.IPL_DEPTH_8U, 3)
        self.imgL = cv.CreateImage((w, h), cv.IPL_DEPTH_8U, 3)

    def setBinning(self, binx, biny):
        """ Binning設定 """
        uc.SetBinning(self.cap, self.cams, (binx, biny))

    def setSubSampling(self, modex, modey):
        """ SubSampling設定 """
        uc.SetSubSampling(self.cap, self.cams, (modex, modey))

    def setAutoParameter(self, param, val1, val2):
        """ AUTOパラメータ設定 """
        uc.SetAutoParameter(self.cap, self.cams, (param, val1, val2))

    def saveParameter(self, filename):
        """ パラメータ保存 """
        uc.SaveParameter(self.cap, self.cams, filename)

    def loadParameter(self, filename):
        """ パラメータ読み込み """
        uc.LoadParameter(self.cap, self.cams, filename)

    def setPixelClock(self, pclock):
        """ PixelClockの設定 """
        uc.SetPixelClock(self.cap, self.cams, 60)

    def setFPS(self, fps):
        """ FPSの設定 """
        return uc.SetFPS(self.cap, self.cams, fps)

    def getFPS(self):
        """ FPSの取得 """
        return uc.GetFPS(self.cap, self.cams)
        
    def showImage(self):
        """ 表示 """
        ## widthStep の計算
        frame1, frame2 = uc.QueryFrame(self.cap, self.cams)
        widthStep1 = len(frame1)/self.right["height"]
        widthStep2 = len(frame2)/self.left["height"]
        c=0
        while 1:
            ## キャプチャ
            frame1, frame2 = uc.QueryFrame(self.cap, self.cams)
            cv.SetData(self.imgR, frame1, widthStep1)
            cv.SetData(self.imgL, frame2, widthStep2)
            cv.ShowImage("img_win1", self.imgR)
            cv.ShowImage("img_win2", self.imgL)
            key = cv.WaitKey(10)
            ## キーイベント処理
            if key&~0x100000==27:
                cv.DestroyWindow("img_win1")
                cv.DestroyWindow("img_win2")
                break;
            elif c>100:
                #print "getFPS", self.getFPS()
                c=0
            c += 1
    def run(self):
        """ デモ実行 """
        self.setBinning(uc.IS_BINNING_4X_VERTICAL, uc.IS_BINNING_4X_HORIZONTAL)
        #self.setSubSampling(uc.IS_SUBSAMPLING_4X_VERTICAL, uc.IS_SUBSAMPLING_4X_HORIZONTAL)
        self.setImageAOI(0, 0, 640, 480)
        self.setAutoParameter(uc.IS_SET_ENABLE_AUTO_GAIN, 1.0, 0.0)
        #self.setAutoParameter(uc.IS_SET_ENABLE_AUTO_SHUTTER, 1.0, 0.0)
        #self.setAutoParameter(uc.IS_SET_ENABLE_AUTO_WHITEBALANCE, 1.0, 0.0)
        self.setPixelClock(60)
        self.setFPS(30.0)
        self.showImage()

if __name__=="__main__":
    sc = StereoCaptureDemo()
    sc.run()

