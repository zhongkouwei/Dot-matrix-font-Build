#pragma once
#include "afxwin.h"
#include "resource.h"

// CSET 对话框

class CSET : public CDialogEx
{
	DECLARE_DYNAMIC(CSET)

public:
	CSET(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSET();

// 对话框数据
	enum { IDD = IDD_SET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnCbnSelchangeCombo1();
	// 字体下拉框
	CString m_CBfonts;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_comboxFonts;
	afx_msg void OnBnClickedSaveButton();
	CString m_editSavepath;
	int m_CB_ModelSave;
	CComboBox m_comboModelWay;
	CComboBox m_CB_FontSize;
	int m_combo_FontSize;
};

extern  CString m_editSavepath;
extern  CString	m_SavePath;
extern  CString m_selectfonts;
extern  int m_fontSize;
extern  int m_CB_ModelSave;