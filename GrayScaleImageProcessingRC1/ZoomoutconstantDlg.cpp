// ZoomoutconstantDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessingRC1.h"
#include "afxdialogex.h"
#include "ZoomoutconstantDlg.h"


// CZoomoutconstantDlg 대화 상자

IMPLEMENT_DYNAMIC(CZoomoutconstantDlg, CDialog)

CZoomoutconstantDlg::CZoomoutconstantDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ZOOMOUTCONSTANT, pParent)
	, m_zoomoutconstant(0)
{

}

CZoomoutconstantDlg::~CZoomoutconstantDlg()
{
}

void CZoomoutconstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_zoomoutconstant);
}


BEGIN_MESSAGE_MAP(CZoomoutconstantDlg, CDialog)
END_MESSAGE_MAP()


// CZoomoutconstantDlg 메시지 처리기
