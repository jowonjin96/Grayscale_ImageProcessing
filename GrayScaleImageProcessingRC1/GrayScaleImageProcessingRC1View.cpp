
// GrayScaleImageProcessingRC1View.cpp: CGrayScaleImageProcessingRC1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImageProcessingRC1.h"
#endif

#include "GrayScaleImageProcessingRC1Doc.h"
#include "GrayScaleImageProcessingRC1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrayScaleImageProcessingRC1View

IMPLEMENT_DYNCREATE(CGrayScaleImageProcessingRC1View, CView)

BEGIN_MESSAGE_MAP(CGrayScaleImageProcessingRC1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CGrayScaleImageProcessingRC1View::OnEqualImage)
	ON_COMMAND(IDM_ADD_IMAGE, &CGrayScaleImageProcessingRC1View::OnAddImage)
	ON_COMMAND(32777, &CGrayScaleImageProcessingRC1View::OnMulImage)
	ON_COMMAND(IDM_DIV_IMAGE, &CGrayScaleImageProcessingRC1View::OnDivImage)
	ON_COMMAND(IDM_REVERSE_IMAGE, &CGrayScaleImageProcessingRC1View::OnReverseImage)
	ON_COMMAND(ID_BW_IMAGE, &CGrayScaleImageProcessingRC1View::OnBwImage)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CGrayScaleImageProcessingRC1View::OnGammaImage)
	ON_COMMAND(IDM_ZOOMOUT_IMAGE, &CGrayScaleImageProcessingRC1View::OnZoomoutImage)
	ON_COMMAND(IDM_ZOOMIN_IMAGE, &CGrayScaleImageProcessingRC1View::OnZoominImage)
	ON_COMMAND(IDM_ROTATE_IMAGE, &CGrayScaleImageProcessingRC1View::OnRotateImage)
	ON_COMMAND(IDM_ROTATER_IMAGE, &CGrayScaleImageProcessingRC1View::OnRotaterImage)
	ON_COMMAND(IDM_UD_IMAGE, &CGrayScaleImageProcessingRC1View::OnUdImage)
	ON_COMMAND(IDM_RL_IMAGE, &CGrayScaleImageProcessingRC1View::OnRlImage)
	ON_COMMAND(IDM_STRETCH_IMAGE, &CGrayScaleImageProcessingRC1View::OnStretchImage)
	ON_COMMAND(IDM_ENDIN_IMAGE, &CGrayScaleImageProcessingRC1View::OnEndinImage)
	ON_COMMAND(IDM_HISTOEQUAL_IMAGE, &CGrayScaleImageProcessingRC1View::OnHistoequalImage)
	ON_COMMAND(IDM_EMBOSS_IMAGE, &CGrayScaleImageProcessingRC1View::OnEmbossImage)
	ON_COMMAND(IDM_BLUR_IMAGE, &CGrayScaleImageProcessingRC1View::OnBlurImage)
	ON_COMMAND(IDM_GAUS_IMAGE, &CGrayScaleImageProcessingRC1View::OnGausImage)
	ON_COMMAND(IDM_SHARP_IMAGE, &CGrayScaleImageProcessingRC1View::OnSharpImage)
	ON_COMMAND(IDM_EDGE1_IMAGE, &CGrayScaleImageProcessingRC1View::OnEdge1Image)
	ON_COMMAND(IDM_EDGE2_IMAGE, &CGrayScaleImageProcessingRC1View::OnEdge2Image)
	ON_COMMAND(IDM_EDGE3_IMAGE, &CGrayScaleImageProcessingRC1View::OnEdge3Image)
	ON_COMMAND(IDM_ROBERT1_IMAGE, &CGrayScaleImageProcessingRC1View::OnRobert1Image)
	ON_COMMAND(IDM_ROBERT2_IMAGE, &CGrayScaleImageProcessingRC1View::OnRobert2Image)
	ON_COMMAND(IDM_ROBER3_IMAGE, &CGrayScaleImageProcessingRC1View::OnRober3Image)
	ON_COMMAND(IDM_FREE1_IMAGE, &CGrayScaleImageProcessingRC1View::OnFree1Image)
	ON_COMMAND(IDM_FREE2_IMAGE, &CGrayScaleImageProcessingRC1View::OnFree2Image)
	ON_COMMAND(IDM_FREE3_IMAGE, &CGrayScaleImageProcessingRC1View::OnFree3Image)
	ON_COMMAND(IDM_SOBEL1_IMAGE, &CGrayScaleImageProcessingRC1View::OnSobel1Image)
	ON_COMMAND(IDM_SOBEL2_IMAGE, &CGrayScaleImageProcessingRC1View::OnSobel2Image)
	ON_COMMAND(IDM_SOBEL3_IMAGE, &CGrayScaleImageProcessingRC1View::OnSobel3Image)
	ON_COMMAND(IDM_LAP_IMAGE, &CGrayScaleImageProcessingRC1View::OnLapImage)
	ON_COMMAND(IDM_LOG_IMAGE, &CGrayScaleImageProcessingRC1View::OnLogImage)
	ON_COMMAND(IDM_DOG_IMAGE, &CGrayScaleImageProcessingRC1View::OnDogImage)
END_MESSAGE_MAP()

// CGrayScaleImageProcessingRC1View 생성/소멸

CGrayScaleImageProcessingRC1View::CGrayScaleImageProcessingRC1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGrayScaleImageProcessingRC1View::~CGrayScaleImageProcessingRC1View()
{
}

BOOL CGrayScaleImageProcessingRC1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGrayScaleImageProcessingRC1View 그리기

void CGrayScaleImageProcessingRC1View::OnDraw(CDC* pDC)
{
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_inH; i++) {
		for (k = 0; k < pDoc->m_inW; k++) {
			R = G = B = pDoc->m_inImage[i][k];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_outH; i++) {
		for (k = 0; k < pDoc->m_outW; k++) {
			R = G = B = pDoc->m_outImage[i][k];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(pDoc->m_inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();


}


// CGrayScaleImageProcessingRC1View 인쇄

BOOL CGrayScaleImageProcessingRC1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGrayScaleImageProcessingRC1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGrayScaleImageProcessingRC1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGrayScaleImageProcessingRC1View 진단

#ifdef _DEBUG
void CGrayScaleImageProcessingRC1View::AssertValid() const
{
	CView::AssertValid();
}

void CGrayScaleImageProcessingRC1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrayScaleImageProcessingRC1Doc* CGrayScaleImageProcessingRC1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrayScaleImageProcessingRC1Doc)));
	return (CGrayScaleImageProcessingRC1Doc*)m_pDocument;
}
#endif //_DEBUG


// CGrayScaleImageProcessingRC1View 메시지 처리기


void CGrayScaleImageProcessingRC1View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnAddImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnMulImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnMulImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnDivImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnDivImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnReverseImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnReverseImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnBwImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnBwImage();
	Invalidate(TRUE);

}


void CGrayScaleImageProcessingRC1View::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnGammaImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnZoomoutImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnZoomoutImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnZoominImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnZoominImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRotateImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnRotateImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRotaterImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnRotaterImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnUdImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnUdImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRlImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnRlImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnStretchImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnStretchImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEndinImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnStretchImage();
	Invalidate(TRUE);
}



void CGrayScaleImageProcessingRC1View::OnHistoequalImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnHistoequalImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEmbossImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnEmbossImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnBlurImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnBlurImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnGausImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnGausImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnSharpImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnSharpImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEdge1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnEdge1Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEdge2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnEdge2Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnEdge3Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnEdge3Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRobert1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnRobert1Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRobert2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnRobert2Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnRober3Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnRober3Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnFree1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnFree1Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnFree2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnFree2Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnFree3Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnFree3Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnSobel1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnSobel1Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnSobel2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnSobel2Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnSobel3Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnSobel3Image();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnLapImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnLapImage();
	Invalidate(TRUE);
}



void CGrayScaleImageProcessingRC1View::OnLogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnLogImage();
	Invalidate(TRUE);
}


void CGrayScaleImageProcessingRC1View::OnDogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingRC1Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnDogImage();
	Invalidate(TRUE);

}
