
// GrayScaleImageProcessingRC1Doc.cpp: CGrayScaleImageProcessingRC1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImageProcessingRC1.h"
#endif

#include "GrayScaleImageProcessingRC1Doc.h"

#include <propkey.h>
#include "ConstantDlg.h"
#include "MulconstantDlg.h"
#include "DivconstantDlg.h"
#include "GammaconstantDlg.h"
#include "ZoomoutconstantDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGrayScaleImageProcessingRC1Doc

IMPLEMENT_DYNCREATE(CGrayScaleImageProcessingRC1Doc, CDocument)

BEGIN_MESSAGE_MAP(CGrayScaleImageProcessingRC1Doc, CDocument)
END_MESSAGE_MAP()


// CGrayScaleImageProcessingRC1Doc 생성/소멸

CGrayScaleImageProcessingRC1Doc::CGrayScaleImageProcessingRC1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGrayScaleImageProcessingRC1Doc::~CGrayScaleImageProcessingRC1Doc()
{
}

BOOL CGrayScaleImageProcessingRC1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGrayScaleImageProcessingRC1Doc serialization

void CGrayScaleImageProcessingRC1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGrayScaleImageProcessingRC1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGrayScaleImageProcessingRC1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGrayScaleImageProcessingRC1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGrayScaleImageProcessingRC1Doc 진단

#ifdef _DEBUG
void CGrayScaleImageProcessingRC1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrayScaleImageProcessingRC1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGrayScaleImageProcessingRC1Doc 명령


unsigned char** CGrayScaleImageProcessingRC1Doc::OnMalloc2D(int h, int w, int initValue)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;
	retMemory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char[w];
	return retMemory;
}

double** CGrayScaleImageProcessingRC1Doc::OnMalloc3D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** retMemory;
	retMemory = new double* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new double[w];
	return retMemory;
}


void CGrayScaleImageProcessingRC1Doc::OnFree3D(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}


void CGrayScaleImageProcessingRC1Doc::OnFree2D(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}


BOOL CGrayScaleImageProcessingRC1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 선택한 파일 열기
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// (수정) 2차원배열로사용하기위함- 정방형이미지만다룸.
	double fLength = (double)File.GetLength();
	double log2Value = log(sqrt(fLength)) / log(2.0);
	if (log2Value != (int)log2Value)
	{
		AfxMessageBox(L"정방향크기의 이미지만 지원함");
		return 0;
	}
	// 기존의 메모리는 모두 해제하고, 관련값 초기화.
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 입력 이미지 크기 결정 및 메모리 할당
	m_inH = m_inW = (long)sqrt(fLength);
	m_inImage = OnMalloc2D(m_inH, m_inW, 0); // 메모리 할당
	for (int i = 0; i < m_inH; i++)
		File.Read(m_inImage[i], m_inW);
	File.Close();
	return TRUE;
}


void CGrayScaleImageProcessingRC1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;

	CDocument::OnCloseDocument();
}


void CGrayScaleImageProcessingRC1Doc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 여러 번 실행할 때, 출력 이미지 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = m_inImage[i][k];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnAddImage()
{

	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return

	// TODO: 여기에 구현 코드 추가.
	// 여러 번 실행할 때, 출력 이미지 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int value = (int)dlg.m_constant;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImage[i][k] + value > 255)
				m_outImage[i][k] = 255;
			else if (m_inImage[i][k] + value < 0)
				m_outImage[i][k] = 0;
			else 
				m_outImage[i][k] = m_inImage[i][k] + value;
		}
	}
}


BOOL CGrayScaleImageProcessingRC1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File;
	CFileDialog SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		for (int i = 0; i < m_outH; i++)
			File.Write(m_outImage[i], m_outW);
		File.Close();
	}

	return true;
}


void CGrayScaleImageProcessingRC1Doc::OnMulImage()
{
	// TODO: 여기에 구현 코드 추가.
	CMulconstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return

		// TODO: 여기에 구현 코드 추가.
		// 여러 번 실행할 때, 출력 이미지 메모리 해제
		OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int value = (int)dlg.m_Mulconstant;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImage[i][k] * value > 255)
				m_outImage[i][k] = 255;
			else if (m_inImage[i][k] * value < 0)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = m_inImage[i][k] * value;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnDivImage()
{
	// TODO: 여기에 구현 코드 추가.
	CMulconstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return

		// TODO: 여기에 구현 코드 추가.
		// 여러 번 실행할 때, 출력 이미지 메모리 해제
		OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int value = (int)dlg.m_Mulconstant;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImage[i][k] / value > 255)
				m_outImage[i][k] = 255;
			else if (m_inImage[i][k] / value < 0)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = m_inImage[i][k] / value;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnReverseImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			m_outImage[i][k] = 255 - m_inImage[i][k];
		}
	}
}		


void CGrayScaleImageProcessingRC1Doc::OnBwImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			if (m_inImage[i][k] > 127)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = 0;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	CGammaconstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return

		// TODO: 여기에 구현 코드 추가.
		// 여러 번 실행할 때, 출력 이미지 메모리 해제
		OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double value = dlg.m_gammaconstant;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = (unsigned char)pow((double)m_inImage[i][k] / 255, 1 / value) * 255;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnZoomoutImage()
{
	// TODO: 여기에 구현 코드 추가.
	CZoomoutconstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return

		// TODO: 여기에 구현 코드 추가.
		// 여러 번 실행할 때, 출력 이미지 메모리 해제
		OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double scale = dlg.m_zoomoutconstant;

	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			m_outImage[(int)(i / scale)][(int)(k / scale)] = m_inImage[i][k];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnZoominImage()
{
	// TODO: 여기에 구현 코드 추가.
	CZoomoutconstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return

	
		// TODO: 여기에 구현 코드 추가.
		// 여러 번 실행할 때, 출력 이미지 메모리 해제
		OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	double scale = dlg.m_zoomoutconstant;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = (int)(m_inH * scale);
	m_outW = (int)(m_inW * scale);
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	

	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			m_outImage[i][k] = m_inImage[(int)(i / scale)][(int)(k / scale)];
		
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnRotateImage()
{
	// TODO: 여기에 구현 코드 추가.
	CZoomoutconstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return


		// TODO: 여기에 구현 코드 추가.
		// 여러 번 실행할 때, 출력 이미지 메모리 해제
		OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;

	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double degree = dlg.m_zoomoutconstant;
	double radian = degree * 3.141592 / 180.0;


	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			int xs = i;
			int ys = k;
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW))
				m_outImage[xd][yd] = m_inImage[xs][ys];

		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnRotaterImage() //중앙+백워딩 회전
{
	// TODO: 여기에 구현 코드 추가.
	CZoomoutconstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return


		// TODO: 여기에 구현 코드 추가.
		// 여러 번 실행할 때, 출력 이미지 메모리 해제
		OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;

	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double degree = dlg.m_zoomoutconstant;
	double radian = -degree * 3.141592 / 180.0;

	int cx = m_inH / 2;
	int cy = m_inW / 2;
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			int xd = i;
			int yd = k;

			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;
			if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
				m_outImage[xd][yd] = m_inImage[xs][ys];

		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnUdImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			m_outImage[m_outH - i - 1][k] = m_inImage[i][k];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnRlImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	for (int i = 0; i < m_outH; i++)
	{
		for (int k = 0; k < m_outW; k++)
		{
			m_outImage[i][m_outW - k - 1] = m_inImage[i][k];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnStretchImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int high = m_inImage[0][0], low = m_inImage[0][0];
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (m_inImage[i][k] < low)
				low = m_inImage[i][k];
			if (m_inImage[i][k] > high)
				high = m_inImage[i][k];
		}
		
	}
	int new1, old1;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			old1 = m_inImage[i][k];
			new1 = (int)((double)(old1 - low) / (double)(high - low) * 255.0);
			if (new1 > 255)
				new1 = 255;
			if (new1 < 0)
				new1 = 0;
			m_outImage[i][k] = new1;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnEndinImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int high = m_inImage[0][0], low = m_inImage[0][0];
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			if (m_inImage[i][k] < low)
				low = m_inImage[i][k];
			if (m_inImage[i][k] > high)
				high = m_inImage[i][k];
		}

	}

	high -= 50;
	low += 50;
	int new1, old1;
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			old1 = m_inImage[i][k];
			new1 = (int)((double)(old1 - low) / (double)(high - low) * 255.0);
			if (new1 > 255)
				new1 = 255;
			if (new1 < 0)
				new1 = 0;
			m_outImage[i][k] = new1;
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnHistoequalImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int histo[256] = { 0, };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			histo[m_inImage[i][k]]++;
	// 2단계 : 누적히스토그램 생성
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	// 3단계 : 정규화된 히스토그램 생성  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++)
	{
		normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImage[i][k] = (unsigned char)normalHisto[m_inImage[i][k]];
		}
	}
}


void CGrayScaleImageProcessingRC1Doc::OnEmbossImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 엠보싱 마스크
						  { 0.0, 0.0, 0.0},
						  { 0.0, 0.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}



void CGrayScaleImageProcessingRC1Doc::OnBlurImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] =
	{
		{1. / 9, 1. / 9, 1. / 9}, // 블러링 마스크
		{1. / 9, 1. / 9, 1. / 9},
		{1. / 9, 1. / 9, 1. / 9}
	};
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnGausImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { { 1. / 16 , 1. / 8  , 1. / 16},
						  { 1. / 8, 1. / 4, 1. / 8 },
						  { 1. / 16 , 1. / 8 , 1. / 16 } };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnSharpImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { { -1 , -1  , -1 },
						  { -1 , 9  , -1 },
						  { -1 , -1  , -1 } };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnEdge1Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { {0.0, 0.0, 0.0},{-1.0, 1.0, 0.0},{0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnEdge2Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { {0.0, -1.0, 0.0},{0.0, 1.0, 0.0},{0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}

void CGrayScaleImageProcessingRC1Doc::OnEdge3Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { {0.0, -1.0, 0.0},{-1.0, 2.0, 0.0},{0.0, 0.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnRobert1Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = {{-1, 0, 0}, { 0, 1, 0 }, { 0, 0, 0 }};
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnRobert2Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { {0, 0, -1},{0, 1, 0},{0, 0, 0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnRober3Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { { -1, 0, -1},{0, 2, 0},{0, 0, 0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);

}


void CGrayScaleImageProcessingRC1Doc::OnFree1Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { { -1, -1, -1},{0, 0, 0},{1, 1, 1} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);

}


void CGrayScaleImageProcessingRC1Doc::OnFree2Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { {1, 0, -1},{1, 0, -1},{1, 0, -1 } };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);

}


void CGrayScaleImageProcessingRC1Doc::OnFree3Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { {0, -1, -2},{1, 0, -1},{2, 1, 0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);

}


void CGrayScaleImageProcessingRC1Doc::OnSobel1Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { { -1, -2, -1},{0, 0, 0},{1, 2, 1} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);

}


void CGrayScaleImageProcessingRC1Doc::OnSobel2Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = {{1, 0, -1},{2, 0, -2}, { 1, 0, -1 }};
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnSobel3Image()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { {0, -2, -2},{2, 0, -2},{2, 2, 0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnLapImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	double mask[3][3] = { {0, -1, 0},{-1, 4, -1},{0, -1, 0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 2, m_inW + 2);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 2);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnLogImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int mask[5][5] = {
							{ 0, 0, -1, 0, 0}, // 로그 마스크
							{ 0, -1, -2, -1, 0},
							{ -1, -2, 16, -2, -1},
							{ 0,-1,-2,-1,0 },
							{ 0,0,-1,0,0 }
	};
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 4, m_inW + 4);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 4; i++)
		for (int k = 0; k < m_inW + 4; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 4);
	OnFree3D(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingRC1Doc::OnDogImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 메모리 크기 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int mask[7][7] = {
						{0,0,-1,-1,-1,0,0},
						{0,-2,-3,-3,-3,-2,0},
						{0,-3,5,5,5,-3,-1},
						{-1,-3,5,16,5,-3,-1},
						{-1,-3,5,5,5,-3,-1},
						{0,-2,-3,-3,-3,-2,0},
						{0,0,-1,-1,-1,0,0},
	};
	// 임시 메모리 할당(실수형)
	double** tmpInImage = OnMalloc3D(m_inH + 6, m_inW + 6);
	double** tmpOutImage = OnMalloc3D(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 6; i++)
		for (int k = 0; k < m_inW + 6; k++)
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.

			for (int m = 0; m < 7; m++)
				for (int n = 0; n < 7; n++)
					S += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = S;
		}
	}


	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	OnFree3D(tmpInImage, m_inH + 6);
	OnFree3D(tmpOutImage, m_outH);
}
