/*!
 *  @file  Robot.cpp
 *  @brief ロボット起動直後に必要な関節軸のキャリブレーションを行うプログラム
 */

#include "Robot.hpp"

#ifndef IPADDR
#define IPADDR "192.168.128.10"
#endif

/*!
 *  usage: jointCalib 接続先ホスト名 or IP address (デフォルト値 192.168.128.10)
 */
int main(int argc, const char *argv[])
{
  const char *ipaddr;
  if (argc < 2) ipaddr = IPADDR;
  else ipaddr = argv[1];

  KSP::Robot rbt(ipaddr);
  rbt.jointCalib();
}
