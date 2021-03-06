
// ViewerDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Viewer.h"
#include "ViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

unsigned char** MemAlloc2D(int nHeight, int nWidth, unsigned char nInitVal) {
	unsigned char** rtn = new unsigned char*[nHeight];
	for (int n = 0; n < nHeight; n++) {
		rtn[n] = new unsigned char[nWidth];
		memset(rtn[n], nInitVal, sizeof(unsigned char) * nWidth);
	}
	return rtn;
}
void MemFree2D(unsigned char** Mem, int nHeight) {
	for (int n = 0; n < nHeight; n++) {
		delete[] Mem[n];
	}
	delete[] Mem;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CViewerDlg 대화 상자



CViewerDlg::CViewerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE_IN, m_PicOri);
	DDX_Control(pDX, IDC_PICTURE_OUT, m_PicProc);
}

BEGIN_MESSAGE_MAP(CViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_FILEOPEN, &CViewerDlg::OnFileOpenBtnClick)
	ON_COMMAND(ID_FILE_FILECLOSE, &CViewerDlg::OnCloseMenuClick)
	ON_COMMAND(ID_EDIT_CONVERT, &CViewerDlg::OnConvertgrayBtnClick)
	ON_COMMAND(ID_EDIT_SCALING, &CViewerDlg::OnEditScalingClick)
	ON_COMMAND(ID_EDIT_ROTATION, &CViewerDlg::OnEditRotationClick)
	ON_COMMAND(ID_HISTOGRAM_GETHISTOGRAM, &CViewerDlg::OnHistogramGetClick)
	ON_COMMAND(ID_HISTOGRAM_HISTOGRAMEQUALIZATION, &CViewerDlg::OnHistogramEqualizationClicked)
	ON_COMMAND(ID_HISTOGRAM_HISTOGRAMMATCHING, &CViewerDlg::OnHistogramMatchingClicked)
	ON_COMMAND(ID_EDIT_FILTER, &CViewerDlg::OnEditFilterClicked)
	ON_COMMAND(ID_NOISEREDUCTION_ADD, &CViewerDlg::OnNoisereductionAdd)
	ON_COMMAND(ID_NOISEFILTERING_MEANFILTER,&CViewerDlg::OnNoisefilteringMeafilterClicked)
	ON_COMMAND(ID_NOISEREDUCTION_GETPSNR, &CViewerDlg::OnGetpsnr)
END_MESSAGE_MAP()


// CViewerDlg 메시지 처리기

BOOL CViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CViewerDlg::DisplayImage(Mat DispMat, bool blnOut) {
	if (blnOut) {
		GetDlgItem(IDC_PICTURE_IN)->GetWindowRect(rect);
		ScreenToClient(rect);
		m_pDC = m_PicOri.GetDC();
		m_PicOri.GetClientRect(&rect);
	}
	else {
		GetDlgItem(IDC_PICTURE_OUT)->GetWindowRect(rect);
		ScreenToClient(rect);
		m_pDC = m_PicProc.GetDC();
		m_PicProc.GetClientRect(&rect);
	}
	IplImage* Ori = &IplImage(DispMat);
	IplImage* Resize = NULL;

	ResizeImage(Ori, &Resize, &rect);
	DisplayBitmap(m_pDC, rect, Resize);
}
void CViewerDlg::DisplayBitmap(CDC* pDC, CRect rect, IplImage* DisplplImage) {
	BITMAPINFO bitmapInfo;
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	bitmapInfo.bmiHeader.biXPelsPerMeter = 100;
	bitmapInfo.bmiHeader.biYPelsPerMeter = 100;
	bitmapInfo.bmiHeader.biClrUsed = 0;
	bitmapInfo.bmiHeader.biClrImportant = 0;
	bitmapInfo.bmiHeader.biSizeImage = 0;
	bitmapInfo.bmiHeader.biWidth = DisplplImage->width;
	bitmapInfo.bmiHeader.biHeight = DisplplImage->height;

	if (DisplplImage->nChannels == 3) {
		IplImage* ReverseImg = cvCreateImage(CvSize(DisplplImage->width, DisplplImage->height), 8, 3);
		for (int h = 0; h < DisplplImage->height; h++) {
			for (int w = 0; w < DisplplImage->width; w++) {
				ReverseImg->imageData[h*DisplplImage->widthStep + w * 3] = DisplplImage->imageData[(DisplplImage->height - h) * DisplplImage->widthStep + w * 3];
				ReverseImg->imageData[h*DisplplImage->widthStep + w * 3 + 1] = DisplplImage->imageData[(DisplplImage->height - h) * DisplplImage->widthStep + w * 3 + 1];
				ReverseImg->imageData[h*DisplplImage->widthStep + w * 3 + 2] = DisplplImage->imageData[(DisplplImage->height - h) * DisplplImage->widthStep + w * 3 + 2];
			}
		}

		bitmapInfo.bmiHeader.biBitCount = DisplplImage->depth * DisplplImage->nChannels;
		pDC->SetStretchBltMode(COLORONCOLOR);
		::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.right, rect.bottom,
			0, 0, DisplplImage->width, DisplplImage->height, ReverseImg->imageData, &bitmapInfo,
			DIB_RGB_COLORS, SRCCOPY);

		cvReleaseImage(&ReverseImg);
	}
	else {
		IplImage* ReverseImg = cvCreateImage(cvGetSize(DisplplImage), DisplplImage->depth, 1);

		for (int h = 0; h < DisplplImage->height; h++) {
			for (int w = 0; w < DisplplImage->width; w++) {
				ReverseImg->imageData[h*DisplplImage->widthStep + w] = DisplplImage->imageData[(DisplplImage->height - h)*DisplplImage->widthStep + w];
			}
		}
		IplImage * tmp = cvCreateImage(cvGetSize(DisplplImage), DisplplImage->depth, 3);
		cvCvtColor(ReverseImg, tmp, CV_GRAY2BGR);

		bitmapInfo.bmiHeader.biBitCount = tmp->depth * tmp->nChannels;
		pDC->SetStretchBltMode(COLORONCOLOR);
		::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.right, rect.bottom, 0, 0, tmp->width, tmp->height, tmp->imageData, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
		cvReleaseImage(&ReverseImg);
		cvReleaseImage(&tmp);
	}
}
void CViewerDlg::ResizeImage(IplImage* src, IplImage** dst, CRect* rect) {
	int ndst_width = 0, ndst_height = 0;
	//먼저, 영상의 가로와 세로 중 장축을 구한다.
	if (src->width > src->height) {
		ndst_width = rect->Width();
		ndst_height = (src->height * rect->Width()) / src->width;

	}
	else {
		ndst_width = (src->width * rect->Height()) / src->height;
		ndst_height = rect->Height();
	}
	(*dst) = cvCreateImage(cvSize(ndst_width, ndst_height), IPL_DEPTH_8U, src->nChannels);

	cvResize(src, (*dst));
	rect->right = rect->left + ndst_width;
	rect->bottom = rect->top + ndst_height;
}

bool CViewerDlg::isInsideBoundary(int nHeight, int nWidth, double h, double w)
{
	return h >= 0 && w >= 0 && h < nHeight && w < nWidth;
}

unsigned char CViewerDlg::BilinearInterpolation(unsigned char ** In, int nHeight_Ori, int nWidth_Ori, double h_Cvt, double w_Cvt)
{
	unsigned char out;
	double h1 = floor(h_Cvt);
	double h2 = ceil(h_Cvt);
	if (h2 >= nHeight_in)
		h2 = nHeight_in-1;
	double w1 = floor(w_Cvt);
	double w2 = ceil(w_Cvt);
	if (w2 >= nWidth_in)
		w2 = nWidth_in-1;
	
	Point p1 = Point(h1, w1);
	Point p2 = Point(h1, w2);
	Point p3 = Point(h2, w1);
	Point p4 = Point(h2, w2);

	Point r1 = Point(floor(h_Cvt), w_Cvt);
	unsigned char r1_interpolation = getLinearInterpolation(h_Cvt, w_Cvt, p1, p2,ch_in_gray[p1.x][p1.y],ch_in_gray[p2.x][p2.y]);
	Point r2 = Point(ceil(h_Cvt), w_Cvt);
	unsigned char r2_interpolation = getLinearInterpolation(h_Cvt, w_Cvt, p3, p4, ch_in_gray[p3.x][p3.y], ch_in_gray[p4.x][p4.y]);
	return  getLinearInterpolation(h_Cvt, w_Cvt, r1, r2, r1_interpolation, r2_interpolation);
}

unsigned char CViewerDlg::getLinearInterpolation(double h_Cvt, double w_Cvt, Point p1, Point p2,unsigned char pixel1, unsigned char pixel2) {
	Point ori = Point(w_Cvt, h_Cvt);
	//ch_in_gray[x][y]
	//->x, w,
	//->y, h
	double d1 = getDistance(ori, p1);
	double d2 = getDistance(p2, ori);
	if (d1 + d2 == 0) {
		return pixel1;
	}
	else {
		return d2 / (d1 + d2)*pixel1 + d1 / (d1 + d2)*pixel2;
	}

}

double CViewerDlg::getDistance(Point p1, Point p2) {
	const double x_diff = p1.x - p2.x;
	const double y_diff = p1.y - p2.y;
	return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}



unsigned char CViewerDlg::BicubicInterpolation(unsigned char ** In, int nHeight_Ori, int nWidth_Ori, double h_Cvt, double w_Cvt)
{
	Point p[4][4];
	Point processedPoint[4];

	if (h_Cvt == 100 && w_Cvt == 100) {
		std::cout << "";
	}
	for (int xi = 0; xi < 4; xi++) {
		for (int yi = 0; yi < 4; yi++) {
			p[xi][yi] = calPosition(xi, yi, h_Cvt, w_Cvt);
		}
	}
	unsigned char cubicValue[4];
	for (int i = 0; i < 4; i++) {
		cubicValue[i] = CubicInterpolation(p[i], w_Cvt);
		processedPoint[i].x = roundPosition(i, h_Cvt, nHeight_in);
		processedPoint[i].y = w_Cvt; 
	}
	unsigned char out = CubicInterpolation(processedPoint, h_Cvt);
	return out;
}

unsigned char CViewerDlg::CubicInterpolation(Point p[],double target) {
	unsigned char v[4];
	for (int i = 0; i < 4; i++) {
		v[i] = ch_in_gray[p[i].x][p[i].y];
	}
	/*
	-1/6  1/2 -1/2   1/6
	 1/2   -1  1/2     0
	-1/3 -1/2    1  -1/6
	   0    1    0     0
	*/
	//ax^3 + bx^2 + cx + d
	double a, b, c, d;
	a = -1 / 6 * v[0] + v[1] / 2 - v[2] / 2 + v[3] / 6;
	b = v[0] / 2 - v[1] + v[2] / 2;
	c = -1 / 3 * v[0] - v[1] / 2 + v[2] - v[3] / 6;
	d = v[1];

	return (unsigned char)cubicFunction(a, b, c, d, target-floor(target));
}

double CViewerDlg::cubicFunction(double a, double b, double c, double d, double x) {
	return a * x*x*x + b * x*x + c * x + d;
}
Point CViewerDlg::calPosition(int xi, int yi, double h_Cvt, double w_Cvt) {
	int calX, calY;
	calX = roundPosition(xi, w_Cvt, nWidth_in);
	calY = roundPosition(yi, h_Cvt, nHeight_in);
	return Point(calX, calY);
}

int CViewerDlg::roundPosition(int index, double originPosition, int boundary) {
	int out;
	out = roundPosition(index, originPosition);
	
	if (out < 0)
		return 0;
	else if (out >= boundary)
		return boundary - 1;
	else
		return out;
}

int CViewerDlg::roundPosition(int index, double originPosition) {
	switch (index) {
	case 0:
		return floor(originPosition) - 1;
	case 1:
		return floor(originPosition);
	case 2:
		return ceil(originPosition);
	case 3:
		return ceil(originPosition) + 1;
	default:
		return originPosition;
	}
}

void CViewerDlg::OnFileOpenBtnClick()
{
	CFileDialog dlg(TRUE);
	if (isImageOpened) {
		if (ch_in_1 != NULL) {
			MemFree2D(ch_in_1, nHeight_in);
		}
		if (ch_in_2 != NULL) {
			if (nFormat == FORMAT_YUV420) {
				MemFree2D(ch_in_2, nHeight_in / 2);

			}
			else MemFree2D(ch_in_2, nHeight_in);
		}
		if (ch_in_3 != NULL) {
			if (nFormat == FORMAT_YUV420) {
				MemFree2D(ch_in_3, nHeight_in / 2);
			}
			else MemFree2D(ch_in_3, nHeight_in);
		}
		if (ch_in_gray != NULL) {
			MemFree2D(ch_in_gray, nHeight_in);
		}
	}
	if (dlg.DoModal() == IDOK) {
		if (dlg.GetFileExt() != "jpg"&&dlg.GetFileExt() != "JPG"&&dlg.GetFileExt() != "raw"&&dlg.GetFileExt() != "yuv") {
			MessageBox("JPG 또는 YUV,Gray 파일이 아닙니다.");
			return;

		}
		InpFileName = dlg.GetFileTitle();
		if (dlg.GetFileExt() == "jpg" || dlg.GetFileExt() == "JPG") {
			Ori_Img = imread((const char*)dlg.GetPathName());
			nHeight_in = Ori_Img.rows;
			nWidth_in = Ori_Img.cols;
			if (Ori_Img.channels() == 3) {
				ch_in_1 = MemAlloc2D(nHeight_in, nWidth_in, 0);
				ch_in_2 = MemAlloc2D(nHeight_in, nWidth_in, 0);
				ch_in_3 = MemAlloc2D(nHeight_in, nWidth_in, 0);

				for (int h = 0; h < nHeight_in; h++) {
					for (int w = 0; w < nWidth_in; w++) {
						Vec3b RGB = Ori_Img.at<Vec3b>(h, w);
						ch_in_1[h][w] = RGB[2];
						ch_in_2[h][w] = RGB[1];
						ch_in_3[h][w] = RGB[0];
					}
				}
				nFormat = FORMAT_RGB;
			}
			else { //Gray Image(JPG)
				ch_in_gray = MemAlloc2D(nHeight_in, nWidth_in, 0);
				for (int h = 0; h < nHeight_in; h++) {
					for (int w = 0; w < nWidth_in; w++) {
						ch_in_gray[h][w] = Ori_Img.at<unsigned char>(h, w);
					}
				}
				nFormat = FORMAT_GRAY;
			}
			isImageOpened = true;
			DisplayImage(Ori_Img, true);
		}
		else {
			//RAW File & YUV File
			//RawOpenDlg를 통하여 Raw 파일의 정보를 입력받는다.
			CRawInfoDlg RawInfoDlg;
			if (RawInfoDlg.DoModal() == IDOK) {
				nHeight_in = RawInfoDlg.GetRawHeight();
				nWidth_in = RawInfoDlg.GetRawWidth();
				nFormat = RawInfoDlg.GetRawFormat();

				if (nHeight_in == 0 || nWidth_in == 0) {
					MessageBox("값을 잘못 입력하셨습니다");
					return;
				}
				FILE *fp_in;

				fopen_s(&fp_in, (const char*)dlg.GetPathName(), "rb");
				if (nFormat == FORMAT_GRAY) {
					ch_in_gray = MemAlloc2D(nHeight_in, nWidth_in, 0);
					for (int h = 0; h < nHeight_in; h++) {
						fread(ch_in_gray[h], sizeof(unsigned char), nWidth_in, fp_in);
					}
					Ori_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
					for (int h = 0; h < nHeight_in; h++) {
						for (int w = 0; w < nWidth_in; w++) {
							Ori_Img.at<unsigned char>(h, w) = ch_in_gray[h][w];
						}
					}
				}
				else if (nFormat == FORMAT_YUV444) {
					ch_in_1 = MemAlloc2D(nHeight_in, nWidth_in, 0);
					ch_in_2 = MemAlloc2D(nHeight_in, nWidth_in, 0);
					ch_in_3 = MemAlloc2D(nHeight_in, nWidth_in, 0);

					for (int h = 0; h < nHeight_in; h++) {
						fread(ch_in_1, sizeof(unsigned char), nWidth_in, fp_in);
					}
					for (int h = 0; h < nHeight_in; h++) {
						fread(ch_in_2, sizeof(unsigned char), nWidth_in, fp_in);
					}
					for (int h = 0; h < nHeight_in; h++) {
						fread(ch_in_3, sizeof(unsigned char), nWidth_in, fp_in);
					}
				}
				else {
					ch_in_1 = MemAlloc2D(nHeight_in, nWidth_in, 0);
					ch_in_2 = MemAlloc2D(nHeight_in/2, nWidth_in/2, 0);
					ch_in_3 = MemAlloc2D(nHeight_in/2, nWidth_in/2, 0);
					for (int h = 0; h < nHeight_in; h++) {
						fread(ch_in_1, sizeof(unsigned char), nWidth_in, fp_in);
					}
					for (int h = 0; h < nHeight_in/2; h++) {
						fread(ch_in_2, sizeof(unsigned char), nWidth_in, fp_in);
					}
					for (int h = 0; h < nHeight_in/2; h++) {
						fread(ch_in_3, sizeof(unsigned char), nWidth_in, fp_in);
					}
				}
				fclose(fp_in);
				isImageOpened = true;
				DisplayImage(Ori_Img, true);

			}
		}
	}
}


void CViewerDlg::OnCloseMenuClick()
{
	if (isImageOpened) {
		if (ch_in_1 != NULL) {
			MemFree2D(ch_in_1, nHeight_in);
		}
		if (ch_in_2 != NULL) {
			if (nFormat == FORMAT_YUV420) {
				MemFree2D(ch_in_2, nHeight_in/2);
			}else
				MemFree2D(ch_in_2, nHeight_in);
		}
		if (ch_in_3 != NULL) {
			if (nFormat == FORMAT_YUV420) {
				MemFree2D(ch_in_3, nHeight_in / 2);
			}
			else
				MemFree2D(ch_in_3, nHeight_in);
		}
		if (ch_in_1 != NULL) {
			MemFree2D(ch_in_gray, nHeight_in);
		}
	}
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}


void CViewerDlg::OnConvertgrayBtnClick()
{
	if (isImageOpened) {
		if (nFormat == FORMAT_GRAY) {
			MessageBox("입력 영상이 회색조 영상입니다.");
			return;
		}
if (nFormat == FORMAT_YUV444 || nFormat == FORMAT_YUV420) {
	Proc_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
	for (int h = 0; h < nHeight_in; h++) {
		for (int w = 0; w < nWidth_in; w++) {
			Proc_Img.at<unsigned char>(h, w) = ch_in_1[h][w];
		}
	}
	DisplayImage(Proc_Img, false);
	return;
}
if (nFormat == FORMAT_RGB) {
	if (ch_in_gray == NULL) {
		ch_in_gray = MemAlloc2D(nHeight_in, nWidth_in, 0);

	}
	for (int h = 0; h < nHeight_in; h++) {
		for (int w = 0; w < nWidth_in; w++) {
			ch_in_gray[h][w] = saturate_cast<unsigned char>(0.299 * ch_in_1[h][w] + 0.587*ch_in_2[h][w] + 0.114*ch_in_3[h][w]);
		}
	}
	Proc_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
	for (int h = 0; h < nHeight_in; h++) {
		for (int w = 0; w < nWidth_in; w++) {
			Proc_Img.at<unsigned char>(h, w) = ch_in_gray[h][w];
		}
	}
	DisplayImage(Proc_Img, false);
	return;
}
else {
	MessageBox("불러온 영상이 없습니다.");
}
	}
}


void CViewerDlg::OnEditScalingClick()
{
	if (isImageOpened && nFormat == FORMAT_GRAY)//영상이 열려있고, 영상 포맷이 GRAY일떄
	{

		if (ImgScalingDlg.DoModal() == IDOK)//스케일링 정보를 받아옴
		{
			int nInterpolationType = ImgScalingDlg.GetInterpType();//보간 타입
			double dScaleRate = ImgScalingDlg.GetScaleRate();//스케일링 비율
			if (dScaleRate < 1 || dScaleRate > 2)//스케일링 비율이 잘못되었을경우
			{
				MessageBox("스케일링 범위가 잘못 되었습니다.");
				return;
			}
			//Scaling후 영상의 크기 계산
			int nHeight_Scale = nHeight_in * dScaleRate;
			int nWidth_Scale = nWidth_in * dScaleRate;

			//스케일링 결과를 담을 2차원 unsigned char형 배열
			unsigned char** Out = MemAlloc2D(nHeight_Scale, nWidth_Scale, 0);

			for (int h = 0; h < nHeight_Scale; h++) {
				for (int w = 0; w < nWidth_Scale; w++) {
					double h_Ori = h / dScaleRate;
					double w_Ori = w / dScaleRate;
					if (nInterpolationType == BILINEAR) {
						Out[h][w] = BilinearInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Ori, w_Ori);

					}
					else {
						Out[h][w] = BicubicInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Ori, w_Ori);
					}
				}
			}
			Ori_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
			Proc_Img = Mat(nHeight_Scale, nWidth_Scale, CV_8UC1);


			for (int h = 0; h < nHeight_in; h++) {
				for (int w = 0; w < nWidth_in; w++) {
					Ori_Img.at<unsigned char>(h, w) = ch_in_gray[h][w];

				}
			}
			for (int h = 0; h < nHeight_Scale; h++) {
				for (int w = 0; w < nWidth_Scale; w++) {
					Proc_Img.at<unsigned char>(h, w) = Out[h][w];
				}
			}
			imshow("Original Image", Ori_Img);
			imshow("Scaled Image", Proc_Img);
			waitKey(0);
		}
		else {
			MessageBox("불러온 영상이 없거나 영상 포맷이 회색조 영상이 아닙니다.");
		}
	}
}


void CViewerDlg::OnEditRotationClick()
{
	//영상이 열려 있을 때 & 영상 포맷이 Gray(1Channel)일 때만 실행
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		if(RotationDlg.DoModal() == IDOK){
			//보간 타입
			int nInterpolationType = RotationDlg.GetInterpolationType();
			//회전각도
			int nAngle = RotationDlg.GetAngle();

			//회전 각도 범위가 잘못 되었을 경우 실행하지 않음
			if (nAngle < 0 || nAngle>360) {
				MessageBox("회전 범위가 잘못 되었습니다.");
				return;
			}
			//회전 결과를 담을 2차원 unsigned char 형 배열
			unsigned char** Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

			int nHeight_2 = nHeight_in / 2;
			int nWidth_2 = nWidth_in / 2;
			double h_Rotate = 0;
			double w_Rotate = 0;

			for (int h = 0; h < nHeight_in; h++) {
				for (int w = 0; w < nWidth_in; w++) {
					//회전 좌표 계산 x, w / y,h
					Point rotatedPoint = rotatePoint(Point(w, h), nAngle, nWidth_2, nHeight_2);
					double h_Rotate = rotatedPoint.y;
					double w_Rotate = rotatedPoint.x;

					if (isInsideBoundary(nHeight_in, nWidth_in, h_Rotate, w_Rotate)) {
						if (nInterpolationType == BILINEAR) {
							Out[h][w] = BilinearInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Rotate, w_Rotate);
						}
						else//Bicubic
							Out[h][w] = BicubicInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Rotate, w_Rotate);
					}
				}
			}
			Proc_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
			for (int h = 0; h < nHeight_in; h++) {
				for (int w = 0; w < nWidth_in; w++) {
					Proc_Img.at<unsigned char>(h, w) = Out[h][w];
				}
			}
			DisplayImage(Proc_Img, false);
			MemFree2D(Out, nHeight_in);
		}
		else {
			MessageBox("불러온 영상이 없거나 영상 포맷이 회색조 영상이 아닙니다.");
		}
	}

}
Point CViewerDlg::rotatePoint(Point p, int angle,int nWidth_2, int nHeight_2)
{
	double theta = angle * M_PI / 180.0;
	double c = cos(theta);
	double s = sin(theta);
	double movedX = p.x - nWidth_2;
	double movedY = p.y - nHeight_2;

	return Point(c*movedX - s * movedY + nWidth_2, s*movedX + c * movedY + nHeight_2);
}

void CViewerDlg::InputGaussianNoise(unsigned char ** In, unsigned char ** Out, int nHeight, int nWidth, float fMean, float fStdev)
{
	float fTemp = 0, fPDF[256] = { 0.0f };
	GetGaussianPDF(fPDF, 256, fMean, fStdev);
	srand(GetTickCount());
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			fTemp = (float)In[h][w] + GetNoise(fPDF, 256);
			Out[h][w] = static_cast<unsigned char>(fTemp);
		}
	}
}

void CViewerDlg::InputSaltPepperNoise(unsigned char ** In, unsigned char ** Out, int nHeight, int nWidth, float fSProb, float fPProb)
{
	float Low = fSProb;
	float High = 1.0f - fPProb;
	float fRand;

	srand(GetTickCount());
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			fRand = ((float)rand() / RAND_MAX);
			if (fRand < Low) {
				Out[h][w] = 255;
			}
			else if (fRand > High) {
				Out[h][w] = 0;
			}
			else
				Out[h][w] = In[h][w];
		}
	}
}

void CViewerDlg::GetGaussianPDF(float * EmptyPDF, int nLength, float fMean, float fStDev)
{
	int n;
	int Center = nLength / 2;
	float x;
	for (n = 0; n < nLength; n++) {
		x = (float)(n - Center);
		EmptyPDF[n] = (1 / ((float)sqrt(2 * M_PI)*fStDev)) * exp(-pow(x - fMean, 2) / (2 * fStDev*fStDev));
	}
}

float CViewerDlg::GetNoise(float * PDF, int nLength)
{
	int n;
	int Center = nLength / 2;
	float fRand, fComp, fTemp = 0;
	float x = 0, fDiff;
	float* CDF = new float[nLength];
	CDF[0] = 0;
	fRand = (float)rand() / (RAND_MAX + 1);
	for (n = 1; n < nLength; n++) {
		CDF[n] = (PDF[n] + PDF[n - 1]) / 2 + CDF[n - 1];
		fDiff = fRand - CDF[n];
		if (fDiff < 0) {
			x = ((float)n - Center);
			break;
		}
	}
	fComp = (fRand - CDF[n - 1]) / (CDF[n] - CDF[n - 1]);
	delete[] CDF;
	return x + fComp;
}

void CViewerDlg::OnHistogramGetClick()
{
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		if (Hist == NULL) {
			Hist = new int[256];
		}
		memset(Hist, 0, sizeof(int) * 256);

		//Get Histogram
		for (int h = 0; h < nHeight_in; h++) {
			for (int w = 0; w < nWidth_in; w++) {
				Hist[ch_in_gray[h][w]]++;
			}
		}

		//Normalize Histogram & Display
		int nMax = 0;
		for (int n = 0; n < 256; n++) {
			if (nMax < Hist[n]) {
				nMax = Hist[n];
			}
		}

		double dNormalizeFactor = 255.0 / nMax;

		Mat HistDisp = Mat(256, 256, CV_8UC1);
		HistDisp = Scalar::all(0);

		for (int w = 0; w < 256; w++) {
			int nNormalizedValue = (int)Hist[w] * dNormalizeFactor;
			for (int h = 255; h > 255 - nNormalizedValue; h--) {
				HistDisp.at<unsigned char>(h, w) = 255;
			}
		}
		imshow("Histogram of Input Image", HistDisp);
		waitKey(0);
	}
}


void CViewerDlg::OnHistogramEqualizationClicked()
{
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		if (Hist == NULL) {
			Hist = new int[256];
		}
		memset(Hist, 0, sizeof(int) * 256);

		//Get Histogram
		for (int h = 0; h < nHeight_in; h++) {
			for (int w = 0; w < nWidth_in; w++) {
				Hist[ch_in_gray[h][w]]++;
			}
		}
		//Histogram Equalization
		double Hist_CDF[256] = { 0.0 };
		Mat Eq_Img = Mat(256, 256, CV_8UC1);

		//TODO : Implemenet
		Hist_CDF[0] = Hist[0] / (double)(nHeight_in*nWidth_in);
		for (int i = 1; i < 256; i++) {
			Hist_CDF[i] = Hist_CDF[i - 1] + Hist[i]/(double)(nHeight_in*nWidth_in);
			
		}

		for (int h = 0; h < nHeight_in; h++) {
			for (int w = 0; w < nWidth_in; w++) {
				unsigned char pixel = ch_in_gray[h][w];
				Eq_Img.at<unsigned char>(h, w) = round(Hist_CDF[pixel] * 255);
			}
		}

		//Display_Result
		int* Hist_Eq = new int[256];
		memset(Hist_Eq, 0, sizeof(int) * 256);

		for (int h = 0; h < nHeight_in; h++) {
			for (int w = 0; w < nWidth_in; w++) {
				Hist_Eq[Eq_Img.at<unsigned char>(h, w)]++;
			}
		}
		DisplayImage(Eq_Img, false);
		DisplayHistogram(Hist);
		DisplayHistogram(Hist_Eq);

		delete[] Hist_Eq;
	}
}
void DisplayHistogram(int* Hist) {
	int nMax = 0;
	for (int n = 0; n < 256; n++) {
		if (nMax < Hist[n]) {
			nMax = Hist[n];
		}
	}

	double dNormalizeFactor = 255.0 / nMax;
	Mat HistDisp = Mat(256, 256, CV_8UC1);
	HistDisp = Scalar::all(0);

	for (int w = 0; w < 256; w++) {
		int nNormalizedValue = (int)Hist[w] * dNormalizeFactor;
		for (int h = 255; h > 255 - nNormalizedValue; h--) {
			HistDisp.at<unsigned char>(h, w) = 255;
		}
	}
	imshow("Histogram", HistDisp);
	waitKey(0);
}

void CViewerDlg::OnHistogramMatchingClicked()
{
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		if (Hist == NULL) {
			Hist = new int[256];
		}
		memset(Hist, 0, sizeof(int) * 256);

		//Get Histogram
		for (int h = 0; h < nHeight_in; h++) {
			for (int w = 0; w < nWidth_in; w++) {
				Hist[ch_in_gray[h][w]]++;
			}
		}
		//Histogram Equalization
		
		//선언 & 초기화
		Mat MatchImg(256, 256, CV_8UC1), RefImg(nHeight_in, nWidth_in, CV_8UC1);
		int Hist_Ref[256] = { 0 };
		int Hist_Mat[256] = { 0 };
		float Hist_CDF[256], Hist_CDF_Ref[256];

		MatchImg = Scalar::all(0);
		RefImg = Scalar::all(0);

		//Reference 영상 생성 및 히스토그램 계산

		srand(GetTickCount());
		for (int h = 0; h < RefImg.rows; h++) {
			for (int w = 0; w < RefImg.cols; w++) {
				RefImg.at<unsigned char>(h, w) = (unsigned char)rand() % 255;
				Hist_Ref[RefImg.at<unsigned char>(h, w)]++;
			}
		}

		//CDF 구하기
		Hist_CDF[0] = (double)Hist[0] / (nHeight_in * nWidth_in);
		Hist_CDF_Ref[0] = (double)Hist_Ref[0] / (nHeight_in * nWidth_in);
		for (int n = 1; n < 256; n++) {
			Hist_CDF[n] = (double)Hist[n] / (nHeight_in * nWidth_in) + Hist_CDF[n - 1];
			Hist_CDF_Ref[n] = (double)Hist_Ref[n] / (nHeight_in * nWidth_in) + Hist_CDF_Ref[n - 1];

		}
		//input : cdf(0~1), output : pixel
		unsigned char LUT[101] = { 0 };
		int findIndex=0;
		for (int i = 0; i < 256; i++) {
			//REf       Source
			//int currentSource = Hist_CDF[i] * 100;
			int currentSource = (Hist_CDF[i] * 100 + Hist_CDF_Ref[i] * 100)/2;
			for (int j = 0; j < 256; j++) {
				int compareSource = Hist_CDF_Ref[j] * 100;
				if (compareSource > currentSource) {
					findIndex = j-1;
					LUT[currentSource] = Hist_CDF_Ref[i] * 255;
					break;
				}
			}
		}
		

		//Histogram Matching 과정을 통하여 Matching결과를 Mat에 저장
		for (int h = 0; h < MatchImg.rows; h++) {
			for (int w = 0; w < MatchImg.cols; w++) {
				//TODO : Implement
				unsigned char pixel = ch_in_gray[h][w];
				double cdf = Hist_CDF[pixel];
				//Hist_CDF_Ref[x] = cdf;
				int cdfIndex = cdf * 100;
				MatchImg.at<unsigned char>(h, w) = LUT[cdfIndex];
				Hist_Mat[LUT[cdfIndex]]++;
			}
		}

		DisplayImage(MatchImg, false);
		DisplayHistogram(Hist_Ref);
		DisplayHistogram(Hist_Mat);
	}
}


void CViewerDlg::OnEditFilterClicked()
{
	if (isImageOpened&&nFormat == FORMAT_GRAY) {
		unsigned char** Pad;
		unsigned char** Out = NULL;

		CFilterDlg FilterDlg;
		int nFilterSize;
		if (FilterDlg.DoModal() == IDOK) {
			int nFilterType = FilterDlg.getFilterType();
			switch (nFilterType) {
			case FILTER_AVERAGE:
				nFilterSize = FilterDlg.getFilterSize();
				if (nFilterSize >= 3) {
					if (nFilterSize % 2 == 0) {
						nFilterSize++;
					}
					Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, nFilterSize);
					Out = MemAlloc2D(nHeight_in, nWidth_in, 0);
					AverageFilter(Pad, Out, nHeight_in, nWidth_in, nFilterSize);
					DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);
					MemFree2D(Pad, nHeight_in + (int)(nFilterSize / 2) * 2);

				}
				else
					MessageBox("Filter Size가 잘못되엇습니다. Filter Size는 3이상입니다.");
				break;
			case FILTER_SMOOTH:
				Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, 3);
				Out = MemAlloc2D(nHeight_in, nWidth_in, 0);
				SmoothFilter(Pad, Out, nHeight_in, nWidth_in);
				DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);
				MemFree2D(Pad, nHeight_in + 2);
				break;
			case FILTER_SHARPEN:
				Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, 3);
				Out = MemAlloc2D(nHeight_in, nWidth_in, 0);
				SharpenFilter(Pad, Out, nHeight_in, nWidth_in);
				DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);
				MemFree2D(Pad, nHeight_in + 2);
				break;
			case FILTER_GAUSSIAN:
				Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, 3);
				Out = MemAlloc2D(nHeight_in, nWidth_in, 0);
				GaussianFilter(Pad, Out, nHeight_in, nWidth_in);
				DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);
				MemFree2D(Pad, nHeight_in + 2);
				break;
			}
			if(Out!=NULL)
				MemFree2D(Out, nHeight_in);
		}
		else {
			MessageBox("불러온 영상이 없거나 영상 포맷이 회색조 영상이 아닙니다.");
		}
	}
}


unsigned char ** Padding(unsigned char ** In, int nHeight, int nWidth, int nFilterSize)
{
	int nPadSize = (int)(nFilterSize / 2);
	unsigned char** Pad = MemAlloc2D(nHeight + 2 * nPadSize, nWidth + 2 * nPadSize, 0);
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			Pad[h + nPadSize][w + nPadSize] = In[h][w];
		}
	}
	for (int h = 0; h < nPadSize; h++) {
		for (int w = 0; w < nWidth; w++) {
			Pad[h][w + nPadSize] = In[0][w];
			Pad[h + (nHeight - 1)][w + nPadSize] = In[nHeight - 1][w];
		}
	}
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nPadSize; w++) {
			Pad[h + nPadSize][w] = In[h][0];
			Pad[h + nPadSize][w + (nWidth - 1)] = In[h][nWidth - 1];
		}
	}
	for (int h = 0; h < nPadSize; h++) {
		for (int w = 0; w < nPadSize; w++) {
			Pad[h][w] = In[0][0];
			Pad[h + (nHeight - 1)][w] = In[nHeight - 1][0];
			Pad[h][w + (nWidth - 1)] = In[0][nWidth - 1];
			Pad[h + (nHeight - 1)][w + (nWidth - 1)] = In[nHeight - 1][nWidth - 1];
		}
	}
	return Pad;
}

void applyFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth, int nFilterSize, double** filterMask) {
	int nPadSize = (int)(nFilterSize / 2);
	for (int h = nPadSize; h <= nHeight - nPadSize; h++) {
		for (int w = nPadSize; w <= nWidth - nPadSize; w++) {

			//filter
			int sum = 0;
			for (int filterH = 0; filterH < nFilterSize; filterH++) {
				for (int filterW = 0; filterW < nFilterSize; filterW++) {
					sum += In_Pad[h+filterH-nPadSize][w+filterW-nPadSize]*filterMask[filterH][filterW];
				}
			}
			if (sum > 255)
				sum = 255;
			else if (sum < 0)
				sum = 0;
			Out[h - nPadSize][w - nPadSize] = sum;
		}
	}
}





Mat GrayToMat(unsigned char ** Img, int nHeight, int nWidth)
{
	Mat rtn = Mat(nHeight, nWidth, CV_8UC1);
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			rtn.at<unsigned char>(h, w) = Img[h][w];
		}
	}
	return rtn;
}


void CViewerDlg::OnNoisereductionAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CAddNoiseDlg AddNoiseDlg;
	BYTE** NoiseImg = MemAlloc2D(nHeight_in, nWidth_in, 0);
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		if (AddNoiseDlg.DoModal() == IDOK) {
			CString outFileName = InpFileName;
			float Value_1 = AddNoiseDlg.GetVal_1();
			float Value_2 = AddNoiseDlg.GetVal_2();
			int nNoiseType = AddNoiseDlg.GetNoiseType();

			if (nNoiseType == NOISE_GN) {
				if (Value_2 < 1) {
					MessageBox("표준 편차 값은 1 이상이여야 합니다.");
					MemFree2D(NoiseImg, nHeight_in);
					return;
				}
				InputGaussianNoise(ch_in_gray, NoiseImg, nHeight_in, nWidth_in, Value_1, Value_2);
				outFileName += "_GN.raw";

			}
			else {
				if (Value_1 <= 0 && Value_2 <= 0) {
					MessageBox("두 개의 확률 값 중 적어도 하나는 0보다 커야합니다.");
					MemFree2D(NoiseImg, nHeight_in);
					return;
				}
				InputSaltPepperNoise(ch_in_gray, NoiseImg, nHeight_in, nWidth_in, Value_1, Value_2);
				outFileName += "SPN.raw";
			}
			DisplayImage(GrayToMat(NoiseImg, nHeight_in, nWidth_in), false);
			FILE* fp;
			fopen_s(&fp, outFileName, "wb");
			for (int h = 0; h < nHeight_in; h++) {
				fwrite(NoiseImg[h], sizeof(unsigned char), nWidth_in, fp);
			}
			MessageBox("파일저장 됨 : " + outFileName);
			fclose(fp);
			MemFree2D(NoiseImg, nHeight_in);
		}
	}
}

void CViewerDlg::OnNoisefilteringMeafilterClicked() {
	MeanFilterDlg MFDlg;
	if (isImageOpened == true && nFormat == FORMAT_GRAY) {
		if (MFDlg.DoModal() == IDOK) {
			int nFilterSize = MFDlg.GetFilterSize();
			int nFilterType = MFDlg.GetMeanFilterType();

			if (nFilterSize < 3) {
				MessageBox("필터 크기가 잘못되었습니다.");
				return;
			}
			if (nFilterSize % 2 == 0) {
				nFilterSize++;
			}
			CString OutFileName = InpFileName;
			unsigned char** Out = MemAlloc2D(nHeight_in, nWidth_in, 0);
			switch (nFilterType) {
			case NF_ARITHMETIC:
				ArithmeticMeanFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize);
				OutFileName += "_ANF.raw";
				break;
			case NF_GEOMETRIC:
				GeometricMeanFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize);
				OutFileName += "_GMFF.raw";
				break;
			case NF_HARMONIC:
				HarmonicMeanFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize);
				OutFileName += "_HMF.raw";
				break;
			case NF_CONTRAHARMONIC:
				int Q = MFDlg.GetQ();
				ContraharmonicMeanFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize,Q);
				OutFileName += "_CHMF.raw";
				break;

			}
			DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);
			FILE* fp;
			fopen_s(&fp, OutFileName, "wb");
			for (int h = 0; h < nHeight_in; h++) {
				fwrite(Out[h], sizeof(unsigned char), nWidth_in, fp);
			}
			fclose(fp);
		}
	}
}

void CViewerDlg::OnNoisefilteringOrderStatisticClicked() {
	COrderStatisticsDlg OSFDlg;
	if (isImageOpened == true && nFormat == FORMAT_GRAY) {
		if (OSFDlg.DoModal() == IDOK) {
			int nFilterSize = OSFDlg.GetfilterSize1();
			int nFilterType = OSFDlg.GetOSFType();

			if (nFilterSize < 3) {
				MessageBox("필터 크기가 잘못되었습니다.");
				return;
			}
			if (nFilterSize % 2 == 0) {
				nFilterSize++;
			}
			CString OutFileName = InpFileName;
			unsigned char** Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

			switch (nFilterType) {
			case NF_MEDIAN:
				MedianFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize);
				OutFileName += "_MEDF.raw";
				break;
			case NF_ADAPTIVEMEDIAN:
				int MaxFilterSize = OSFDlg.GetFilterSize2();
				AdaptiveMedianFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize, MaxFilterSize);
				OutFileName += "_AMEDF.raw";
				break;
			}
			DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);
			FILE* fp;
			fopen_s(&fp, OutFileName, "wb");
			for (int h = 0; h < nHeight_in; h++) {
				fwrite(Out[h], sizeof(unsigned char), nWidth_in, fp);
			}
			fclose(fp);
		}
	}
}

void ArithmeticMeanFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize) {
	int nTemp, nPadSize = (int)(nFilterSize / 2);
	unsigned char** Img_Pad = Padding(Img_in, nHeight, nWidth, nFilterSize);

	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			nTemp = 0;
			for (int m = 0; m < nFilterSize; m++) {
				for (int n = 0; n<nFilterSize; n++) {
					nTemp += Img_Pad[h + m][w + n];
				}
			}
			Out[h][w] = static_cast<unsigned char>(nTemp / (nFilterSize*nFilterSize));
		}
	}
	MemFree2D(Img_Pad, nHeight + 2 * nPadSize);
}
void AverageFilter(unsigned char ** In_Pad, unsigned char ** Out, int nHeight, int nWidth, int nFilterSize)
{
	int nPadSize = (int)(nFilterSize / 2);
	int filterTotalSize = nFilterSize * nFilterSize;
	double** filterMask = new double*[nFilterSize];
	for (int i = 0; i < nFilterSize; i++) {
		filterMask[i] = new double[nFilterSize];
		for (int j = 0; j < nFilterSize; j++) {
			filterMask[i][j] = (double)1 / filterTotalSize;
		}
	}
	applyFilter(In_Pad, Out, nHeight, nWidth, nFilterSize, filterMask);
}
void SmoothFilter(unsigned char ** In_Pad, unsigned char ** Out, int nHeight, int nWidth)
{
	int nFilterSize = 3;
	int nPadSize = (int)(nFilterSize / 2);
	int filterTotalSize = nFilterSize * nFilterSize;
	double** filterMask = new double*[nFilterSize];

	for (int i = 0; i < nFilterSize; i++) {
		filterMask[i] = new double[nFilterSize];
	}

	// 1  2  1
	// 2  4  2  ÷ 16
	// 1  2  1
	filterMask[0][0] = 1.0 / 16;
	filterMask[0][1] = 2.0 / 16;
	filterMask[0][2] = 1.0/ 16;
	filterMask[1][0] = 2.0 / 16;
	filterMask[1][1] = 4.0 / 16;
	filterMask[1][2] = 2.0 / 16;
	filterMask[2][0] = 1.0 / 16;
	filterMask[2][1] = 2.0 / 16;
	filterMask[2][2] = 1.0 / 16;
	applyFilter(In_Pad, Out, nHeight, nWidth, 3, filterMask);
}

void SharpenFilter(unsigned char ** In_Pad, unsigned char ** Out, int nHeight, int nWidth)
{
	int nFilterSize = 3;
	int nPadSize = (int)(nFilterSize / 2);
	int filterTotalSize = nFilterSize * nFilterSize;
	double** filterMask = new double*[nFilterSize];
	// 0 -1  0
	//-1  5 -1
	// 0 -1  0
	for (int i = 0; i < nFilterSize; i++) {
		filterMask[i] = new double[nFilterSize];
	}
	filterMask[0][0] = 0.0;
	filterMask[0][1] = -1.0;
	filterMask[0][2] = 0.0;
	filterMask[1][0] = -1.0;
	filterMask[1][1] = 5.0;
	filterMask[1][2] = -1.0;
	filterMask[2][0] = 0.0;
	filterMask[2][1] = -1.0;
	filterMask[2][2] = 0.0;
	applyFilter(In_Pad, Out, nHeight, nWidth, 3, filterMask);
}

double linearGaussian(double x,double std) {
	return exp(-pow(x,2) / 2*pow(std,2)) / (std*sqrt(2 * M_PI));
}

double getGaussianValue(int h, int w, int sigma) {
	return linearGaussian(h, sigma)*linearGaussian(w, sigma);
}

void GaussianFilter(unsigned char ** In_Pad, unsigned char ** Out, int nHeight, int nWidth)
{
	int nFilterSize = 3;
	int nPadSize = (int)(nFilterSize / 2);
	int filterTotalSize = nFilterSize * nFilterSize;
	int sigma = 1;
	double** filterMask = new double*[nFilterSize];
	double r;


	for (int i = -1; i <= 1; i++) {
		filterMask[i+1] = new double[nFilterSize];
		for (int j = -1; j <= 1; j++) {
			r = sqrt(i*i + j * j);
			filterMask[i + 1][j + 1] = (exp(-(r*r) / sigma)) / (M_PI*sigma);
			cout << filterMask[i + 1][j + 1] << endl;
		}
	}
	applyFilter(In_Pad, Out, nHeight, nWidth, 3, filterMask);
}
void GeometricMeanFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize) {

}
void HarmonicMeanFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize) {

}
void ContraharmonicMeanFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize, int Q) {

}

void MedianFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize) {

}
void AdaptiveMedianFilter(unsigned char **ImgImg_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize_Min, int nFilterSize_Max) {

}

void CViewerDlg::OnGetpsnr()
{
	CPSNRDlg PSNFDlg;
	PSNFDlg.DoModal();
}
