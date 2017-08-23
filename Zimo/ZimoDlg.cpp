/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		ZimoDlg.cpp
* Author 	gaoshuo
* Version 	1.2
* Date   	16.7.12
* Description   主界面的响应等
description
*******************************************************************************/

#include <stdio.h>
#include "stdafx.h"
#include "Zimo.h"
#include "ZimoDlg.h"
#include "afxdialogex.h"
#include "SET.h"
#include "Font.h"
#include  "myFile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include<stdio.h>#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fstream>
using namespace std;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx 
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CZimoDlg 对话框

CZimoDlg::CZimoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZimoDlg::IDD, pParent)
	, m_editInput(_T(""))   //初始值
	, m_editOutput(_T(""))
	, readFilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZimoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT_EDIT, m_editInput);
	DDX_Text(pDX, IDC_OUTPUT_EDIT, m_editOutput);
	DDX_Text(pDX, IDC_EDIT_SAVE, readFilePath);
}

BEGIN_MESSAGE_MAP(CZimoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEGIN_BUTTON, &CZimoDlg::OnBnClickedBeginButton)
	ON_EN_CHANGE(IDC_INPUT_EDIT, &CZimoDlg::OnEnChangeInputEdit)
	ON_BN_CLICKED(IDC_BUTTON1, &CZimoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_OpenFile_Button, &CZimoDlg::OnBnClickedOpenfileButton)
END_MESSAGE_MAP()


// CZimoDlg 消息处理程序

BOOL CZimoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{						
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZimoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZimoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZimoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZimoDlg::OnBnClickedBeginButton()
{
	// TODO:  在此添加控件通知处理程序代码
	//下面是弹出窗口
	INT_PTR	nRES;		//用来保存Domodel的返回值

	CSET set;              //构建对话框类CSET类的实例

	nRES = set.DoModal();	//弹出对话框
	if (IDCANCEL == nRES)
	{
		//如果返回值为IDCANCEL  则return
		return;
	}

	//将控件输入字符传递给变量
	UpdateData(TRUE);
	
	//
	unsigned char word[100] = {0};
	memcpy(word, (unsigned char *)m_editInput.GetBuffer(0), m_editInput.GetLength() * 2);

	//实例化
	CMyFont myFont;
	myFile	myFile;
	int m = 0;
	int offset;
	unsigned char* Lib = NULL;
	myFile.setPath(m_SavePath);
	while (word[m] != '\0'){
		if (word[m]>'A' && word[m]<'z'){
			offset = word[m] * 16;
			Lib = myFont.getAsciiLib(offset, ((m_fontSize / 8) - 1) * m_fontSize);
			myFile.outFile(Lib, ((m_fontSize / 8) - 1) * m_fontSize);
			m += 1;		//向后移动一个字节
		}
		else{
			offset = (94 * (word[m] - 0xa0 - 1) + (word[m + 1] - 0xa0 - 1)) * 32;
			if (m_fontSize == 24)
				offset = (94 * (word[m] - 176) + (word[m + 1] - 0xa0 - 1)) * 72; //如果是24则用这种求偏移量方法
			Lib = myFont.getHzkLib(offset, m_fontSize * m_fontSize / 8);
			myFile.outFile(Lib, m_fontSize * m_fontSize / 8);
			m += 2;		//向后移动两个字节
		}
	}
	MessageBox("转换成功", "提示");
	

}

//输入框更新时的响应
void CZimoDlg::OnEnChangeInputEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//UpdateData(TRUE);

	//当输入的字符改变，显示框随之改变
	//SetDlgItemText(IDC_OUTPUT_EDIT, i);
	
}

//浏览文件的处理，打开文件对话框
void CZimoDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	// 设置过滤器   
	TCHAR szFilter[] = _T("文本文件|*.txt|c语言文件(*.c)|*.txt|");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("c"), _T("字符"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_SAVE, strFilePath);
	}
}

void CZimoDlg::OnBnClickedOpenfileButton()
{
	// TODO:  在此添加控件通知处理程序代码
	//下面是弹出窗口
	INT_PTR	nRES;		//用来保存Domodel的返回值

	CSET set;              //构建对话框类CSET类的实例

	nRES = set.DoModal();	//弹出对话框
	if (IDCANCEL == nRES)
	{
		//如果返回值为IDCANCEL  则return
		return;
	}

	//将控件输入字符传递给变量
	UpdateData(TRUE);

	unsigned char word[100] = { 0 };
	memcpy(word, (unsigned char *)m_editInput.GetBuffer(0), m_editInput.GetLength() * 2);
	int m = 0;
	int offset;
	unsigned char* Lib = NULL;

	//实例化
	CMyFont myFont;
	myFile	myFile;

	ifstream in(readFilePath);
	in >> word;
	while (word[m] != '\0'){
		if (word[m]>'A' && word[m]<'z'){
			offset = word[m] * 16;
			Lib = myFont.getAsciiLib(offset, ((m_fontSize / 8) - 1) * m_fontSize);
			myFile.outFile(Lib, 1);
			m += 1;		//向后移动一个字节
		}
		else{
			offset = (94 * (word[m] - 0xa0 - 1) + (word[m + 1] - 0xa0 - 1)) * 32;
			if (m_fontSize == 24)
				offset = (94 * (word[m] - 176) + (word[m + 1] - 0xa0 - 1)) * 72; //如果是24则用这种求偏移量方法
			Lib = myFont.getHzkLib(offset, m_fontSize * m_fontSize / 8);
			myFile.outFile(Lib, 2);
			m += 2;		//向后移动两个字节
		}
	}

	MessageBox("转换成功", "提示");
}



