#pragma once
#include "afxdialogex.h"


// CDivconstantDlg 대화 상자

class CDivconstantDlg : public CDialog
{
	DECLARE_DYNAMIC(CDivconstantDlg)

public:
	CDivconstantDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDivconstantDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIVCONSTANT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
