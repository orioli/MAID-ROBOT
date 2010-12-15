・はじめに

- このREADME.txtは，uEyeCameraのキャプチャに関するものであり，ロボット
  コントロールに関しては別途 classLib/00memo.txtを参照すること


・ディレクトリ構成

uEyeCameraHIRO
|-- camShiftDemo：camShiftのデモ
|   `-- Release
|-- classLib：HIROコントロールのためのライブラリ
|   |-- Debug
|   |-- Release：ロボット動作に関するライブラリが作成される
|   |-- idls
|   `-- test0
|       `-- Release
|-- stereoCaptureDemo：ステレオカメラキャプチャのデモ
|   `-- Release
|-- uEyeCamPy：uEyeCameraのPythonインタフェース
|   `-- Release
`-- uEyeCamera：uEyeCameraキャプチャライブラリ
    |-- Debug
    |-- Release：uEyeCameraライブラリ，サンプルなどの全バイナリが作成される (windows)
    `-- bin：uEyeCameraライブラリ，サンプルなどの全バイナリが作成される (linux)


・メソッド（Pythonインタフェース関数）一覧
- ++++++++++ 初期化 ++++++++++++
  uEyeCamera, (--)
    * コンストラクタ
  -- (uEyeCam.CaptureFromUEYE)
    * キャプチャ構造体の初期化 

- ++++++++++ キャプチャ ++++++++++++
  queryFrame, (uEyeCam.QueryFrame)
    * 次のフレームをキャプチャ

- ++++++++++ 設定 ++++++++++++
  setImageSize, (uEyeCam.SetImageSize)
    * キャプチャフレーム位置の設定（左上コーナー）
  setImagePos, (uEyeCam.SetImagePos)
    * キャプチャフレームサイズの設定
  setImageAOI, (uEyeCam.SetImageAOI)
    * キャプチャのAOI（Size＋Pos）設定：これがあれば上記2つは不要…
  setSubSampling, (uEyeCam.SetSubSampling)
    * SubSamplingの設定
  setBinning, (uEyeCam.SetBinning)
    * Binningの設定
  setAutoParameter, (uEyeCam.SetAutoParameter)
    * Autoパラメータの設定（Autoゲイン，Autoシャッタースピードなど）
  getFPS, (uEyeCam.GetFPS)
    * 現在のFPSを取得
  setFPS, (uEyeCam.SetFPS)
    * FPSを設定
  setPixelClock, (uEyeCam.SetPixelClock)
    * ピクセル読み込みの周期（MHz）を設定
  saveParameter, (uEyeCam.SaveParameter)
    * カメラ設定の保存
  loadParameter, (uEyeCam.LoadParameter)
    * カメラ設定の読み込み


・動作確認環境

- windowsXP(SP3)
- ubuntu8.04(2.6.24-21)
  -- kernel 2.6.25 以降はドライバが存在しないため未対応
- classLibに必要なライブラリ + openCV,openCVが依存するライブラリが必要
- uEyeCameraのドライバに付属するサンプルをコンパイルする場合にはQtが必要(linux)


・インストール

1. classLibのコンパイル（classLib/00memo.txtを参照）
2. openCV2.0のインストール
   2.1 cmakeのインストール
   2.2 openCV2.0のコンパイル (PYTHON_SUPPORT=ON(linux),
       new_python_interface (windows)
3. uEyeカメラのドライバインストール http://www.ids-imaging.com/drivers.php?cat=2
   a. uEye32_34000.zip (windows)
   b. uEye_Linux_3.25.00.zpi (linux)
4. uEyeCamera, uEyeCamPy, サンプルのコンパイル
   a. uEyeCamera/uEyeCamera.sln (windows)
   b. uEyeCamera/Makefile (linux)


・サンプルプログラムの動作

- stereoCaptureDemo[.exe], stereoCaptureDemo.py
  -- 起動すると自動的にカメラキャプチャ，表示を行う．必ず2台のカメラを
     接続してから実行すること．Escキーで終了する．
- camShiftDemo[.exe], camShiftDemo.py
  -- 起動するとキャプチャ画像が表示されるので，その画面上でトラッキン
  グしたい物体領域をドラッグして選択．選択後は自動的にトラッキングとロ
  ボット頭部の制御が開始される．Escキーで終了する．"b"キーで，バックプ
  ロジェクションを表示する．


・コンパイルに関して

- OpenCV(linux)
  -- cd OpenCV-2.0.0
  -- mkdir release && cd release
  -- cmake -D CMAKE_BUILD_TYPE=RELEASE -D \
    CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_PYTHON_SUPPORT=ON -D \
    BUILD_EXAMPLES=ON ..
  -- make && make install 
- OpenCV(windows)
  -- ビルド用ディレクトリ作成 (ex. release)
  -- cmake configure & generate (vs2008 Express の場合は OpenMP OFF)
  -- opencv.sln からビルド
- OpenCV2.0 がサポートするpythonは，2.5以降
- pythonのデバッグバイナリが存在しない場合は, それに依存するバイナリは
  作成できない（classLibも同様）


・その他

- uEyeCameraサンプルを動作させる前に，必ずロボットのキャリブレーション
  が必要！！
- uEyeCameraライブラリは、uEyeCameraのAPIの一部を利用したものなので，
  更に細かい制御が必要な場合は，ドライバに付属のAPIマニュアル（pdf）を
  参照すること
- setAutoParameterで設定できるパラメータ名（IS_SET_ENABLE_AUTO_GAIN,
  IS_SET_AUTO_WB_ONCE, など）に関しても上記マニュアルを参照すること
  -- IS_SET_ENABLE_AUTO_GAIN
  -- IS_SET_ENABLE_AUTO_SHUTTER
  -- IS_SET_ENABLE_AUTO_WHITEBALANCE
  -- IS_SET_AUTO_WB_ONCE
- LinuxのMakeで，pythonのサンプルコードは uEyeCamera/Release/*.py を
  uEyeCamera/bin/ にコピーしているだけなので注意すること（片方を編集
  しても他方は変更されない）．
