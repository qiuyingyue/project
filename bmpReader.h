#ifndef bmpReader_h
#define bmpReader_h

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

//λͼ�ļ�ͷ����;
typedef struct  tagBITMAPFILEHEADER{
	//	WORD bfType;//������ȡ���ṹ���оͲ�������
	DWORD bfSize;//�ļ���С
	WORD bfReserved1;//������
	WORD bfReserved2;//������
	DWORD bfOffBits;//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	DWORD biSize;//��Ϣͷ��С
	DWORD biWidth;//ͼ����
	DWORD biHeight;//ͼ��߶�
	WORD biPlanes;//λƽ����������Ϊ1
	WORD biBitCount;//ÿ����λ��
	DWORD  biCompression; //ѹ������
	DWORD  biSizeImage; //ѹ��ͼ���С�ֽ���
	DWORD  biXPelsPerMeter; //ˮƽ�ֱ���
	DWORD  biYPelsPerMeter; //��ֱ�ֱ���
	DWORD  biClrUsed; //λͼʵ���õ���ɫ����
	DWORD  biClrImportant; //��λͼ����Ҫ��ɫ����
}BITMAPINFOHEADER; //λͼ��Ϣͷ����

//������Ϣ
typedef struct tagIMAGEDATA
{
	BYTE blue;
	BYTE green;
	BYTE red;
}DATA;

class BmpReader{
public:
	BITMAPFILEHEADER strHead;
	BITMAPINFOHEADER strInfo;
	int h, w, size;
	WORD bfType;

	DATA* imgdata;
	bool readBMP(const char* filename);
	void clear();
};

#endif /* bmpReader_h */
