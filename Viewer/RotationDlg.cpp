// RotationDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Viewer.h"
#include "RotationDlg.h"
#include "afxdialogex.h"


// CRotationDlg 대화 상자

IMPLEMENT_DYNAMIC(CRotationDlg, CDialogEx)

CRotationDlg::CRotationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROTATIONDIALOG, pParent)
	, m_radio_Interp(0)
{

}

CRotationDlg::~CRotationDlg()
{
}

void CRotationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_BILINEAR_R, m_radio_Interp);
	DDX_Control(pDX, IDC_EDIT_ROTATEANGLE, m_EditRotateAngle);
}


BEGIN_MESSAGE_MAP(CRotationDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRotationDlg::OnClickedOkbutton3)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_BILINEAR_R, IDC_RADIO_BICUBIC_R, OnRadioClicked)
END_MESSAGE_MAP()


// CRotationDlg 메시지 처리기


void CRotationDlg::OnClickedOkbutton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrAngle;
	m_EditRotateAngle.GetWindowText(cstrAngle);
	nAngle = atoi(cstrAngle);
	CDialogEx::OnOK();
}

void CRotationDlg::OnRadioClicked(UINT msg)
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

int CRotationDlg::GetAngle()
{
	return nAngle;
}

int CRotationDlg::GetInterpolationType()
{
	return nInterpolationType;
}
