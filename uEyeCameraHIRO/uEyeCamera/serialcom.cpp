#define _CRT_SECURE_NO_DEPRECATE 1  /* VisualC++2005 での警告抑制 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Win32 API
#include <string.h>
#include <math.h>
#include <dos.h>
//#include <sys/time.h>
//#include <unistd.h>
#include <time.h>
#include "serial_com_ver2_20101203.h"




HANDLE port_a, port_b, port_c;
	char TX[16];
	char RX_a[16], RX_b[16], RX_c[16];
	char math[16];

//#define sample 0.02
//#define dtc_low_kasoku 0.08
//#define AMP 2.8


HANDLE open_port_x(char name[]){
	HANDLE port_a;

	const char* c = name;

	// ポートを開く
	port_a = CreateFileA(
	  name,								// 通信デバイスの名前のアドレス //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//アクセス (読み取りおよび書き込み) モード //
	  0,								// 共有モード //
	  NULL,								// セキュリティ記述子のアドレス //
	  OPEN_EXISTING,					// 作成方法 //
	  0,								// ファイル属性 //
	  NULL);							// コピーする属性付きファイルのハンドル //
	if(port_a == INVALID_HANDLE_VALUE){
		// ポートが開けなかった
		fprintf(stderr, "Serial port(%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_a;
}

// ポートを開く関数の定義
HANDLE open_port_a(char name[]){
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
		fprintf(stderr, "Serial port(%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_a;
}

HANDLE open_port_b(char name[]){
	HANDLE port_b;

	const char* c = name;

	// ポートを開く
	port_b = CreateFileA(
	  "\\\\.\\COM12",					// 通信デバイスの名前のアドレス //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//アクセス (読み取りおよび書き込み) モード //
	  0,								// 共有モード //
	  NULL,								// セキュリティ記述子のアドレス //
	  OPEN_EXISTING,					// 作成方法 //
	  0,								// ファイル属性 //
	  NULL);							// コピーする属性付きファイルのハンドル //
	if(port_b == INVALID_HANDLE_VALUE){
		// ポートが開けなかった
		fprintf(stderr, "Serial port(%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_b;
}

HANDLE open_port_c(char name[]){
	HANDLE port_c;

	const char* c = name;

	// ポートを開く
	port_c = CreateFileA(
	  "\\\\.\\COM10",					// 通信デバイスの名前のアドレス //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//アクセス (読み取りおよび書き込み) モード //
	  0,								// 共有モード //
	  NULL,								// セキュリティ記述子のアドレス //
	  OPEN_EXISTING,					// 作成方法 //
	  0,								// ファイル属性 //
	  NULL);							// コピーする属性付きファイルのハンドル //
	if(port_c == INVALID_HANDLE_VALUE){
		// ポートが開けなかった
		fprintf(stderr, "Serial port(%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_c;
}

// ポートAを閉じる関数の定義
void close_port_a(HANDLE port){
  // ポートを閉じる
  CloseHandle(port_a);
}  

// ポートBを閉じる関数の定義
void close_port_b(HANDLE port){
  // ポートを閉じる
  CloseHandle(port_b);
}  
// ポートCを閉じる関数の定義
void close_port_c(HANDLE port){
  // ポートを閉じる
  CloseHandle(port_c);
}  


// ポートAに書き込む関数の定義
size_t port_a_write(HANDLE port_a, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port_a, buf, nbytes, &num, NULL);
    return (size_t)num;
}
// ポートBに書き込む関数の定義
size_t port_b_write(HANDLE port_b, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port_b, buf, nbytes, &num, NULL);
    return (size_t)num;
}
// ポートCに書き込む関数の定義
size_t port_c_write(HANDLE port_c, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port_c, buf, nbytes, &num, NULL);
    return (size_t)num;
}


// ポートAから読み込む関数の定義
size_t port_a_read(HANDLE port_a, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port_a, buf, nbytes, &num, NULL);
  return (size_t)num;
}
// ポートBから読み込む関数の定義
size_t port_b_read(HANDLE port_b, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port_b, buf, nbytes, &num, NULL);
  return (size_t)num;
}
// ポートCから読み込む関数の定義
size_t port_c_read(HANDLE port_c, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port_c, buf, nbytes, &num, NULL);
  return (size_t)num;
}


// ポートAに1byte書き込む関数の定義
int port_a_putc(char c, HANDLE port_a){
  char buf = c;

  port_a_write(port_a, &buf, 1);

  return c;
}
// ポートBに1byte書き込む関数の定義
int port_b_putc(char c, HANDLE port_b){
  char buf = c;

  port_b_write(port_b, &buf, 1);

  return c;
}
// ポートCに1byte書き込む関数の定義
int port_c_putc(char c, HANDLE port_c){
  char buf = c;

  port_c_write(port_c, &buf, 1);

  return c;
}

// ポートAから1byte読み込む関数の定義
int port_a_getc(HANDLE port_a){
	unsigned char buf;
	size_t s;

	do{
		s = port_a_read(port_a, &buf, 1);
	} while(s < 1);

  return (int)buf;
}
// ポートBから1byte読み込む関数の定義
int port_b_getc(HANDLE port_b){
	unsigned char buf;
	size_t s;

	do{
		s = port_b_read(port_b, &buf, 1);
	} while(s < 1);

  return (int)buf;
}
// ポートCから1byte読み込む関数の定義
int port_c_getc(HANDLE port_c){
	unsigned char buf;
	size_t s;

	do{
		s = port_c_read(port_c, &buf, 1);
	} while(s < 1);

  return (int)buf;
}

// ポートAを設定する関数の定義
int serial_port_a_params (HANDLE port_a,
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
int serial_port_b_params (HANDLE port_b,
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
int serial_port_c_params (HANDLE port_c,
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

void pa()
{
	fingermove('a',"7fffaaaa");
	fingermove('b',"7fffaaaa");
	fingermove('c',"7fffaaaa");
}

void choki()
{
	fingermove('a',"7fffaaaa");
	fingermove('b',"7fff6666");
	fingermove('c',"7fff7fff");
}

void gu()
{
	fingermove('c',"7fff2222");
	fingermove('b',"55553333");
	fingermove('a',"7fff4444");
}


void fingermove(char abc, char m[])
{

	if (abc == 'a')
	{

	TX[0] = 'a';
	port_a_putc(TX[0], port_a);
	port_a_putc(m[0], port_a);
	port_a_putc(m[1], port_a);
	port_a_putc(m[2], port_a);
	port_a_putc(m[3], port_a);
	port_a_putc(m[4], port_a);
	port_a_putc(m[5], port_a);
	port_a_putc(m[6], port_a);
	port_a_putc(m[7], port_a);

	//PORT_Aデータ受信//
	RX_a[0] = port_a_getc(port_a);
	RX_a[1] = port_a_getc(port_a);
	RX_a[2] = port_a_getc(port_a);
	RX_a[3] = port_a_getc(port_a);
	RX_a[4] = port_a_getc(port_a);
	RX_a[5] = port_a_getc(port_a);
	RX_a[6] = port_a_getc(port_a);
	RX_a[7] = port_a_getc(port_a);
	RX_a[8] = port_a_getc(port_a);
	}

	if (abc == 'b')
	{

	TX[0] = 'a';
	port_b_putc(TX[0], port_b);
	
	port_b_putc(m[0], port_b);
	port_b_putc(m[1], port_b);
	port_b_putc(m[2], port_b);
	port_b_putc(m[3], port_b);
	port_b_putc(m[4], port_b);
	port_b_putc(m[5], port_b);
	port_b_putc(m[6], port_b);
	port_b_putc(m[7], port_b);

	//PORT_Bデータ受信//
	RX_b[0] = port_b_getc(port_b);
	RX_b[1] = port_b_getc(port_b);
	RX_b[2] = port_b_getc(port_b);
	RX_b[3] = port_b_getc(port_b);
	RX_b[4] = port_b_getc(port_b);
	RX_b[5] = port_b_getc(port_b);
	RX_b[6] = port_b_getc(port_b);
	RX_b[7] = port_b_getc(port_b);
	RX_b[8] = port_b_getc(port_b);
	}
	
	
	if (abc == 'c')
	{

	TX[0] = 'a';
	port_c_putc(TX[0], port_c);
	
	port_c_putc(m[0], port_c);
	port_c_putc(m[1], port_c);
	port_c_putc(m[2], port_c);
	port_c_putc(m[3], port_c);
	port_c_putc(m[4], port_c);
	port_c_putc(m[5], port_c);
	port_c_putc(m[6], port_c);
	port_c_putc(m[7], port_c);

	//PORT_Cデータ受信//
	RX_c[0] = port_c_getc(port_c);
	RX_c[1] = port_c_getc(port_c);
	RX_c[2] = port_c_getc(port_c);
	RX_c[3] = port_c_getc(port_c);
	RX_c[4] = port_c_getc(port_c);
	RX_c[5] = port_c_getc(port_c);
	RX_c[6] = port_c_getc(port_c);
	RX_c[7] = port_c_getc(port_c);
	RX_c[8] = port_c_getc(port_c);
	}
	

return;
}


// main関数の定義
int main(void){

	//gu();
	//pa();
	//choki();



	//定数//
	
 
  	
//	FILE *fp;
//	int i;
//	long t,t1;

	// ポートを開く
//    port = open_port("COM5");
//	port = open_port("\\\\.\\COM24");
//	port = open_port("com19");
	 port_a = open_port_a("COM");
	if(port_a < 0){
 	   // ポートが開けなかった
 	   return -1;
	}
	port_b = open_port_b("COM");
	if(port_b < 0){
 	   // ポートが開けなかった
 	   return -1;
	}
	port_c = open_port_c("COM");
	if(port_c < 0){
 	   // ポートが開けなかった
 	   return -1;
	}
	// ポートの設定
	serial_port_a_params(port_a,115200, 8, ONESTOPBIT, NOPARITY);
	serial_port_b_params(port_b,115200, 8, ONESTOPBIT, NOPARITY);
	serial_port_c_params(port_c,115200, 8, ONESTOPBIT, NOPARITY);


	/*
	fingermove('a',"7fffaaaa");
	fingermove('b',"7fffaaaa");
	fingermove('c',"7fffaaaa");

	fingermove('a',"7fff7fff");
	fingermove('b',"7fff7fff");
	fingermove('c',"7fff7fff");

	fingermove('a',"7fffaaaa");
	fingermove('b',"7fffaaaa");
	fingermove('c',"7fffaaaa");

	fingermove('a',"7fff7fff");
	fingermove('b',"7fff7fff");
	fingermove('c',"7fff7fff");
	*/
	/*

	TX[0] = 'a';  //マイコンをコントロールモードへ移行する
 

	//PORT_Aデータ送信//
	port_a_putc(TX[0], port_a);   // Board 'a' mode
	port_a_putc('7', port_a);
	port_a_putc('f', port_a);	
	port_a_putc('f', port_a);	
	port_a_putc('f', port_a);
	port_a_putc('7', port_a);
	port_a_putc('f', port_a);
	port_a_putc('f', port_a);
	port_a_putc('f', port_a);
	//PORT_Aデータ受信//
	RX_a[0] = port_a_getc(port_a);
	RX_a[1] = port_a_getc(port_a);
	RX_a[2] = port_a_getc(port_a);
	RX_a[3] = port_a_getc(port_a);
	RX_a[4] = port_a_getc(port_a);
	RX_a[5] = port_a_getc(port_a);
	RX_a[6] = port_a_getc(port_a);
	RX_a[7] = port_a_getc(port_a);
	RX_a[8] = port_a_getc(port_a);

	//PORT_Aデータ送信//
	port_a_putc(TX[0], port_a);   // Board 'a' mode
	port_a_putc('7', port_a);
	port_a_putc('f', port_a);	
	port_a_putc('f', port_a);	
	port_a_putc('f', port_a);
	port_a_putc('a', port_a);
	port_a_putc('a', port_a);
	port_a_putc('a', port_a);
	port_a_putc('a', port_a);
	//PORT_Aデータ受信//
	RX_a[0] = port_a_getc(port_a);
	RX_a[1] = port_a_getc(port_a);
	RX_a[2] = port_a_getc(port_a);
	RX_a[3] = port_a_getc(port_a);
	RX_a[4] = port_a_getc(port_a);
	RX_a[5] = port_a_getc(port_a);
	RX_a[6] = port_a_getc(port_a);
	RX_a[7] = port_a_getc(port_a);
	RX_a[8] = port_a_getc(port_a);

	//PORT_Aデータ送信//
	port_a_putc(TX[0], port_a);   // Board 'a' mode
	port_a_putc('7', port_a);
	port_a_putc('f', port_a);	
	port_a_putc('f', port_a);	
	port_a_putc('f', port_a);
	port_a_putc('7', port_a);
	port_a_putc('f', port_a);
	port_a_putc('f', port_a);
	port_a_putc('f', port_a);
	//PORT_Aデータ受信//
	RX_a[0] = port_a_getc(port_a);
	RX_a[1] = port_a_getc(port_a);
	RX_a[2] = port_a_getc(port_a);
	RX_a[3] = port_a_getc(port_a);
	RX_a[4] = port_a_getc(port_a);
	RX_a[5] = port_a_getc(port_a);
	RX_a[6] = port_a_getc(port_a);
	RX_a[7] = port_a_getc(port_a);
	RX_a[8] = port_a_getc(port_a);

	//PORT_Bデータ送信//
	port_b_putc(TX[0], port_b);   // Board 'a' mode
	port_b_putc('7', port_b);
	port_b_putc('f', port_b);	
	port_b_putc('f', port_b);	
	port_b_putc('f', port_b);
	port_b_putc('7', port_b);
	port_b_putc('f', port_b);
	port_b_putc('f', port_b);
	port_b_putc('f', port_b);
	//PORT_Bデータ受信//
	RX_b[0] = port_b_getc(port_b);
	RX_b[1] = port_b_getc(port_b);
	RX_b[2] = port_b_getc(port_b);
	RX_b[3] = port_b_getc(port_b);
	RX_b[4] = port_b_getc(port_b);
	RX_b[5] = port_b_getc(port_b);
	RX_b[6] = port_b_getc(port_b);
	RX_b[7] = port_b_getc(port_b);
	RX_b[8] = port_b_getc(port_b);

	//PORT_Cデータ送信//
	port_c_putc(TX[0], port_c);   // Board 'a' mode
	port_c_putc('7', port_c);
	port_c_putc('f', port_c);	
	port_c_putc('f', port_c);	
	port_c_putc('f', port_c);
	port_c_putc('7', port_c);
	port_c_putc('f', port_c);
	port_c_putc('f', port_c);
	port_c_putc('f', port_c);
	//PORT_Cデータ受信//
	RX_c[0] = port_c_getc(port_c);
	RX_c[1] = port_c_getc(port_c);
	RX_c[2] = port_c_getc(port_c);
	RX_c[3] = port_c_getc(port_c);
	RX_c[4] = port_c_getc(port_c);
	RX_c[5] = port_c_getc(port_c);
	RX_c[6] = port_c_getc(port_c);
	RX_c[7] = port_c_getc(port_c);
	RX_c[8] = port_c_getc(port_c);


*/



	//	printf("受信したデータは、%xです。\r\n",b);
	


	//すべての状態を表示する。//
	printf("PORT_Aの指先は、%c %c %c %cです。\r\n", RX_a[0], RX_a[1], RX_a[2], RX_a[3]);
	printf("PORT_Aの根元は、%c %c %c %cです。\r\n", RX_a[4], RX_a[5], RX_a[6], RX_a[7]);
	printf("PORT_Bの指先は、%c %c %c %cです。\r\n", RX_b[0], RX_b[1], RX_b[2], RX_b[3]);
	printf("PORT_Bの根元は、%c %c %c %cです。\r\n", RX_b[4], RX_b[5], RX_b[6], RX_b[7]);
	printf("PORT_Cの指先は、%c %c %c %cです。\r\n", RX_c[0], RX_c[1], RX_c[2], RX_c[3]);
	printf("PORT_Cの根元は、%c %c %c %cです。\r\n", RX_c[4], RX_c[5], RX_c[6], RX_c[7]);
	
	printf("Pleas Push Enter!\n");
	getchar();
	
//	fclose(fp);
	
	
//	printf("ファイルをクローズしました\n");

//	close_port(port);

	
  return 0;
}
