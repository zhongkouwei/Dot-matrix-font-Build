/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		Font.cpp
* Author 	gaoshuo
* Version 	1.2
* Date		2016.07.11
* Description   对字库操作的类的实现
description     
*******************************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include "SET.h"
#include "Font.h"
CMyFont::CMyFont()
{
	openAsc();
	openHzk(m_selectfonts);	
}

CMyFont::~CMyFont()
{
	fclose(fileAsc);
	fileAsc = NULL;
	fclose(fileHzk);
	fileHzk = NULL;
}

// 从英文字库中根据offset偏移量读取出bitNumber位
unsigned char* CMyFont::getAsciiLib(int offset,int bitNumber){
	unsigned char* Lib = NULL;
	unsigned char* reverseLib = NULL;
	unsigned char ascii16[16][2];
	unsigned char ascii24[24][3];
	int conduct , column ;
	fseek(fileAsc, offset, SEEK_SET);
	fread(asciiLib, 1, bitNumber, fileAsc);
	// 根据选择不同的取模算法来进行操作
	if (0 == m_CB_ModelSave)
		return asciiLib;
	if (1 == m_CB_ModelSave){

		bit_reverse(asciiLib, reverseLib);
		return reverseLib;
	}
	if (16 == bitNumber) { 
		conduct = 1; 
		column = 16; 
		memcpy(ascii16, asciiLib, sizeof(asciiLib));
		transverse_modulus(ascii16, Lib, conduct, column);
		if (4 == m_CB_ModelSave){
			bit_reverse(Lib, reverseLib);
			return reverseLib;
		}
	}
	else { 
		conduct = 2;
		column = 24;
		memcpy(ascii24, asciiLib, sizeof(asciiLib));
		transverse_modulus(ascii24, Lib, conduct, column);
		if (4 == m_CB_ModelSave){
			bit_reverse(Lib, reverseLib);
			return reverseLib;
		}
	}
	return Lib;
}

// 从中文字库中根据offset偏移量读出bytetNumber位
unsigned char* CMyFont::getHzkLib(int offset,int byteNumber){
	unsigned char* Lib = NULL;
	unsigned char* reverseLib = NULL;
	unsigned char hzk16[16][2];
	unsigned char hzk24[24][3];
	int conduct, column;
	fseek(fileHzk, offset, SEEK_SET);
	fread(hzkLib, 1, byteNumber, fileHzk);
	if (0 == m_CB_ModelSave)
		return hzkLib;
	if (1 == m_CB_ModelSave){

		bit_reverse(hzkLib, reverseLib);
		return reverseLib;
	}
	if (16 == byteNumber) {
		conduct = 2;
		column = 16;
		memcpy(hzk16, hzkLib, sizeof(hzkLib));
		transverse_modulus(hzk16, Lib,conduct,column);
		if (4 == m_CB_ModelSave){
			bit_reverse(Lib, reverseLib);
			return reverseLib;
		}
	}
	else {
		conduct = 3;
		column = 24;
		memcpy(hzk24, hzkLib, sizeof(hzkLib));
		transverse_modulus(hzk24, Lib,conduct,column);
		if (4 == m_CB_ModelSave){
			bit_reverse(Lib, reverseLib);
			return reverseLib;
		}
	}
	return Lib;
}

// 获得字符判断中英文从而读取相应字库
unsigned char* CMyFont::getLib(unsigned char* word){
	int m = 0;
	unsigned char* Lib = NULL;

	// 对每个字符进行判断，求偏移量，读取相应字库
	while (word[m] != '\0'){
		if (word[m] > 'A' && word[m] < 'z'){
			offset = word[m] * ((m_fontSize / 8) - 1) * m_fontSize;
			Lib = getAsciiLib(offset, ((m_fontSize / 8)-1) * m_fontSize);
			m += 1;// 向后移动一个字节
		}
		else{
			offset = (94 * (word[m] - 0xA0 - 1) + (word[m + 1] - 0xA0 - 1)) * 32;
			if (m_fontSize == 24) offset = (94 * (word[m] - 176) + (word[m + 1] - 0xa0 - 1)) * 72; //如果是24则用这种求偏移量方法
			Lib = getHzkLib(offset, m_fontSize * m_fontSize / 8);
			m += 2;// 向后挪两个字节
		}
	}

	return Lib;
}

bool CMyFont::openAsc(){
	if (m_fontSize == 16)
		fileAsc = fopen("ASC16", "rb");
	else
		fileAsc = fopen("ASC24", "rb");
	if (fileAsc == NULL)
	{
		return false;
	}
}

bool CMyFont::openHzk(CString m_selectfonts){
	// 将用户的两个选择字体和大小合并为字符串，以打开文件
	CString i;
	i.Format("%d", m_fontSize);
	m_selectfonts += i;
	fileHzk = fopen(m_selectfonts, "rb");

	if (fileHzk == NULL){
		return false;
	}
}

// 纵向取模的算法
char CMyFont::shift_value(char org, int index)
{
	org = (org & (0x1 << index)) >> index;
	return org;
}
void CMyFont::transverse_modulus(unsigned char org[][2], unsigned char* re,int x,int y)
{
	char **tmp = (char **)malloc(sizeof(char*)*x);	// 生成一个指向指针的指针
	for (i = 0; i < x; i++){
		tmp[i] = (char *)malloc(sizeof(char)*y);
	}
	int j = 0, n = 0, column = 0;
	for (; j< x; j++)
	{
		int i = 0, index = 0;
		for (; i< y; i++)
		{
			if (i % 2 != 0)
			{
				n = 1;
			}
			else
			{
				n = 0;
			}
			tmp[j][i] = (shift_value(org[(1 - n) * 8][column], 7 - index) << 0) | \
				(shift_value(org[(1 - n) * 8 + 1][column], 7 - index) << 1) | \
				(shift_value(org[(1 - n) * 8 + 2][column], 7 - index) << 2) | \
				(shift_value(org[(1 - n) * 8 + 3][column], 7 - index) << 3) | \
				(shift_value(org[(1 - n) * 8 + 4][column], 7 - index) << 4) | \
				(shift_value(org[(1 - n) * 8 + 5][column], 7 - index) << 5) | \
				(shift_value(org[(1 - n) * 8 + 6][column], 7 - index) << 6) | \
				(shift_value(org[(1 - n) * 8 + 7][column], 7 - index) << 7);
			if (i % 2 != 0)
				index++;
		}
		column++;
	}

	memcpy(re, tmp, 32);
}
// 纵向取模算法重载
void CMyFont::transverse_modulus(unsigned char org[][3], unsigned char* re, int x, int y)
{
	char tmp[2][16];
	int j = 0, n = 0, column = 0;
	for (; j<x; j++)
	{
		int i = 0, index = 0;
		for (; i< y; i++)
		{
			if (i % 2 != 0)
			{
				n = 1;
			}
			else
			{
				n = 0;
			}
			tmp[j][i] = (shift_value(org[(1 - n) * 8][column], 7 - index) << 0) | \
				(shift_value(org[(1 - n) * 8 + 1][column], 7 - index) << 1) | \
				(shift_value(org[(1 - n) * 8 + 2][column], 7 - index) << 2) | \
				(shift_value(org[(1 - n) * 8 + 3][column], 7 - index) << 3) | \
				(shift_value(org[(1 - n) * 8 + 4][column], 7 - index) << 4) | \
				(shift_value(org[(1 - n) * 8 + 5][column], 7 - index) << 5) | \
				(shift_value(org[(1 - n) * 8 + 6][column], 7 - index) << 6) | \
				(shift_value(org[(1 - n) * 8 + 7][column], 7 - index) << 7);
			if (i % 2 != 0)
				index++;
		}
		column++;
	}

	memcpy(re, tmp, 32);
}

// 字节倒序算法
void  CMyFont::bit_reverse(unsigned char* word, unsigned char *retValue){
	int j = 0;
	while (word[j] != '\0')
	{
		int i;
		retValue[j] |= (word[j] & 1);
		for (i = 1; i < 8; i++)
		{
			retValue[j] <<= 1;
			retValue[j] |= (((1 << i) & word[j]) >> i);
		}
	}
}