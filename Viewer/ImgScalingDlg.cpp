// ImgScalingDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Viewer.h"
#include "ImgScalingDlg.h"
#include "afxdialogex.h"


// CImgScalingDlg 대화 상자

IMPLEMENT_DYNAMIC(CImgScalingDlg, CDialogEx)

CImgScalingDlg::CImgScalingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCALEDIALOG, pParent)
	, m_radio_Interp(0)
{

}

CImgScalingDlg::~CImgScalingDlg()
{
}

void CImgScalingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SCALERATE, m_EditScaleRate);
	DDX_Radio(pDX, IDC_RADIO_BILINEAR_S, m_radio_Interp);
}


BEGIN_MESSAGE_MAP(CImgScalingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CImgScalingDlg::OnBnClickedOkbutton2)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_BILINEAR_S, IDC_RADIO_BICUBIC_S, OnRadioClicked)
	ON_BN_CLICKED(IDC_OKBUTTON2, &CImgScalingDlg::OnBnClickedOkbutton2)
END_MESSAGE_MAP()


// CImgScalingDlg 메시지 처리기


void CImgScalingDlg::OnRadioClicked(UINT msg)
{
	UpdateData(TRUE);
	switch (m_radio_Interp) {
	case 0:
		nInterpolationType = 0;
		break;
	case 1:
		nInterpolationType = 1;
		break;
	}
}

double CImgScalingDlg::GetScaleRate()
{
	return dScaleRate;
}

int CImgScalingDlg::GetInterpType()
{
	return nInterpolationType;
}


void CImgScalingDlg::OnBnClickedOkbutton2()
{
	CString cstrTemp;
	m_EditScaleRate.GetWindowText(cstrTemp);
	dScaleRate = atof(cstrTemp);
	CDialogEx::OnOK();
}
