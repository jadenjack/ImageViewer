// MeanFilterDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Viewer.h"
#include "MeanFilterDlg.h"
#include "afxdialogex.h"


// MeanFilterDlg 대화 상자

IMPLEMENT_DYNAMIC(MeanFilterDlg, CDialogEx)

MeanFilterDlg::MeanFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MeanFilterDIALOG, pParent)
{

}

MeanFilterDlg::~MeanFilterDlg()
{
}

void MeanFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_ARITHMETIC, m_radio_mf);
	DDX_Control(pDX, IDC_EDIT_MF_FILTERSIZE, Edit_FilterSize);
	DDX_Control(pDX, IDC_EDIT_Q, Edit_Q);
}


int MeanFilterDlg::GetFilterSize() {
	return this->nFilterSize;
}
int MeanFilterDlg::GetMeanFilterType() {
	return this->nMeanFilterType;
}
int MeanFilterDlg::GetQ() {
	return this->Q;
}

BEGIN_MESSAGE_MAP(MeanFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK_MF,&MeanFilterDlg::OnOkMfButtonClicked)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RADIO_ARITHMETIC,IDC_RADIO_CONTRA_HARMONIC,OnRadioClicked)
END_MESSAGE_MAP()

// MeanFilterDlg 메시지 처리기

void MeanFilterDlg::OnOkMfButtonClicked() {
	CString strTemp1, strTemp2;
	Edit_FilterSize.GetWindowTextA(strTemp1);
	Edit_Q.GetWindowTextA(strTemp2);
	nFilterSize = atoi(strTemp1);
	Q = atoi(strTemp2);;
	CDialog:OnOK();
}

void MeanFilterDlg::OnRadioClicked(UINT msg) {
	UpdateData(TRUE);
	switch (m_radio_mf) {
	case 0:
		nMeanFilterType = 0;
		break;
	case 1:
		nMeanFilterType = 1;
		break;
	case 2:
		nMeanFilterType = 2;
		break;
	case 3:
		nMeanFilterType = 3;

	}
}