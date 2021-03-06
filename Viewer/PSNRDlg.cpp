// PSNRDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Viewer.h"
#include "PSNRDlg.h"
#include "afxdialogex.h"


// CPSNRDlg 대화 상자

IMPLEMENT_DYNAMIC(CPSNRDlg, CDialogEx)

BEGIN_MESSAGE_MAP(CPSNRDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPSNRDlg::OnOriopenButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CPSNRDlg::OnNoiseopenButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &CPSNRDlg::OnGetpsnrButtonClicked)
END_MESSAGE_MAP()

double CPSNRDlg::GetMSE(unsigned char ** Ori, unsigned char ** Dst, int nHeight, int nWidth) {
	double size = nHeight * nWidth;
	double sumOfSub = 0.0;
	double sub;
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			sub = Ori[h][w] - Dst[h][w];
			sumOfSub += sub;
		}
	}
	return sumOfSub/size;
}

double CPSNRDlg::GetPSNR(unsigned char ** Ori, unsigned char ** Dst, int nHeight, int nWidth)
{
	double mse = GetMSE(Ori, Dst, nHeight, nWidth);
	return 10 * log10(255 * 255 / mse);
}

CPSNRDlg::CPSNRDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PSNRDIALOG, pParent)
{

}

CPSNRDlg::~CPSNRDlg()
{
}

void CPSNRDlg::OnOriopenButtonClicked()
{
	CFileDialog dlg(TRUE);
	CRawInfoDlg RawDlg;

	if (Ori != NULL) {
		MemFree2D(Ori, nHeight_Ori);
	}
	if (dlg.DoModal() == IDOK) {
		if (dlg.GetFileExt() != "raw"&&dlg.GetFileExt() != "RAW") {
			MessageBox("파일 확장자가 raw파일이 아닙니다.");
			return;
		}
		FILE* fp;
		fopen_s(&fp, dlg.GetFileName(), "rb");
		if (RawDlg.DoModal() == IDOK) {
			nHeight_Ori = RawDlg.GetRawHeight();
			nWidth_Ori = RawDlg.GetRawWidth();
			if (nHeight_Ori == 0 || nWidth_Ori == 0 || RawDlg.GetRawFormat() != 3) {
				MessageBox("입력 값이 잘못되었습니다.");
				return;
			}
			Edit_File_Ori.SetWindowTextA(dlg.GetFileTitle());
			Ori = MemAlloc2D(nHeight_Ori, nWidth_Ori, 0);
			for (int h = 0; h < nHeight_Ori; h++) {
				fread(Ori[h], sizeof(unsigned char), nWidth_Ori, fp);
			}
		}
		fclose(fp);
	}
}

void CPSNRDlg::OnNoiseopenButtonClicked()
{
	CFileDialog dlg(TRUE);
	CRawInfoDlg RawDlg;
	if (Dst != NULL) {
		MemFree2D(Dst, nHeight_Dst);
	}
	if (dlg.DoModal() == IDOK) {
		if (dlg.GetFileExt() != "raw" && dlg.GetFileExt() != "RAW") {
			MessageBox("파일 확장자가 raw파일이 아닙니다.");
			return;
		}
		FILE *fp;
		fopen_s(&fp, dlg.GetFileName(), "rb");
		if (RawDlg.DoModal() == IDOK) {
			nHeight_Dst = RawDlg.GetRawHeight();
			nWidth_Dst = RawDlg.GetRawWidth();
			if (nHeight_Dst == 0 || nWidth_Dst == 0 || RawDlg.GetRawFormat() != 3) {
				MessageBox("입력 값이 잘못되었습니다.");
				return;
			}
			Edit_File_Dst.SetWindowTextA(dlg.GetFileTitle());
			Dst = MemAlloc2D(nHeight_Ori, nWidth_Ori, 0);
			for (int h = 0; h < nHeight_Dst; h++) {
				fread(Ori[h], sizeof(unsigned char), nWidth_Dst, fp);
			}
		}
		fclose(fp);
	}
}

void CPSNRDlg::OnGetpsnrButtonClicked()
{
	if (Ori == NULL || Dst == NULL) {
		MessageBox("원본 영상과 비교 영상을 불러오지 않았습니다.");
		return;
	}
	if (nHeight_Ori != nHeight_Dst || nWidth_Ori != nWidth_Dst) {
		MessageBox("원본 영상과 비교 영상의 크기가 다릅니다.");
		return;
	}
	CString strTemp;
	double dPSNR = GetPSNR(Ori, Dst, nHeight_Ori, nWidth_Ori);
	strTemp.Format(_T("%f"), dPSNR);
	Edit_PSNR.SetWindowTextA(strTemp);
}

void CPSNRDlg::OnBnClickedButtonClose()
{
	if (Ori != NULL) {
		MemFree2D(Ori, nHeight_Ori);
	}
	if (Dst != NULL) {
		MemFree2D(Dst, nWidth_Dst);
	}
	CDialog::OnCancel();

}

void CPSNRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Edit_File_Ori);
	DDX_Control(pDX, IDC_EDIT2, Edit_File_Dst);
	DDX_Control(pDX, IDC_EDIT3, Edit_PSNR);
}





// CPSNRDlg 메시지 처리기
