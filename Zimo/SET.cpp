/*******************************************************************************
* Copyright (c) 2016 Chongqing SpiritLong Technology Co., Ltd.
* All rights reserved.
*
* File		SET.cpp
* Author 	gaoshuo
* Version 	1.2
* Date   	16.7.11
* Description   参数设置对话框
description
*******************************************************************************/

#include "stdafx.h"
#include "Zimo.h"
#include "SET.h"
#include "afxdialogex.h"
using namespace std;

// CSET 对话框


CSET::CSET(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSET::IDD, pParent)
	, m_CBfonts(_T(""))
	, m_editSavepath(_T(""))
	, m_CB_ModelSave(0)
	, m_combo_FontSize(0)
{

}
CSET::~CSET()
{
}

void CSET::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_CBfonts);
	DDX_Control(pDX, IDC_COMBO1, m_comboxFonts);
	DDX_Text(pDX, IDC_SAVE_EDIT, m_editSavepath);
	DDX_CBIndex(pDX, IDC_COMBO_ModelSave, m_CB_ModelSave);
	DDX_Control(pDX, IDC_COMBO_ModelSave, m_comboModelWay);
	DDX_Control(pDX, IDC_COMBO_FontSize, m_CB_FontSize);
	DDX_CBIndex(pDX, IDC_COMBO_FontSize, m_combo_FontSize);
}

IMPLEMENT_DYNAMIC(CSET, CDialogEx)
BEGIN_MESSAGE_MAP(CSET, CDialogEx)
	
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSET::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CSET::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CSET::OnBnClickedSaveButton)
END_MESSAGE_MAP()


// CSET 消息处理程序

void CSET::OnLbnSelchangeList1()
{
	// TODO:  在此添加控件通知处理程序代码

}


void CSET::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
}

CString m_selectfonts;
int selectfonts;
int m_fontSize;
int m_CB_ModelSave;
void CSET::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//将变量保存
	UpdateData(TRUE);

	// 将用户的选择存到超全局变量中
	selectfonts	= m_comboxFonts.GetCurSel();
	GetDlgItemText(IDC_COMBO1, m_selectfonts);       // 获取选中列表项的字符串 
	m_CB_ModelSave	= m_comboModelWay.GetCurSel();
	switch (m_combo_FontSize = m_CB_FontSize.GetCurSel()){
	case 0:
		m_fontSize = 16;
	case 1:
		m_fontSize = 24;
	}

	CDialogEx::OnOK();

}

//额外的初始化代码
BOOL CSET::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 为字体选择组合框控件的列表框添加列表项 字体   
	m_comboxFonts.AddString(_T("宋体"));
	m_comboxFonts.AddString(_T("仿宋"));
	m_comboxFonts.AddString(_T("楷体"));
	m_comboxFonts.AddString(_T("黑体"));
	m_comboxFonts.AddString(_T("隶书"));  
	m_comboxFonts.SetCurSel(0);	//默认选择宋体

	// 为取模方式组合框控件添加列表项
	m_comboModelWay.AddString("横向取模，字节正序");
	m_comboModelWay.AddString("横向取模，字节倒序");
	m_comboModelWay.AddString("纵向取模，字节正序");
	m_comboModelWay.AddString("纵向取模，字节倒序");
	m_comboModelWay.SetCurSel(0);	//默认选择横向取模，字节正序

	// 为字体大小组合框控件添加列表项
	m_CB_FontSize.AddString("16*16（英文8*16）");
	m_CB_FontSize.AddString("24*24（英文16*24）");
	m_CB_FontSize.SetCurSel(0);	// 默认选择16*16

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

CString	m_SavePath;
//SAVEBUTTON的事件处理：打开文件
void CSET::OnBnClickedSaveButton()
{
	// TODO:  在此添加控件通知处理程序代码
	// 设置过滤器   
	TCHAR szFilter[] = _T("C语言文件|*.c|文本文件(*.txt)|*.txt|");
	// 构造保存文件对话框   
	CFileDialog fileDlg(FALSE, _T("doc"), _T("字模"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_SAVE_EDIT, strFilePath);
		m_SavePath = strFilePath;
	}
}
