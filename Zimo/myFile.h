/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		doFile.h
* Author 	gaoshuo
* Version 	1.2
* Date		2016.07.12
* Description   头文件声明：doFile.h
description     提供对文件操作的类的声明
*******************************************************************************/
#pragma once

class   myFile
{
public:
	myFile();
	~myFile();

	/* DESCRIPTION
	将字库输出到文件
	* ARGUMENTS
	Argumegnt1          char* word
	* RETURN
	Return value        bool
	* NOTES
	Function note
	*/
	bool outFile(unsigned char*, int byteNumber);

	// 设置文件存储路径
	bool setPath(CString path);
private:
	CStdioFile mysFile;
	CFileException fileException;
	CString strOrder;
	char * pszFileName;
	CString savePath;

};

