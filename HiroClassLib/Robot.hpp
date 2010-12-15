/*!
 *  @file
 *  @~japanese
 *  @brief ロボット制御クラスライブラリ
 *  @~english
 *  @brief the main source code of the library for controling hiro
 */

#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include <iostream>
#include <string>
#include "systemCommand.hpp"
#include "statusPlugin.hpp"
#include "armServer.hpp"
#include "coordServer.hpp"
#include "dioPlugin.hpp"

namespace KSP {

  const int NECK  = statusPluginTypes::PART_NECK;   // 0x02;
  const int CHEST = statusPluginTypes::PART_CHEST;  // 0x01;
  const int RARM  = statusPluginTypes::PART_RARM;	// 0x04;
  const int LARM  = statusPluginTypes::PART_LARM;	// 0x08;
  const int WHOLE = 0xff;

#ifdef _WIN32
#define DRARM  (0x04)
#define DLARM  (0x08)
#else
#define DRARM  (RARM)
#define DLARM  (LARM)
#endif

  const int DOFS_WHOLE = 15;
  const int DOFS_ARM   =  6;
  const int DOFS_NECK  =  2;
  const int DOFS_CHEST =  1;

  const int COMPLEMENTBY_ANGLE = 0;
  const int COMPLEMENTBY_LINE  = 1;

  /*!
   * @~japanese
   * @brief ロボットの腕を抽象化したクラス。Robotクラスのメンバ。
   * @~english
   * @brief The class which represent robot arm for manipurating. The member of the class Robot.
   */
  class Arm {
    friend class Robot;
  private:
    int block;
    armServer_var arm;
  private:
    Arm(int block);
    virtual ~Arm();
    void connect(armServer_var arm);
    
  public:
    int speed;
	/*!
	 * @brief 対応する腕のデフォルトの動作速度をパーセントで指定します。
	 *        ロボットの他の部位の速度には影響を与えません。
	 * @param speed パーセントで指定する動作速度[%]。
	 *        最大速度に対するパーセント値となります（@c 100 = 最大速度 )。
	 */ 
    void setDefaultSpeed(int speed);

	/*!
	 * @brief      対応する腕の関節角度を取得します。
	 * @param[in]  angles   取得した関節角度が格納されます[deg]。
	 * @param[out] realFlag 取得する関節角度が実際の角度か指令角度かを指定します。
	 *                 - true : 実際の関節角度を返します。
	 *                 - false : 指令関節角度を返します。
	 */ 
    void getAngles(double angles[], bool realFlag=false);

	/*!
	 * @brief      対応する腕を指定角度(配列で与える)まで動かします。
	 * @param[out] angles  腕の関節角度を指定します[deg]。
	 * @param[in]  speed   speed パーセントで指定する動作速度[%]。
	 */ 
    unsigned long makePose(const double angles[], int speed=-1);

	/*!
	 * @brief     対応する腕を指定角度まで動かします。
	 * @param[in] j0    腕の1番目の関節角度を指定します[deg]。
	 * @param[in] j1    腕の2番目の関節角度を指定します[deg]。
	 * @param[in] j2    腕の3番目の関節角度を指定します[deg]。
	 * @param[in] j3    腕の4番目の関節角度を指定します[deg]。
	 * @param[in] j4    腕の5番目の関節角度を指定します[deg]。
	 * @param[in] j5    腕の6番目の関節角度を指定します[deg]。
	 * @param[in] speed speed パーセントで指定する動作速度[%]。
	 * @return          成功したら0を返す。
	 */ 
    unsigned long makePose(double j0, double j1, double j2,
			   double j3, double j4, double j5, int speed=-1);

	/*!
	 * @brief           対応する肩と肘の関節を指定角度分だけ動かします。
	 * @param[in] j0    腕の1番目の関節角度を指定します[deg]。
	 * @param[in] j1    腕の2番目の関節角度を指定します[deg]。
	 * @param[in] j2    腕の3番目の関節角度を指定します[deg]。
	 * @param[in] speed speed パーセントで指定する動作速度[%]。
	 * @return          成功したら0を返す。
	 */ 
    unsigned long moveUpper(double j0, double j1, double j2, int speed=-1);

	/*!
	 * @brief     対応する肩と肘の関節を指定角度[degree]まで動かします。
	 * @param[in] j0    腕の1番目の関節角度の移動量[degree]指定します。
	 * @param[in] j1    腕の2番目の関節角度を指定します[degree]。
	 * @param[in] j2    腕の3番目の関節角度を指定します[degree]。
	 * @param[in] speed speed パーセントで指定する動作速度[%]
	 * @return          成功したら0を返す。
	 */ 
    unsigned long moveUpperTo(double j0, double j1, double j2, int speed=-1);

	/*!
	 * @brief     手首の3軸を指定角度分動かす。
	 * @param[in] j3    腕の3番目の関節角度の移動量[deg]指定します。
	 * @param[in] j4    腕の4番目の関節角度を指定します[deg]。
	 * @param[in] j5    腕の5番目の関節角度を指定します[deg]。
	 * @param[in] speed speed パーセントで指定する動作速度[%]。
	 * @return          成功したら0を返す。
	 */ 
    unsigned long moveFore(double j3, double j4, double j5, int speed=-1);

	/*!
	 * @brief     手首の3軸を指定角度まで動かす。
	 * @param[in] j3    腕の3番目の関節角度の移動量[deg]指定します。
	 * @param[in] j4    腕の4番目の関節角度を指定します[deg]。
	 * @param[in] j5    腕の5番目の関節角度を指定します[deg]。
	 * @param[in] speed speed パーセントで指定する動作速度[%]。
	 * @return          成功したら0を返す。
	 */ 
    unsigned long moveForeTo(double j3, double j4, double j5, int speed=-1);

	/*!
	 * @brief       現在動作中の動作が完了するまで待つ。
	 */ 
    void wait(void);
  };

  /*!
   * @brief ロボットのエンドエフェクタを抽象化したクラス。Robotクラスのメンバ。
   */
  class Hand {
    friend class Robot;
  private:
    int block;
    armServer_var arm;
    coordServer_var coord;
  private:
    Hand(int block);
    virtual ~Hand();
    void connect(armServer_var arm, coordServer_var coord);

  public:
    int speed;
    void setDefaultSpeed(int speed);
    int complementType;
    void setDefaultComplementType(int cType);
    

    /*!
     * @brief     手先の位置と姿勢を取得します。
     * @param[out] coord    取得した手先の位置と姿勢が格納されます。
     */ 
    void getCoord(double coord[6]);

    /*!
     * @brief     正面座標系から見たターゲットの位置と姿勢を取得します。
     * @param[in]  offset   ハンド座標系でのターゲットの位置と姿勢を指定します。
     * @param[out] coord    取得したターゲットの正面座標系での位置と姿勢が格納されます。
     */ 
    void getCoord(double offset[6], double coord[6]);

    /*!
     * @brief     手先の位置を指定量だけ動かす。
     * @param[in] xyz    手先の正面座標系での移動量[mm]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @param[in] cType  cType 補間方法を指定する。
     * @return           成功したら0を返す。
     */ 
    unsigned long move(double xyz[3], int speed=-1, int cType=-1);

    /*!
     * @brief     手先の位置を指定量だけ動かす。
     * @param[in] x      正面座標系でのX軸の移動量[mm]を指定します。
     * @param[in] y      正面座標系でのY軸の移動量[mm]を指定します。
     * @param[in] z      正面座標系でのZ軸の移動量[mm]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @param[in] cType  cType 補間方法を指定する。
     * @return           成功したら0を返す。
     */ 
    unsigned long move(double x, double y, double z, int speed=-1, int cType=-1);

    /*!
     * @brief     手先の位置を指定位置まで動かす。
     * @param[in] xyz    正面座標系での位置[mm]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @param[in] cType  cType 補間方法を指定する。
     * @return           成功したら0を返す。
     */ 
    unsigned long moveTo(double xyz[3], int speed=-1, int cType=-1);

    /*!
     * @brief     手先の位置を指定位置まで動かす。
     * @param[in] x      正面座標系でのX軸の位置[mm]を指定します。
     * @param[in] y      正面座標系でのY軸の位置[mm]を指定します。
     * @param[in] z      正面座標系でのZ軸の位置[mm]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @param[in] cType  cType 補間方法を指定する。
     * @return           成功したら0を返す。
     */ 
    unsigned long moveTo(double x, double y, double z, int speed=-1, int cType=-1);

    /*!
     * @brief     手先の姿勢だけを初期姿勢に戻す。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @param[in] cType  cType 補間方法を指定する。
     * @return           成功したら0を返す。
     */ 
    unsigned long resetPose(int speed=-1, int cType=-1);

    /*!
     * @brief     手先の姿勢を指定量だけ動かす。
     * @param[in] rpy    手先の正面座標系での移動量Roll/Pitch/Yaw[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @param[in] cType  cType 補間方法を指定する。
     * @return           成功したら0を返す。
     */ 
    unsigned long turn(double rpy[3], int speed=-1, int cType=-1);

    /*!
     * @brief     手先の姿勢を指定量だけ動かす。
     * @param[in] r      手先の正面座標系でのRoll軸の移動量[deg]を指定します。
     * @param[in] p      手先の正面座標系でのPitch軸の移動量[deg]を指定します。
     * @param[in] y      手先の正面座標系でのYaw軸の移動量[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @param[in] cType  cType 補間方法を指定する。
     * @return           成功したら0を返す。
     */ 
    unsigned long turn(double r, double p, double y, int speed=-1, int cType=-1);

    /*!
     * @brief     手先の姿勢(x-y-z系オイラー角)を指定した角度まで動かす。
     * @param[in] rpy    手先の正面座標系でのオイラー角Roll/Pitch/Yaw[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @param[in] cType  cType 補間方法を指定する。
     * @return           成功したら0を返す。
     */ 
    unsigned long turnTo(double rpy[3], int speed=-1, int cType=-1);

    /*!
     * @brief     手先の姿勢(x-y-z系オイラー角)を指定した角度まで動かす。
     * @param[in] r      手先の正面座標系でのRoll角度[deg]を指定します。
     * @param[in] p      手先の正面座標系でのPitch角度[deg]を指定します。
     * @param[in] y      手先の正面座標系でのYaw角度[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @param[in] cType  cType 補間方法を指定する。
     * @return           成功したら0を返す。
     */ 
    unsigned long turnTo(double r, double p, double y, int speed=-1, int cType=-1);

    /*!
     * @brief       現在動作中の動作が完了するまで待つ。
     */ 
    void wait();
  };

  /*!
   * @brief ロボットを抽象化したクラス。
   */
  class Robot {
  private:
    const std::string ipaddr;
    std::ostream &msgstrm;
    
  public:
    Arm  rarm;
    Arm  larm;
    Hand rhand;
    Hand lhand;
    int speed;

  public:
    Robot(const std::string ipaddr);
    virtual ~Robot();
    
  private:
    void emesg(const char *mesg, const char *hdr="**");
    void connect(void);

  public:

    /*!
     * @brief       制御PCをシャットダウンする。
     */ 
    void poweroff(void);

    /*!
     * @brief       関節軸のキャリブレーションを実行する。
     */ 
    unsigned long jointCalib(void);

    /*!
     * @brief       サーボONを実行する。
     */ 
    void servoON(void);

    /*!
     * @brief       サーボOFFを実行する。
     */ 
    void servoOFF(void);
    void setDefaultSpeed(int speed);

    /*!
     * @brief     両手を肩の後ろに回したサーボOFF姿勢に移行する。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     */ 
    unsigned long makeEscapePose(int speed=-1);

    /*!
     * @brief      全身の関節角度を取得します。
     * @param[in]  angles   取得した関節角度が格納されます。
     * @param[out] realFlag 取得する関節角度が実際の角度か指令角度かを指定します。
     *                 - true : 実際の関節角度を返します。
     *                 - false : 指令関節角度を返します。
     */ 
    void getAngles(double angles[DOFS_WHOLE], bool realFlag=false);

    /*!
     * @brief      首軸の関節角度を取得します。
     * @param[in]  pan   取得した関節角度（パン）が格納されます。
     * @param[in]  tilt  取得した関節角度（チルト）が格納されます。
     * @param[out] realFlag 取得する関節角度が実際の角度か指令角度かを指定します。
     *                 - true : 実際の関節角度を返します。
     *                 - false : 指令関節角度を返します。
     */ 
    void getNeckAngles(double &pan, double &tilt, bool realFlag=false);

    /*!
     * @brief      首軸の関節角度を取得します。
     * @param[in]  angles   取得した関節角度が格納されます。
     * @param[out] realFlag 取得する関節角度が実際の角度か指令角度かを指定します。
     *                 - true : 実際の関節角度を返します。
     *                 - false : 指令関節角度を返します。
     */ 
    void getNeckAngles(double angles[DOFS_NECK], bool realFlag=false);

    /*!
     * @brief     首関節を指定した角度まで動かす。
     * @param[in] pan    パン角度[deg]を指定します。
     * @param[in] tilt   チルト角度[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @return           成功したら0を返す。
     */ 
    unsigned long faceTo(double pan, double tilt, int speed=-1);

    /*!
     * @brief     首関節を指定した角度まで動かす。
     * @param[in] angles パン・チルト角度[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @return           成功したら0を返す。
     */ 
    unsigned long faceTo(double angles[2], int speed=-1);

    /*!
     * @brief     首関節を現在角度から指定した角度分だけ動かす。
     * @param[in] pan    パン角度[deg]を指定します。
     * @param[in] tilt   チルト角度[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @return           成功したら0を返す。
     */ 
    unsigned long turnNeck(double pan, double tilt, int speed=-1);

    /*!
     * @brief     首関節を現在角度から指定した角度分だけ動かす。
     * @param[in] angles パン・チルト角度[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @return           成功したら0を返す。
     */ 
    unsigned long turnNeck(double angles[2], int speed=-1);

    /*!
     * @brief      腰ヨー軸の関節角度を取得します。
     * @param[in]  angle    取得した関節角度が格納されます。
     * @param[out] realFlag 取得する関節角度が実際の角度か指令角度かを指定します。
     *                 - true : 実際の関節角度を返します。
     *                 - false : 指令関節角度を返します。
     */ 
    void getChestAngle(double &angle, bool realFlag=false);

    /*!
     * @brief     腰ヨー軸を指定した角度まで動かす。
     * @param[in] angle  関節角度[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @return           成功したら0を返す。
     */ 
    unsigned long directTo(double angle, int speed=-1);

    /*!
     * @brief     腰ヨー軸を現在角度から指定した角度分だけ動かす。
     * @param[in] angle  関節角度[deg]を指定します。
     * @param[in] speed  speed パーセントで指定する動作速度[%]。
     * @return           成功したら0を返す。
     */ 
    unsigned long turnChest(double angle, int speed=-1);

    /*!
     * @brief      全身の関節を指定角度(配列で与える)まで動かします。
     * @param[out] angles  全身の関節角度を指定します[deg]。
     * @param[in]  speed   speed パーセントで指定する動作速度[%]。
     * @return           成功したら0を返す。
     */ 
    unsigned long makePose(const double angles[], int speed=-1);
    unsigned long makePose(double jw, double jn0, double jn1,
			   double jr0, double jr1, double jr2,
			   double jr3, double jr4, double jr5,
			   double jl0, double jl1, double jl2,
			   double jl3, double jl4, double jl5,
			   int speed=-1);
    void wait(int block=WHOLE);

    /*!
     * @brief      デジタル入力の値を取得します。
     * @return     デジタル入力のステータス情報（２バイト）。
     */ 
    unsigned short getDin();
    
#ifndef SWIG
  private:
    systemCommand_var sysCom;
    armServer_var arm;
    coordServer_var coord;
    dioPlugin_var dio;
#endif
  };

}

#endif // _ROBOT_HPP_
