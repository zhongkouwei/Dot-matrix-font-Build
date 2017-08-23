/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		Font.h
* Author 	gaoshuo
* Version 	1.2
* Date		2016.07.11
* Description   头文件声明：Font.h
description     提供对字库操作的类的声明
*******************************************************************************/
#pragma once

//类的声明
class CMyFont
{
public:
	//构造函数
	CMyFont();
	//析构函数
	~CMyFont();

	/* DESCRIPTION
	求中英文字库
	* ARGUMENTS
	Argumegnt1          int offset
	* RETURN
	Return value        unsigned char* 
	* NOTES
	Function note
	*/
	unsigned char* getAsciiLib(int offset, int byteNumber);
	unsigned char* getHzkLib(int offset, int byteNumber);

	/* DESCRIPTION
	先求字符在字库中的偏移量，再求出字库
	* ARGUMENTS
	Argumegnt1          char* word
	* RETURN
	Return value        int offset
	* NOTES
	Function note
	*/
	unsigned char* getLib(unsigned char* word);

	bool openHzk(CString m_selectfonts);
	bool openAsc();

	/* DESCRIPTION
	将横向取模转为纵向取模
	* ARGUMENTS
	Argumegnt1          unsigned char org[][2], unsigned char* re
	* RETURN
	Return value        void
	* NOTES
	Function note
	*/
	char shift_value(char org, int index);
	void transverse_modulus(unsigned char org[][2], unsigned char* re, int x, int y);
	void transverse_modulus(unsigned char org[][3], unsigned char* re, int x, int y);

	// 字节倒序
	void bit_reverse(unsigned char* word, unsigned char *retValue);
private:
	FILE* fileHzk;		// Hzk文件指针
	FILE* fileAsc;		// Asc文件指针
	int i, j, k, offset;	// 偏移量

	
	unsigned char asciiLib[16];
	unsigned char hzkLib[32];
};

