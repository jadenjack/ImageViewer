
// ViewerDlg.h: 헤더 파일
//

#pragma once
#include <opencv2\opencv.hpp>
#include "math.h"
#include "RawInfoDlg.h"
#include "ImgScalingDlg.h"
#include "RotationDlg.h"
#include "FilterDlg.h"
#include "AddNoiseDlg.h"
#include "MeanFilterDlg.h"
#include "COrderStatisticsDlg.h"
#include "PSNRDlg.h"

#define M_PI       3.14159265358979323846   // pi
enum NoiseFilterType {
	NF_ARITHMETIC,
	NF_GEOMETRIC,
	NF_HARMONIC,
	NF_CONTRAHARMONIC,
	NF_MEDIAN,
	NF_ADAPTIVEMEDIAN
};
using namespace cv;
using namespace std;
unsigned char** MemAlloc2D(int nHeight, int nWidth, unsigned char nInitVal);
void MemFree2D(unsigned char** Mem, int nHeight);
void DisplayHistogram(int* Hist);
unsigned char ** Padding(unsigned char ** In, int nHeight, int nWidth, int nFilterSize);
void AverageFilter(unsigned char ** In_Pad, unsigned char ** Out, int nHeight, int nWidth, int nFilterSize);
void SmoothFilter(unsigned char ** In_Pad, unsigned char ** Out, int nHeight, int nWidth);
void SharpenFilter(unsigned char ** In_Pad, unsigned char ** Out, int nHeight, int nWidth);
void GaussianFilter(unsigned char ** In_Pad, unsigned char ** Out, int nHeight, int nWidth);

double linearGaussian(double x, double std);
double getGaussianValue(int h, int w, int sigma);

void applyFilter(unsigned char** In_Pad, unsigned char** Out, int nHeight, int nWidth, int nFilterSize, double** filterMask);

void ArithmeticMeanFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize);
void GeometricMeanFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize);
void HarmonicMeanFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize);
void ContraharmonicMeanFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize, int Q);



void MedianFilter(unsigned char **Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize);
void AdaptiveMedianFilter(unsigned char **ImgImg_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize_Min, int nFilterSize_Max);

Mat GrayToMat(unsigned char** Img, int nHeight, int nWidth);

// CViewerDlg 대화 상자
class CViewerDlg : public CDialogEx
{
// 생성입니다.
private:
	unsigned char **ch_in_1, **ch_in_2, **ch_in_3;
	unsigned char **ch_in_gray;

	int* Hist;

	int nHeight_in, nWidth_in;
	int nFormat;
	bool isImageOpened;

	CString InpFileName;
public:
	CViewerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	enum ImageFormat {
		FORMAT_RGB,
		FORMAT_YUV444,
		FORMAT_YUV420,
		FORMAT_GRAY
	};
	enum InterpolationType {
		BILINEAR,
		BICUBIC
	};

	enum FilterType {
		FILTER_AVERAGE,
		FILTER_SMOOTH,
		FILTER_SHARPEN,
		FILTER_GAUSSIAN
	};

	enum NoiseType {
		NOISE_GN,
		NOISE_SP
	};
	CStatic m_PicOri;
	CStatic m_PicProc;
	CRawInfoDlg RawInfoDlg;
	CImgScalingDlg ImgScalingDlg;
	CRotationDlg RotationDlg;

	//Display용 멤버 변수 및 메서드
	Mat Ori_Img, Proc_Img;
	CRect rect;
	CDC* m_pDC;

	void CViewerDlg::DisplayImage(Mat DispMat, bool blnOut);
	void CViewerDlg::DisplayBitmap(CDC* pDC, CRect rect, IplImage* DisplplImage);
	void CViewerDlg::ResizeImage(IplImage* src, IplImage** dst, CRect* rect);
	bool isInsideBoundary(int nHeight, int nWidth, double h, double w);
	unsigned char BilinearInterpolation(unsigned char** In, int nHeight_Ori, int nWidth_Ori, double h_Cvt, double w_Cvt);
	unsigned char CViewerDlg::getLinearInterpolation(double h_Cvt, double w_Cvt, Point p1, Point p2,unsigned char v1, unsigned char v2);

	unsigned char BicubicInterpolation(unsigned char** In, int nHeight_Ori, int nWidth_Ori, double h_Cvt, double w_Cvt);
	unsigned char CubicInterpolation(Point p[], double target);
	double cubicFunction(double a, double b, double c, double d, double x);
	Point calPosition(int x, int y, double h_Cvt, double w_Cvt);
	int CViewerDlg::roundPosition(int index, double originPosition, int boundary);
	int CViewerDlg::roundPosition(int index, double originPosition);
	double CViewerDlg::getDistance(Point p1, Point p2);

	Point rotatePoint(Point p, int angle, int nWidth_2, int nHeight_2);

	void InputGaussianNoise(unsigned char** In, unsigned char** Out, int nHeight, int nWidth, float fMean, float fStdev);
	void InputSaltPepperNoise(unsigned char** In, unsigned char**Out, int nHeight, int nWidth, float fSProb, float fPProb);

	void GetGaussianPDF(float* EmptyPDF, int nLength, float fMean, float fStDev);
	float GetNoise(float* PDF, int nLength);

	void OnNoisefilteringOrderStatisticClicked();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpenBtnClick();
	afx_msg void OnCloseMenuClick();
	afx_msg void OnConvertgrayBtnClick();
	afx_msg void OnEditScalingClick();
	afx_msg void OnEditRotationClick();
	afx_msg void OnHistogramGetClick();
	afx_msg void OnHistogramEqualizationClicked();
	afx_msg void OnHistogramMatchingClicked();
	afx_msg void OnEditFilterClicked();
	afx_msg void OnNoisereductionAdd();
	afx_msg void OnNoisefilteringMeafilterClicked();
	afx_msg void OnGetpsnr();
};
