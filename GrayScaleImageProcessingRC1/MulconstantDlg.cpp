// MulconstantDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessingRC1.h"
#include "afxdialogex.h"
#include "MulconstantDlg.h"


// CMulconstantDlg 대화 상자

IMPLEMENT_DYNAMIC(CMulconstantDlg, CDialog)

CMulconstantDlg::CMulconstantDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MULCONSTANT, pParent)
	, m_Mulconstant(0)
{

}

CMulconstantDlg::~CMulconstantDlg()
{
}

void CMulconstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Mulconstant);
	DDV_MinMaxDouble(pDX, m_Mulconstant, 0, 25);
}


BEGIN_MESSAGE_MAP(CMulconstantDlg, CDialog)
END_MESSAGE_MAP()


// CMulconstantDlg 메시지 처리기
