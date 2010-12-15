#define _CRT_SECURE_NO_DEPRECATE 1  /* VisualC++2005 �ł̌x���}�� */
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

	// �|�[�g���J��
	port_a = CreateFileA(
	  name,								// �ʐM�f�o�C�X�̖��O�̃A�h���X //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//�A�N�Z�X (�ǂݎ�肨��я�������) ���[�h //
	  0,								// ���L���[�h //
	  NULL,								// �Z�L�����e�B�L�q�q�̃A�h���X //
	  OPEN_EXISTING,					// �쐬���@ //
	  0,								// �t�@�C������ //
	  NULL);							// �R�s�[���鑮���t���t�@�C���̃n���h�� //
	if(port_a == INVALID_HANDLE_VALUE){
		// �|�[�g���J���Ȃ�����
		fprintf(stderr, "Serial port(%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_a;
}

// �|�[�g���J���֐��̒�`
HANDLE open_port_a(char name[]){
	HANDLE port_a;

	const char* c = name;

	// �|�[�g���J��
	port_a = CreateFileA(
	  "COM9",								// �ʐM�f�o�C�X�̖��O�̃A�h���X //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//�A�N�Z�X (�ǂݎ�肨��я�������) ���[�h //
	  0,								// ���L���[�h //
	  NULL,								// �Z�L�����e�B�L�q�q�̃A�h���X //
	  OPEN_EXISTING,					// �쐬���@ //
	  0,								// �t�@�C������ //
	  NULL);							// �R�s�[���鑮���t���t�@�C���̃n���h�� //
	if(port_a == INVALID_HANDLE_VALUE){
		// �|�[�g���J���Ȃ�����
		fprintf(stderr, "Serial port(%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_a;
}

HANDLE open_port_b(char name[]){
	HANDLE port_b;

	const char* c = name;

	// �|�[�g���J��
	port_b = CreateFileA(
	  "\\\\.\\COM12",					// �ʐM�f�o�C�X�̖��O�̃A�h���X //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//�A�N�Z�X (�ǂݎ�肨��я�������) ���[�h //
	  0,								// ���L���[�h //
	  NULL,								// �Z�L�����e�B�L�q�q�̃A�h���X //
	  OPEN_EXISTING,					// �쐬���@ //
	  0,								// �t�@�C������ //
	  NULL);							// �R�s�[���鑮���t���t�@�C���̃n���h�� //
	if(port_b == INVALID_HANDLE_VALUE){
		// �|�[�g���J���Ȃ�����
		fprintf(stderr, "Serial port(%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_b;
}

HANDLE open_port_c(char name[]){
	HANDLE port_c;

	const char* c = name;

	// �|�[�g���J��
	port_c = CreateFileA(
	  "\\\\.\\COM10",					// �ʐM�f�o�C�X�̖��O�̃A�h���X //
	  //name,
	  GENERIC_READ | GENERIC_WRITE,		//�A�N�Z�X (�ǂݎ�肨��я�������) ���[�h //
	  0,								// ���L���[�h //
	  NULL,								// �Z�L�����e�B�L�q�q�̃A�h���X //
	  OPEN_EXISTING,					// �쐬���@ //
	  0,								// �t�@�C������ //
	  NULL);							// �R�s�[���鑮���t���t�@�C���̃n���h�� //
	if(port_c == INVALID_HANDLE_VALUE){
		// �|�[�g���J���Ȃ�����
		fprintf(stderr, "Serial port(%s) open error.\n", name);
		return (HANDLE)-1;
	}

  return port_c;
}

// �|�[�gA�����֐��̒�`
void close_port_a(HANDLE port){
  // �|�[�g�����
  CloseHandle(port_a);
}  

// �|�[�gB�����֐��̒�`
void close_port_b(HANDLE port){
  // �|�[�g�����
  CloseHandle(port_b);
}  
// �|�[�gC�����֐��̒�`
void close_port_c(HANDLE port){
  // �|�[�g�����
  CloseHandle(port_c);
}  


// �|�[�gA�ɏ������ފ֐��̒�`
size_t port_a_write(HANDLE port_a, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port_a, buf, nbytes, &num, NULL);
    return (size_t)num;
}
// �|�[�gB�ɏ������ފ֐��̒�`
size_t port_b_write(HANDLE port_b, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port_b, buf, nbytes, &num, NULL);
    return (size_t)num;
}
// �|�[�gC�ɏ������ފ֐��̒�`
size_t port_c_write(HANDLE port_c, void *buf, size_t nbytes)
{
    DWORD num;

    WriteFile(port_c, buf, nbytes, &num, NULL);
    return (size_t)num;
}


// �|�[�gA����ǂݍ��ފ֐��̒�`
size_t port_a_read(HANDLE port_a, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port_a, buf, nbytes, &num, NULL);
  return (size_t)num;
}
// �|�[�gB����ǂݍ��ފ֐��̒�`
size_t port_b_read(HANDLE port_b, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port_b, buf, nbytes, &num, NULL);
  return (size_t)num;
}
// �|�[�gC����ǂݍ��ފ֐��̒�`
size_t port_c_read(HANDLE port_c, void *buf, size_t nbytes)
{
  DWORD num;
  
  ReadFile(port_c, buf, nbytes, &num, NULL);
  return (size_t)num;
}


// �|�[�gA��1byte�������ފ֐��̒�`
int port_a_putc(char c, HANDLE port_a){
  char buf = c;

  port_a_write(port_a, &buf, 1);

  return c;
}
// �|�[�gB��1byte�������ފ֐��̒�`
int port_b_putc(char c, HANDLE port_b){
  char buf = c;

  port_b_write(port_b, &buf, 1);

  return c;
}
// �|�[�gC��1byte�������ފ֐��̒�`
int port_c_putc(char c, HANDLE port_c){
  char buf = c;

  port_c_write(port_c, &buf, 1);

  return c;
}

// �|�[�gA����1byte�ǂݍ��ފ֐��̒�`
int port_a_getc(HANDLE port_a){
	unsigned char buf;
	size_t s;

	do{
		s = port_a_read(port_a, &buf, 1);
	} while(s < 1);

  return (int)buf;
}
// �|�[�gB����1byte�ǂݍ��ފ֐��̒�`
int port_b_getc(HANDLE port_b){
	unsigned char buf;
	size_t s;

	do{
		s = port_b_read(port_b, &buf, 1);
	} while(s < 1);

  return (int)buf;
}
// �|�[�gC����1byte�ǂݍ��ފ֐��̒�`
int port_c_getc(HANDLE port_c){
	unsigned char buf;
	size_t s;

	do{
		s = port_c_read(port_c, &buf, 1);
	} while(s < 1);

  return (int)buf;
}

// �|�[�gA��ݒ肷��֐��̒�`
int serial_port_a_params (HANDLE port_a,
			int baudrate, int byte_size,
			int stop_bits, int parity){
  DCB dcb;

  dcb.DCBlength = sizeof(DCB);
  // �ݒ��ǂݍ���
  GetCommState(port_a, &dcb);
  dcb.BaudRate = baudrate;  // �{�[���[�g
  dcb.ByteSize = byte_size; // �r�b�g��
  dcb.StopBits = stop_bits; // �X�g�b�v�r�b�g
  dcb.Parity = parity; 		// �p���e�B
  // �ݒ肷��
  SetCommState(port_a, &dcb);

  return 1;
}
// �|�[�gB��ݒ肷��֐��̒�`
int serial_port_b_params (HANDLE port_b,
			int baudrate, int byte_size,
			int stop_bits, int parity){
  DCB dcb;

  dcb.DCBlength = sizeof(DCB);
  // �ݒ��ǂݍ���
  GetCommState(port_b, &dcb);
  dcb.BaudRate = baudrate;  // �{�[���[�g
  dcb.ByteSize = byte_size; // �r�b�g��
  dcb.StopBits = stop_bits; // �X�g�b�v�r�b�g
  dcb.Parity = parity; 		// �p���e�B
  // �ݒ肷��
  SetCommState(port_b, &dcb);

  return 1;
}
// �|�[�gC��ݒ肷��֐��̒�`
int serial_port_c_params (HANDLE port_c,
			int baudrate, int byte_size,
			int stop_bits, int parity){
  DCB dcb;

  dcb.DCBlength = sizeof(DCB);
  // �ݒ��ǂݍ���
  GetCommState(port_c, &dcb);
  dcb.BaudRate = baudrate;  // �{�[���[�g
  dcb.ByteSize = byte_size; // �r�b�g��
  dcb.StopBits = stop_bits; // �X�g�b�v�r�b�g
  dcb.Parity = parity; 		// �p���e�B
  // �ݒ肷��
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

	//PORT_A�f�[�^��M//
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

	//PORT_B�f�[�^��M//
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

	//PORT_C�f�[�^��M//
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


