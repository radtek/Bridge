// Set.cpp : implementation file
//

#include "stdafx.h"
#include "���ʽ����֧�ܽ�ģ����.h"
#include "Set.h"
#include "math.h"
#include "MyNode.h"
#include "xSkinButton.h"
#include "excel.h"
//#include "msword.h"
#include "WordOffice.h"
#include "UIThread.h"
#include "Section.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <string>

using namespace std;


struct threadInfo
{
	int Process;
	CProgressCtrl* pctrlProgress;
	//CWnd* pCWnd;
};
//UINT ThreadFunc(LPVOID lpParam);
threadInfo Info;
int Process=0;
UINT ThreadFunc(LPVOID lpParam)
{
	threadInfo* pInfo=(threadInfo*)lpParam;
	pInfo->pctrlProgress->SetPos(Process);
	return 0;
};

CxSkinButton m_button_Output;
CxSkinButton m_button_Clear;

float PaiJuDealSave[50];
int PaiJuCountSave[50];
float PaiJuDataSave[50];


float ZhuJuDealSave[50];
int ZhuJuCountSave[50];
float ZhuJuDataSave[50];

float BuJuDealSave[50];
int BuJuCountSave[50];
float BuJuDataSave[50];


int Sort=0;
int PaiJuCount=0;
int ZhuJuGeShu_X=0;
int BuJuGeShu_Z=0;
int PaiJuGeShu_Y=0;
int NodeZongShu=0;
float Length_X=0;
float Length_Y=0;
float Length_Z=0;

//***************************���ز�����ʼֵ�������*****************//
float ini_GangJinHunNingTu=0.0;
float ini_MoBanFangLeng=0.0;
float ini_FuJiaGouJian=0.0;
float ini_RenChaiJi=0.0;
float ini_JiaoZhuZhenDao=0.0;
float ini_FengHeZai=0.0;




//************************�޸�VB�����趨�ı���************************//
int a,c;
int b=0;
int dy=1;               //��Ԫ���
int dc=0      ;            //����ڵ���
int qd=  0      ;           //��Ԫǰ�ڵ�
int zd=  0      ;           //��Ԫ��ڵ�

//************************�޸�VB����б��Ԫ�趨�ı���****************************//

int J1=1;
int j2=1;
int i1=1;
int i2=1;
int is1=0;
int s1=1;
int s2=1;
int k1=0;
int k2=0;
int k3=0;
int k4=0;

//************************ѭ�������趨*************************//
int xx=0;     //רҵѭ������
int yy=0;     //רҵѭ������
int zz=0;     //רҵѭ������
int rr=0; 
int tt=0;
int kk=0;
int yj1=0;
int jy1=0;
int hh=0;
int ee=0;
int ff=0;
int cc=0;
int xi1=0;

//************************���ز���************************//
int m1=0;
int m2=0;
int m3=0;
int u=0;
float qy=0;
float qq6, qq5, qq4, qq3, qq2, qj1, qj2, qy1, qy2, qy3;

Node *NodeZong;
////////////////////����Ϊoffice����궨��/////////////////////////////////////
#define xlAscending (long) 1

#define xlDescending (long) 2

#define vOpt COleVariant((long) DISP_E_PARAMNOTFOUND, VT_ERROR)

#define xlHeader (long) 1                            // ѡȡ�������б���

#define xlNoHeader (long) 2                          // ѡȡ�������ޱ���    һ��Ҫ��ȷȷ���Ƿ��б��⣬����������ܲ��ɹ�

#define xlMatchCase COleVariant((long) 1)

#define xlIgnoreCase COleVariant((long) 0)

#define xlTopToBottom (long) 1                       // ��ֱ�����������

#define xlLeftToRight (long) 2                       // ˮƽ�����������

#define xlPinYin (long) 1 // this is the default     // ���ַ�������ƴ����������

#define xlStroke (long) 2                            // ��ÿ���ַ��еıʻ�����������
////////////////////����Ϊoffice����궨��/////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSet dialog


CSet::CSet(CWnd* pParent /*=NULL*/)
: CDialog(CSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSet)
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DiErCiJiaoZhu = _T("");
	m_DiErCiYuYa = _T("");
	m_SaoDiGanGaoDu = _T("");
	m_DingCengXuanBi = _T("");
	m_DiSanCiYuYa = _T("");
	m_DiYiCiJiaoZhu = _T("");
	m_DiYiCiYuYa = _T("");
	m_FengHeZai = _T("");
	m_FuJiaGouJian = _T("");
	m_GangJinHunNingTu = _T("");
	m_JiaoZhuZhenDao = _T("");
	m_MoBanFangLeng = _T("");
	m_PaiJu_Y = _T("");
	m_RenChaiJi = _T("");
	m_BujuZ = _T("");
	m_ZhuJuX = _T("");
	//}}AFX_DATA_INIT
	//EnableVisualManagerStyle(TRUE, TRUE);
}


void CSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSet)
	DDX_Control(pDX, IDC_EDIT_XLSPATH, m_Path);
	DDX_Control(pDX, IDXLCD_DanWei_RenChaiJi, m_Control_DanWei_RenChaiJi);
	DDX_Control(pDX, IDXLCD_DanWei_MoBanFangLeng, m_Control_DanWei_MoBanFangLeng);
	DDX_Control(pDX, IDXLCD_DanWei_JiaoZhuZhenDao, m_Control_DanWei_JiaoZhuZhenDao);
	DDX_Control(pDX, IDXLCD_DanWei_GangJinHunNingTu, m_Control_DanWei_GangJinHunNingTu);
	DDX_Control(pDX, IDXLCD_DanWei_FuJiaGouJian, m_Control_DanWei_FuJiaGouJian);
	DDX_Control(pDX, IDXLCD_DanWei_FengHeZai, m_Control_DanWei_FengHeZai);
	DDX_Control(pDX, IDC_ZhuJu_X, m_Control_ZhuJu_X);
	DDX_Control(pDX, IDC_BuJu_Z, m_Control_BuJu_Z);
	DDX_Text(pDX, IDE_DiErCiJiaoZhu, m_DiErCiJiaoZhu);
	DDX_Text(pDX, IDE_DiErCiYuYa, m_DiErCiYuYa);
	DDX_Text(pDX, IDE_SaoDiGanGaoDu, m_SaoDiGanGaoDu);
	DDX_Text(pDX, IDE_DingCengXuanBi, m_DingCengXuanBi);
	DDX_Text(pDX, IDE_DiSanCiYuYa, m_DiSanCiYuYa);
	DDX_Text(pDX, IDE_DiYiCiJiaoZhu, m_DiYiCiJiaoZhu);
	DDX_Text(pDX, IDE_DiYiCiYuYa, m_DiYiCiYuYa);
	DDX_Text(pDX, IDE_FengHeZai, m_FengHeZai);
	DDX_Text(pDX, IDE_FuJiaGouJian, m_FuJiaGouJian);
	DDX_Text(pDX, IDE_GangJinHunNingTu, m_GangJinHunNingTu);
	DDX_Text(pDX, IDE_JiaoZhuZhenDao, m_JiaoZhuZhenDao);
	DDX_Text(pDX, IDE_MoBanFangLeng, m_MoBanFangLeng);
	DDX_Text(pDX, IDE_PaiJu_Y, m_PaiJu_Y);
	DDX_Text(pDX, IDE_RenChaiJi, m_RenChaiJi);
	DDX_Text(pDX, IDE_BuJuZ, m_BujuZ);
	DDX_Text(pDX, IDE_ZhuJuX, m_ZhuJuX);
	//DDX_Control(pDX,IDB_Output,m_button_Output);//�ﺣ��
	//DDX_Control(pDX,IDB_Clear,m_button_Clear);//�ﺣ��
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSet, CDialog)
//{{AFX_MSG_MAP(CSet)
ON_CBN_SELCHANGE(IDC_BuJu_Z, OnSelchangeBuJuZ)
ON_CBN_SELCHANGE(IDC_ZhuJu_X, OnSelchangeZhuJuX)
ON_CBN_SELCHANGE(IDXLCD_DanWei_FengHeZai, OnSelchangeDanWeiFengHeZai)
ON_CBN_SELCHANGE(IDXLCD_DanWei_FuJiaGouJian, OnSelchangeDanWeiFuJiaGouJian)
ON_CBN_SELCHANGE(IDXLCD_DanWei_GangJinHunNingTu, OnSelchangeDanWeiGangJinHunNingTu)
ON_CBN_SELCHANGE(IDXLCD_DanWei_JiaoZhuZhenDao, OnSelchangeDanWeiJiaoZhuZhenDao)
ON_CBN_SELCHANGE(IDXLCD_DanWei_MoBanFangLeng, OnSelchangeDanWeiMoBanFangLeng)
ON_CBN_SELCHANGE(IDXLCD_DanWei_RenChaiJi, OnSelchangeDanWeiRenChaiJi)
ON_EN_CHANGE(IDE_GangJinHunNingTu, OnChangeGangJinHunNingTu)
ON_EN_CHANGE(IDE_JiaoZhuZhenDao, OnChangeJiaoZhuZhenDao)
ON_EN_CHANGE(IDE_MoBanFangLeng, OnChangeMoBanFangLeng)
ON_EN_CHANGE(IDE_FuJiaGouJian, OnChangeFuJiaGouJian)
ON_EN_CHANGE(IDE_RenChaiJi, OnChangeRenChaiJi)
ON_EN_CHANGE(IDE_FengHeZai, OnChangeFengHeZai)
ON_EN_CHANGE(IDE_DiYiCiJiaoZhu, OnChangeDiYiCiJiaoZhu)
ON_EN_CHANGE(IDE_DiErCiYuYa, OnChangeDiErCiYuYa)
ON_EN_CHANGE(IDE_DiYiCiYuYa, OnChangeDiYiCiYuYa)
ON_EN_CHANGE(IDE_DiSanCiYuYa, OnChangeDiSanCiYuYa)
ON_EN_CHANGE(IDE_DiErCiJiaoZhu, OnChangeDiErCiJiaoZhu)
ON_BN_CLICKED(IDB_test, Ontest)
ON_EN_CHANGE(IDE_ZhuJuX, OnChangeZhuJuX)
ON_EN_CHANGE(IDE_BuJuZ, OnChangeBuJuZ)
ON_EN_CHANGE(IDE_SaoDiGanGaoDu, OnChangeSaoDiGanGaoDu)
ON_EN_CHANGE(IDE_DingCengXuanBi, OnChangeDingCengXuanBi)
ON_BN_CLICKED(IDB_Output, OnOutput)
ON_BN_CLICKED(IDB_Clear, OnClear)
ON_BN_CLICKED(IDC_BUTTON_INPUTEXCEL, OnButtonInputexcel)
ON_BN_CLICKED(IDC_BUTTON_OUTPUTWORD, OnButtonOutputword)
ON_BN_CLICKED(IDC_RADIO_G1, OnRadioG1)
ON_BN_CLICKED(IDC_RADIO_G2, OnRadioG2)
ON_BN_CLICKED(IDC_RADIO_G3, OnRadioG3)
ON_BN_CLICKED(IDC_BUTTON_INPUTEXCEL2, OnButtonInputexcel2)
ON_BN_CLICKED(IDC_BUTTON_CACLU, OnButtonCaclu)
ON_EN_CHANGE(IDE_ZhuJu_X1, OnChangeZhuJuX1)
ON_EN_CHANGE(IDE_PaiJu_Y, OnChangePaiJuY)
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
ON_EN_CHANGE(IDE_XiaTuoChengGaoDu, OnChangeXiaTuoChengGaoDu)
ON_BN_CLICKED(IDC_ADD_WAIJING, OnAddWaijing)
ON_BN_CLICKED(IDC_DEL_WAIJING, OnDelWaijing)
ON_BN_CLICKED(IDC_ADD_BIHOU, OnAddBihou)
ON_BN_CLICKED(IDC_DEL_BIHOU, OnDelBihou)
ON_BN_CLICKED(IDC_BTN_TESTZERO, OnBtnTestzero)
ON_EN_CHANGE(IDE_BuJu_Z, OnChangeBuJuZ)
	ON_BN_CLICKED(IDC_BTN_SECTION, OnBtnSection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSet message handlers

void CSet::OnSelchangeBuJuZ() 
{
	// TODO: Add your control notification handler code here
	CString str;
	//int i;
    Sort=m_Control_BuJu_Z.GetCurSel();
	if(Sort==0)                                        //0.6
	{
		BuJu_Z=0.6;
	}
	if(Sort==1)                                        //0.9
	{
		BuJu_Z=0.9;
	}
	if(Sort==2)                                        //1.2
	{
		BuJu_Z=1.2;
	}
}

void CSet::OnSelchangeZhuJuX() 
{
	// TODO: Add your control notification handler code here
	CString str;
	//int i;
    Sort=m_Control_ZhuJu_X.GetCurSel();
	if(Sort==0)                                        //0.6
	{
		ZhuJu_X=0.6;
	}
	if(Sort==1)                                        //0.9
	{
		ZhuJu_X=0.9;
	}
	if(Sort==2)                                        //1.2
	{
		ZhuJu_X=1.2;
	}
}

void CSet::OnSelchangeDanWeiFengHeZai()               //�����
{
	// TODO: Add your control notification handler code here
	CString str;
	//int i;
    Sort=m_Control_DanWei_FengHeZai.GetCurSel();
	if(Sort==0)                                        //kg
	{
		//	AfxMessageBox("1");
		FengHeZai=ini_FengHeZai;
		FengHeZai=9.8*FengHeZai/1000;
	}
	if(Sort==1)                                        //kN/(m*m)
	{
		//	AfxMessageBox("2");
		FengHeZai=ini_FengHeZai;
		FengHeZai=FengHeZai*ZhuJu_X*a*2.4;
	}
}

void CSet::OnSelchangeDanWeiFuJiaGouJian()           //���ӹ���
{
	// TODO: Add your control notification handler code here
	CString str;
	//int i;
    Sort=m_Control_DanWei_FuJiaGouJian.GetCurSel();
	
	if(Sort==0)                                        //kg
	{
		//	AfxMessageBox("1");
		FuJiaGouJian=ini_FuJiaGouJian;
		FuJiaGouJian=(9.8)*FuJiaGouJian/1000;
	}
	if(Sort==1)                                        //kN
	{
		//	AfxMessageBox("2");
		FuJiaGouJian=ini_FuJiaGouJian;
	}
	if(Sort==2)                                        //kN/(m*m)
	{
		//	AfxMessageBox("3");
        FuJiaGouJian=ini_FuJiaGouJian;
		FuJiaGouJian=FuJiaGouJian*a*ZhuJu_X*1.2;
	}
	if(Sort==3)                                        //t
	{
		//	AfxMessageBox("4");
		FuJiaGouJian=ini_FuJiaGouJian;
		FuJiaGouJian=FuJiaGouJian*9.8;
	}
}

void CSet::OnSelchangeDanWeiGangJinHunNingTu()       //�ֽ�
{
	// TODO: Add your control notification handler code here
	CString str;
	//int i;
    Sort=m_Control_DanWei_GangJinHunNingTu.GetCurSel();
	if(Sort==0)                                        //kg
	{
		//AfxMessageBox("1");
		GangJinHunNingTu=ini_GangJinHunNingTu;
        GangJinHunNingTu=9.8*GangJinHunNingTu/1000;
		str.Format("%f",GangJinHunNingTu);
		AfxMessageBox(str);
		
	}
	if(Sort==1)                                        //kN
	{
		//	AfxMessageBox("2");
		GangJinHunNingTu=ini_GangJinHunNingTu;
		GangJinHunNingTu=GangJinHunNingTu;
		str.Format("%f",GangJinHunNingTu);
		AfxMessageBox(str);
		
	}
	if(Sort==2)                                        //m3
	{
		//	AfxMessageBox("3");
		GangJinHunNingTu=ini_GangJinHunNingTu;
		GangJinHunNingTu=25*GangJinHunNingTu;
		str.Format("%f",GangJinHunNingTu);
		AfxMessageBox(str);
	}
	if(Sort==3)                                        //t
	{
		//	AfxMessageBox("4");
		GangJinHunNingTu=ini_GangJinHunNingTu;
		GangJinHunNingTu=9.8*GangJinHunNingTu;		
		str.Format("%f",GangJinHunNingTu);
		AfxMessageBox(str);
	}
}

void CSet::OnSelchangeDanWeiJiaoZhuZhenDao()         //��
{
	// TODO: Add your control notification handler code here
	CString str;
	//int i;
    Sort=m_Control_DanWei_JiaoZhuZhenDao.GetCurSel();
	if(Sort==0)                                        //kg
	{
		//	AfxMessageBox("1");
		JiaoZhuZhenDao=ini_JiaoZhuZhenDao;
		JiaoZhuZhenDao=9.8*JiaoZhuZhenDao/1000;
	}
	if(Sort==1)                                        //kN/(m*m)
	{
		//	AfxMessageBox("2");
		JiaoZhuZhenDao=ini_JiaoZhuZhenDao;
		for(int oo=1;oo<=10;oo++)
		{
			Length_Y+=(PaiJuDataSave[oo]*PaiJuCountSave[oo]);
		}
		JiaoZhuZhenDao=JiaoZhuZhenDao*a*ZhuJu_X*Length_Y;
	}
}

void CSet::OnSelchangeDanWeiMoBanFangLeng()     //ģ�淽�
{
	// TODO: Add your control notification handler code here
	CString str;
	//int i;
    Sort=m_Control_DanWei_MoBanFangLeng.GetCurSel();
	if(Sort==0)                                        //kg
	{
		//	AfxMessageBox("1");
		/*
		MoBanFangLeng=ini_MoBanFangLeng;
		MoBanFangLeng=9.8*MoBanFangLeng/1000;
		*/
		
	}
	if(Sort==1)                                        //kN
	{
		//	AfxMessageBox("2");
		MoBanFangLeng=ini_MoBanFangLeng;
	}
	if(Sort==2)                                        //kN/(m*m)
	{
		//	AfxMessageBox("3");
        for(int oo=1;oo<=10;oo++)
		{
			Length_Y+=(PaiJuDataSave[oo]*PaiJuCountSave[oo]);
		}
		MoBanFangLeng=MoBanFangLeng*a*ZhuJu_X*Length_Y;
		
	}
	if(Sort==3)                                        //t
	{
		//	AfxMessageBox("4");
		MoBanFangLeng=ini_MoBanFangLeng;
		MoBanFangLeng=9.8*MoBanFangLeng;
	}
}

void CSet::OnSelchangeDanWeiRenChaiJi()           //�˲Ļ�
{
	// TODO: Add your control notification handler code here
	CString str;
	//int i;
    Sort=m_Control_DanWei_RenChaiJi.GetCurSel();
	if(Sort==0)                                        //kg
	{
	/*
	//	AfxMessageBox("1");
	RenChaiJi=ini_RenChaiJi;
	RenChaiJi=9.8*RenChaiJi/1000;
	str.Format("%f",RenChaiJi);
	AfxMessageBox(str);
		*/
	}
	if(Sort==1)                                        //kN
	{
		//	AfxMessageBox("2");
		RenChaiJi=ini_RenChaiJi;
		str.Format("%f",RenChaiJi);
		AfxMessageBox(str);
	}
	if(Sort==2)                                        //kN/(m*m)
	{
		
		//	AfxMessageBox("3");
		/*
		Deal_PaiJu_Y();
		RenChaiJi=ini_RenChaiJi;
		for(int oo=1;oo<=10;oo++)
		{
		Length_Y=Length_Y+(PaiJuDataSave[oo]*PaiJuCountSave[oo]);
		}
		RenChaiJi=RenChaiJi*a*ZhuJu_X*Length_Y;
		str.Format("%f",RenChaiJi);
		AfxMessageBox(str);
		*/
	}
	if(Sort==3)                                        //t
	{
		
		//	AfxMessageBox("4");
        /*
        RenChaiJi=ini_RenChaiJi;
		RenChaiJi=9.8*RenChaiJi;
		str.Format("%f",RenChaiJi);
		AfxMessageBox(str);
        */
	}
}

void CSet::OnChangeGangJinHunNingTu() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_GangJinHunNingTu,str);
	GangJinHunNingTu=atof(str);
	ini_GangJinHunNingTu=GangJinHunNingTu;
	
	
}

void CSet::OnChangeJiaoZhuZhenDao() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_JiaoZhuZhenDao,str);
	JiaoZhuZhenDao=atof(str);
	ini_JiaoZhuZhenDao=JiaoZhuZhenDao;
}

void CSet::OnChangeMoBanFangLeng() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_MoBanFangLeng,str);
	MoBanFangLeng=atof(str);	
	ini_MoBanFangLeng=MoBanFangLeng;
}

void CSet::OnChangeFuJiaGouJian() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_FuJiaGouJian,str);
	FuJiaGouJian=atof(str);
	ini_FuJiaGouJian=FuJiaGouJian;
}

void CSet::OnChangeRenChaiJi() 
{
    CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_RenChaiJi,str);
	RenChaiJi=atof(str);
	ini_RenChaiJi=RenChaiJi;
}

void CSet::OnChangeFengHeZai() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_FengHeZai,str);
	FengHeZai=atof(str);
	ini_FengHeZai=FengHeZai;
}

void CSet::OnChangeDiYiCiJiaoZhu() 
{
    CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_DiYiCiJiaoZhu,str);
	DiYiCiJiaoZhu=atof(str);
	UpdateData(TRUE);
	DiErCiJiaoZhu=1-DiYiCiJiaoZhu;
	
	m_DiErCiJiaoZhu.Format("%f",DiErCiJiaoZhu);
	UpdateData(FALSE);
	
	
}



void CSet::OnChangeDiYiCiYuYa() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_DiYiCiYuYa,str);
	DiYiCiYuYa=atof(str);
	
}

void CSet::OnChangeDiErCiYuYa() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_DiErCiYuYa,str);
	DiErCiYuYa=atof(str);
}

void CSet::OnChangeDiSanCiYuYa() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_DiSanCiYuYa,str);
	DiSanCiYuYa=atof(str);
}

void CSet::OnChangeDiErCiJiaoZhu() 
{
/*
CString str; 
UpdateData(TRUE);
GetDlgItemText(IDE_DiErCiJiaoZhu,str);
DiErCiJiaoZhu=atof(str);
	*/
}

void CSet::Deal_PaiJu_Y()
{
	CStdioFile File;	
   	CString str;
	string segment;	
	string paijusave;
	CString strtmp1;            //���û�����ĵ��ʴ�txt�ļ��ж�����
	CString strtmp2;
	CString sentence;
	CString sentence1;
    //double b;
	//float value1;
	//int   value2;
	int Length=0;
	int Empty=0;
	int q=0;
	int n=0;
	int j=0;					//�����еĵ��ʼ���
    int i=0;                    //���λ 
	int k=0;
	int l=0;
	int m=0;
	
	int iiii=0;
	int jjjj=0;
	
	
	
	
	//*********************************�ֿ緽��******************************//
    UpdateData(TRUE);
	CEdit *pEdit=(CEdit *)GetDlgItem(IDE_PaiJu_Y);
	fstream File_Clear("Sentence.txt", fstream::out | ios_base::trunc); //ÿ�δ���ǰ�����ǰһ�ε�����
	File_Clear.close();
	UpdateData(TRUE);
	if(m_PaiJu_Y.IsEmpty())
	{
		AfxMessageBox("�����ž಻��Ϊ��!",MB_ICONSTOP);	
		
	}
    else 
	{
		////////////////////////////////////////////////////
		CString Editstr = "";
		CString tempstr = "";
		pEdit->GetWindowText(tempstr);
		Editstr = tempstr+" ";
		char Strbuf[30];
		char Countbuf[10];
		char Databuf[20];
		for(i = 0,j=0; i <Editstr.GetLength();i++)
		{
			Strbuf[j++] = Editstr.GetAt(i);
			if((Editstr.GetAt(i)==',')||(Editstr.GetAt(i)==' '))
			{
				Strbuf[j]='\0';
				int AtFlag = 0;
				for(k=0;k<j;k++)
				{
					if(Strbuf[k]=='@')
					{
						AtFlag=1;
						for(l=0;l<k;l++)
						{
							Countbuf[l]=Strbuf[l];
						}
						Countbuf[l]='\0';
						PaiJuCountSave[iiii++] = atoi(Countbuf);
						for(l=k;l<j;l++)
						{
							Databuf[l-k]=Strbuf[l+1];
						}
						Databuf[l-k]='\0';
						PaiJuDataSave[jjjj++]=atof(Databuf);
						PaiJuCount++;
						break;
					}
				}
				if(AtFlag==0)
				{
					tempstr.Format("%s",Strbuf);
					PaiJuCountSave[iiii++] = 1;
					PaiJuDataSave[jjjj++]=atof(tempstr);
					PaiJuCount++;
					//float tempflo = atof(tempstr);
				}
				j=0;
			}
		}
	}
	Count_Y=iiii;
	PaiJuGeShu_Y=0;
	for(int iii=0;iii<PaiJuCount;iii++)
	{
		PaiJuGeShu_Y=PaiJuGeShu_Y+PaiJuCountSave[iii];
	}
	PaiJuGeShu_Y=PaiJuGeShu_Y+1;
	return ;
	/*		Count_Y=iiii;
	PaiJuGeShu_Y = 0;
	for(int i=0;i<iiii;i++)
	{
	PaiJuGeShu_Y=PaiJuGeShu_Y+PaiJuCountSave[i];
	}
	return;
	//////////////////////////////////////////////////////
	Empty=0;
	sentence=m_PaiJu_Y;
	Length=sentence.GetLength();
	str.Format("%d",Length);
	//	AfxMessageBox(str);
	
	  paijusave= LPCSTR(sentence); 
	  for(i=1;i<=Length;i++)
	  {
	  if(paijusave[i]=='@')
	  {
	  paijusave[i]=' ';
	  }
	  }
	  
		str.Format("%s",paijusave.c_str());
		sentence=str;
		//AfxMessageBox(str);
		
		  
			
			  File.Open("Sentence.txt",CFile::modeReadWrite); 
			  File.WriteString(sentence);                 //��"Sentence.txt"������ݸ�ֵ��string����sentence
			  File.Close();
			  ifstream fileout("Sentence.txt");
			  i=0;
			  while(fileout>>segment)                    //���û��������������Re[n]
			  {
			  CString str;
			  if(i%2==0)
			  {
			  value2=atoi(segment.c_str());
			  PaiJuCountSave[iiii]=value2;
			  iiii++;
			  }
			  if(i%2==1)
			  {
			  value1 = atof(segment.c_str());
			  PaiJuDataSave[jjjj]=value1;
			  jjjj++;
			  }
			  i++;
			  PaiJuCount++;
			  }
			  
				
				  
					}
					
					  for(int iii=0;iii<(PaiJuCount/2);iii++)
					  {
					  PaiJuGeShu_Y=PaiJuGeShu_Y+PaiJuCountSave[iii];
					  }
    PaiJuGeShu_Y=PaiJuGeShu_Y+1;*/
}



void CSet::Deal_ZhuJu_X()
{
	int i=0,j=0,k=0,l=0,m=0,n=0;
	//*********************************�ֿ緽��******************************//
    UpdateData(TRUE);
	CEdit *pEdit=(CEdit *)GetDlgItem(IDE_ZhuJu_X1);
	fstream File_Clear("Sentence.txt", fstream::out | ios_base::trunc); //ÿ�δ���ǰ�����ǰһ�ε�����
	File_Clear.close();
	UpdateData(TRUE);
	CString Editstr = "";
	CString tempstr = "";
	pEdit->GetWindowText(tempstr);
	if(tempstr.IsEmpty())
	{
		AfxMessageBox("�������಻��Ϊ��!",MB_ICONSTOP);	
		
	}
    else 
	{
		////////////////////////////////////////////////////
		Editstr = tempstr+" ";
		char Strbuf[30];
		char Countbuf[10];
		char Databuf[20];
		for(i = 0,j=0; i <Editstr.GetLength();i++)
		{
			Strbuf[j++] = Editstr.GetAt(i);
			if((Editstr.GetAt(i)==',')||(Editstr.GetAt(i)==' '))
			{
				Strbuf[j]='\0';
				int AtFlag = 0;
				for(k=0;k<j;k++)
				{
					if(Strbuf[k]=='@')
					{
						AtFlag=1;
						for(l=0;l<k;l++)
						{
							Countbuf[l]=Strbuf[l];
						}
						Countbuf[l]='\0';
						ZhuJuCountSave[m++] = atoi(Countbuf);
						for(l=k;l<j;l++)
						{
							Databuf[l-k]=Strbuf[l+1];
						}
						Databuf[l-k]='\0';
						ZhuJuDataSave[n++]=atof(Databuf);
						break;
					}
				}
				if(AtFlag==0)
				{
					tempstr.Format("%s",Strbuf);
					ZhuJuCountSave[m++] = 1;
					ZhuJuDataSave[n++]=atof(tempstr);
					//float tempflo = atof(tempstr);
				}
				j=0;
			}
		}
		Count_X=m;
		ZhuJuGeShu_X = 0;
		for(i=0;i<m;i++)
		{
			ZhuJuGeShu_X=ZhuJuGeShu_X+ZhuJuCountSave[i];
		}
		ZhuJuGeShu_X=ZhuJuGeShu_X+1;
	}
	return;
}

void CSet::Deal_BuJu_Z()
{
	int i=0,j=0,k=0,l=0,m=0,n=0;
	//*********************************�ֿ緽��******************************//
    UpdateData(TRUE);
	CEdit *pEdit=(CEdit *)GetDlgItem(IDE_BuJu_Z);
	fstream File_Clear("Sentence.txt", fstream::out | ios_base::trunc); //ÿ�δ���ǰ�����ǰһ�ε�����
	File_Clear.close();
	UpdateData(TRUE);
	CString Editstr = "";
	CString tempstr = "";
	pEdit->GetWindowText(tempstr);
	if(tempstr.IsEmpty())
	{
		AfxMessageBox("���벽�಻��Ϊ��!",MB_ICONSTOP);	
		
	}
    else 
	{
		////////////////////////////////////////////////////
		BuJuCountSave[m++] = 1;
		BuJuDataSave[n++]=XiaBuTuoChengGaoDu;
		BuJuCountSave[m++] = 1;
		BuJuDataSave[n++]=SaoDiGanGaoDu-XiaBuTuoChengGaoDu;
		BuJuCountSave[m++] = 1;
		BuJuDataSave[n++]=0.3+XiaBuTuoChengGaoDu-SaoDiGanGaoDu;
		Editstr = tempstr+" ";
		char Strbuf[30];
		char Countbuf[10];
		char Databuf[20];
		for(i = 0,j=0; i <Editstr.GetLength();i++)
		{
			Strbuf[j++] = Editstr.GetAt(i);
			if((Editstr.GetAt(i)==',')||(Editstr.GetAt(i)==' '))
			{
				Strbuf[j]='\0';
				int AtFlag = 0;
				for(k=0;k<j;k++)
				{
					if(Strbuf[k]=='@')
					{
						AtFlag=1;
						for(l=0;l<k;l++)
						{
							Countbuf[l]=Strbuf[l];
						}
						Countbuf[l]='\0';
						BuJuCountSave[m++] = atoi(Countbuf);
						for(l=k;l<j;l++)
						{
							Databuf[l-k]=Strbuf[l+1];
						}
						Databuf[l-k]='\0';
						BuJuDataSave[n++]=atof(Databuf);
						break;
					}
				}
				if(AtFlag==0)
				{
					tempstr.Format("%s",Strbuf);
					BuJuCountSave[m++] = 1;
					BuJuDataSave[n++]=atof(tempstr);
					//float tempflo = atof(tempstr);
				}
				j=0;
			}
		}
		BuJuCountSave[m++] = 1;
		BuJuDataSave[n++]=DingCengXuanBiChangDu;
		Count_Z=m;
		BuJuGeShu_Z = 0;
		for(i=0;i<m;i++)
		{
			BuJuGeShu_Z=BuJuGeShu_Z+BuJuCountSave[i];
		}
		BuJuGeShu_Z=BuJuGeShu_Z+1;
	}
	return;	
}
void CSet::Ontest() 
{
	// TODO: Add your control notification handler code here
	CString str;
	//	init();
	//	Deal_PaiJu_Y();
	
	str.Format("a:%d,b:%d,c:%d,dc:%d",a,b,c,dc);
	AfxMessageBox(str);
}



void CSet::OnChangeZhuJuX() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_ZhuJuX,str);
	ZhuJuGeShu_X=atoi(str);
	ZhuJuGeShu_X=ZhuJuGeShu_X+1;
	Length_X=ZhuJuGeShu_X*ZhuJu_X;
}

void CSet::OnChangeBuJuZ() 
{
	return;
   	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_BuJuZ,str);
	BuJuGeShu_Z=atoi(str);
	Length_Z=BuJuGeShu_Z*BuJu_Z;
	
}

void CSet::OnChangeSaoDiGanGaoDu() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_SaoDiGanGaoDu,str);
	SaoDiGanGaoDu=atof(str);
	if(SaoDiGanGaoDu>0.35)
	{
		MessageBox("ɨ�ظ˾������߶�ӦС�ڵ���0.35m","��ʾ:", MB_ICONEXCLAMATION);
	}
	
}

void CSet::OnChangeDingCengXuanBi() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_DingCengXuanBi,str);
	DingCengXuanBiChangDu=atof(str);
	if(DingCengXuanBiChangDu>0.7)
	{
		MessageBox("ɨ�ظ˾������߶�ӦС�ڵ���0.35m","��ʾ:", MB_ICONEXCLAMATION);
	}
}

void CSet::OnOutput() 
{
	// TODO: Add your control notification handler code here
	if(FALSE==AddDeviation())
		return;
	int N=3;
	int num=1;//���
	int i=0;//������
	int j=0;
	int k=0;
	int l=0;
	int m=0;
	int n=0;
	CString str;
	init();
    Deal_PaiJu_Y();
    Deal_ZhuJu_X();
    Deal_BuJu_Z();
	if(BuJuGeShu_Z==0)
	{
		AfxMessageBox("����������Ч����ǰ����Ϊ0");
		return ;
	}
	//BuJuGeShu_Z=BuJuGeShu_Z+4;
	
	NodeZongShu=BuJuGeShu_Z*ZhuJuGeShu_X*PaiJuGeShu_Y;
    //NodeZong=new Node[NodeZongShu+1];
	vector < Node > NodeZong;
	NodeZong.resize(NodeZongShu*3);
	for(i=0;i<NodeZongShu*3;i++)
	{
		NodeZong[i].Num=0;
		NodeZong[i].x=0;
		NodeZong[i].y=0;
		NodeZong[i].z=0;
	}
	
	
	
	
	////////////////////////////////////////////////////////////////////////////////
	int BB,BB1,ZZ,ZZ1,PP,PP1;
    //Deal_PaiJu_Y();
    //Deal_ZhuJu_X();
    //Deal_BuJu_Z();
	int tempBu=0;
	int tempZhu=0;
	int tempPai=0;
	//CString filename="h:\\midas.txt";
	//filename=filename+".mct";
	//CStdioFile File;
	//File.Open(filename,CFile::modeCreate|CFile::modeReadWrite);//����ļ����Ȳ����ڵĻ�������ҪCFile::modeCreate������Ͳ���Ҫ��
	//CString TxtStr="";
	float CurZVal = 0.0;
	for(BB=-1;BB<Count_Z;BB++)
	{
		if(BB==-1)
			tempBu=1;
		else
			tempBu=BuJuCountSave[BB];
		for(BB1=0;BB1<tempBu;BB1++)
		{
			if(BB==-1)
				CurZVal=0.0;
			else
				CurZVal=CurZVal+BuJuDataSave[BB];
			float CurXVal = 0.0;
			for(ZZ=-1;ZZ<Count_X;ZZ++)
			{
				if(ZZ==-1)
					tempZhu=1;
				else
					tempZhu=ZhuJuCountSave[ZZ];
				for(ZZ1=0;ZZ1<tempZhu;ZZ1++)
				{
					if(ZZ==-1)
						CurXVal=0.0;
					else
						CurXVal=CurXVal+ZhuJuDataSave[ZZ];
					float CurYVal=0.0;
					for(PP=-1;PP<Count_Y;PP++)
					{
						if(PP==-1)
							tempPai=1;
						else
							tempPai=PaiJuCountSave[PP];
						for(PP1=0;PP1<tempPai;PP1++)
						{
							if(PP==-1)
								CurYVal=0.0;
							else
								CurYVal=CurYVal+PaiJuDataSave[PP];
							NodeZong[num].Num=num;
							NodeZong[num].x=CurXVal;
							NodeZong[num].y=CurYVal;
							NodeZong[num++].z=CurZVal;
							//TxtStr.Format("%.2f,%.2f,%.2f\n",CurXVal,CurYVal,CurZVal);
							//File.WriteString(TxtStr);
						}
					}
				}
			}
		}
	}
	//File.Close();
	
	
	
	
	//**********************��Ԫ************************/
	int MeiCengDanYuanShu=0;
	int ZongDanYuanShu=0;
	
	
	
	//***********************�ļ����****************//
	
	CStdioFile  File1;
	CString filename;
	CString filename1;
	CString fileext;//�ļ���չ��
	CString filepathname;
	CFileDialog fpdlg(FALSE,  NULL,  NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"(�ļ�����)(*.mct)|*.mct|(�ļ�����)(*.txt)|*.txt|�����ļ�(*.*)|*.*||",NULL);
	
	if(fpdlg.DoModal() == IDOK)
	{
		filename = fpdlg.GetFileName();
		fileext = fpdlg.GetFileExt();//�ļ���չ��
		filepathname = fpdlg.GetPathName(); 
	}
	else if (fpdlg.DoModal() == IDCANCEL)
	{
		AfxMessageBox("û�ж�ȡsgy�ļ�");
		return;
	}
	
	filename1=filename+".mct";
	File1.Open(filename1,CFile::modeCreate|CFile::modeReadWrite);//����ļ����Ȳ����ڵĻ�������ҪCFile::modeCreate������Ͳ���Ҫ��
	// str=_T("     ����������:         ");
	// File1.WriteString(str);
	// File1.WriteString("\n");	   
	str.Format(";---------------------------------------------------------------------------\n");
	File1.WriteString(str);
	str.Format(";  MIDAS/Civil Text(MCT) File.\n");
	File1.WriteString(str);
	CTime t = CTime::GetCurrentTime();
	str.Format(";  Date : %d/%d/%d\n",t.GetYear(),t.GetMonth(),t.GetDay());
	File1.WriteString(str);
	str.Format(";---------------------------------------------------------------------------\n\n");
	File1.WriteString(str);
	str.Format("*VERSION\n   8.0.5\n\n");
	File1.WriteString(str);
	str.Format("*UNIT    ; Unit System\n; FORCE, LENGTH, HEAT, TEMPER\n   KN   , M, KJ, C\n\n");
	File1.WriteString(str);
	
	
	
	
	//***************************�ڵ����ǰ׺*************************//
	str=_T("*NODE    ; Nodes");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	str=_T("; iNO, X, Y, Z");
	File1.WriteString(str);
	File1.WriteString("\n");
	for(int h=1;h<NodeZongShu+1;h++)
	{
		str.Format("%d,  %7.2f , %7.2f , %7.2f",NodeZong[h].Num,NodeZong[h].x,NodeZong[h].y,NodeZong[h].z);
		File1.WriteString(str);
		File1.WriteString("\n");
	}
	File1.WriteString("\n");
	File1.WriteString("\n");
	//***************************��б��Ԫ���*************************//
	str=_T("*ELEMENT ");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	/*
	Dim dy, dc, qd, zd As Integer
	' dy��Ԫ��� dc����ڵ�����qd��Ԫ���ڵ�ţ�zd��Ԫ�ص�ڵ��
	dy = 0
	dc = (a + 1) * (b + 1)
	*/
	
	a=ZhuJuGeShu_X-1;
	b=PaiJuGeShu_Y-1;
	c=BuJuGeShu_Z-3;//-3;�ﺣ��20:00 2016/9/8
	float z=BuJu_Z;
	int HorizPoleNum=0;//��¼������ܸ���
	dy=0;
	dc=(a+1)*(b+1);
	int vc=0;
	int va=0;
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////�״�ִ��������Ԫ��ģ�����Լ����ܵ�Ԫ��////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	for(vc=2;vc<=c+1;vc++)
	{
		for(va=1;va<=a+1;va++)
		{
			for(qd=(va-1)*b+va+vc*dc;qd<=va-1+va*b+vc*dc;qd++)
			{
				dy=dy+1;
			}
		}
		
	}
	//���2/2
	for(vc=2;vc<=c+1;vc++)
	{ 
		for(qd=1+dc*vc;qd<=a*(b+1)+dc*vc;qd++)
		{
			dy=dy+1;
		}
		
	}
	HorizPoleNum = dy;
	//����
	for(vc=0;vc<=c+1;vc++)
	{ 
		for(qd=1+dc*vc;qd<=(a+1)*(b+1)+dc*vc;qd++)
		{
			dy=dy+1;
		}
		
	}
	int ZCount=0;
	int ZNum[20];
	float tempZDate=0.0;
	int tempZNum=2;
	ZNum[ZCount++]=1+ZhuJuGeShu_X*PaiJuGeShu_Y*tempZNum;
	for(i=2;i<Count_Z-1;i++)
	{
		for(j=0;j<BuJuCountSave[i];j++)
		{
			tempZDate=tempZDate+BuJuDataSave[i];
			if(tempZDate>=4.8)
			{
				ZNum[ZCount++]=1+ZhuJuGeShu_X*PaiJuGeShu_Y*tempZNum;
				tempZDate=BuJuDataSave[i];
			}
			tempZNum++;
		}
	}
	if(ZNum[ZCount-1]!=1+ZhuJuGeShu_X*PaiJuGeShu_Y*(BuJuGeShu_Z-1))
	{
		ZNum[ZCount++]=1+ZhuJuGeShu_X*PaiJuGeShu_Y*(BuJuGeShu_Z-2);
	}
	int Turn = 1;
	//////////////////////ˮƽ������///////////////////////////
	for(i=0;i<ZCount;i++)
	{
		//int Max=ZhuJuGeShu_X>PaiJuGeShu_Y?ZhuJuGeShu_X:PaiJuGeShu_Y;
		//int Min=ZhuJuGeShu_X<PaiJuGeShu_Y?ZhuJuGeShu_X:PaiJuGeShu_Y;
		for(k=0;k<=(PaiJuGeShu_Y-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=ZNum[i]+k*5;
			for(j=1+5*k;j<=PaiJuGeShu_Y-1;j++)
			{
				dy = dy + 1;
				if((j-5*k)==ZhuJuGeShu_X-1)
					break;
			}
		}
		for(k=1;k<=(ZhuJuGeShu_X-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=ZNum[i]+k*5*PaiJuGeShu_Y;
			for(j=1+5*k;j<=ZhuJuGeShu_X-1;j++)
			{
				dy = dy + 1;
				if((j-5*k)==PaiJuGeShu_Y-1)
					break;
			}
		}
		for(k=1;k<=(ZhuJuGeShu_X-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=ZNum[i]+k*5*PaiJuGeShu_Y;
			for(j=1;j<=5*k;j++)
			{
				dy = dy + 1;
				if(j==PaiJuGeShu_Y-1)
					break;
			}
		}
		if((ZhuJuGeShu_X-1)%5>=3)
		{
			zd=ZNum[i]+ZhuJuGeShu_X*PaiJuGeShu_Y-PaiJuGeShu_Y;
			for(j=1;j<=PaiJuGeShu_Y-1;j++)
			{
				dy = dy + 1;
				if(j==ZhuJuGeShu_X-1)
					break;
			}
		}
		for(k=(ZhuJuGeShu_X-1)%5;k<PaiJuGeShu_Y-1;k+=5)//1��������ĩβ�������
		{
			zd=ZNum[i]+ZhuJuGeShu_X*PaiJuGeShu_Y-PaiJuGeShu_Y+k;
			for(j=1;j<=ZhuJuGeShu_X-1;j++)
			{
				dy = dy + 1;
				if(j+k==PaiJuGeShu_Y-1)
					break;
			}
		}
	}
	//File1.Close();
	//AfxMessageBox("success");
	//return;
	//File1.WriteString(";;�����������\n");
	
	//////////////////////////////////////////////////////////
	///////////////////////�����������//////////////////////////////
	for(i=0;i<=(ZhuJuGeShu_X-1-1)/5+1;i++)
	{
		//int Max=ZhuJuGeShu_X>PaiJuGeShu_Y?ZhuJuGeShu_X:PaiJuGeShu_Y;
		//int Min=ZhuJuGeShu_X<PaiJuGeShu_Y?ZhuJuGeShu_X:PaiJuGeShu_Y;
		for(k=0;k<=(PaiJuGeShu_Y-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=1+2*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y+k*5;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=1+2*ZhuJuGeShu_X*PaiJuGeShu_Y+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*5;
			for(j=1;j<=BuJuGeShu_Z-5;j++)
			{
				dy = dy + 1;
				if((j+5*k)==PaiJuGeShu_Y-1)
					break;
			}
		}
		for(k=1;k<=(BuJuGeShu_Z-5)/5;k++)//1��������ĩβ�������
		{
			zd=1+3*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y*5;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=1+3*ZhuJuGeShu_X*PaiJuGeShu_Y+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y*5;
			for(j=1;j<=PaiJuGeShu_Y-1;j++)
			{
				dy = dy + 1;
				if((j+5*k)==BuJuGeShu_Z-5)
					break;
			}
		}
		/////////////////////////////0915��ͣ
		for(k=1;k<=(PaiJuGeShu_Y-1)/5;k++)//1��������ĩβ�������
		{
			zd=1+2*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y+k*5;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=1+2*ZhuJuGeShu_X*PaiJuGeShu_Y+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*5;
			for(j=1;j<=5*k;j++)
			{
				dy = dy + 1;
				if(j==BuJuGeShu_Z-5)
					break;
			}
		}
		if((PaiJuGeShu_Y-1)%5>=3)
		{
			zd=2*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y+PaiJuGeShu_Y;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=3*ZhuJuGeShu_X*PaiJuGeShu_Y;
			for(j=1;j<=PaiJuGeShu_Y-1;j++)
			{
				dy = dy + 1;
				if(j==BuJuGeShu_Z-5)
					break;
			}
		}
		for(k=(PaiJuGeShu_Y-1)%5+3;k<BuJuGeShu_Z-3;k+=5)//1��������ĩβ�������
		{
			zd=PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y;
			for(j=1;j+k<=BuJuGeShu_Z-2;j++)
			{
				dy = dy + 1;
				if(j==PaiJuGeShu_Y-1)
					break;
			}
		}
	}
	
	///////////////////////˳���������//////////////////////////////
	for(i=0;i<=(PaiJuGeShu_Y-1-1)/5+1;i++)
	{
		//int Max=PaiJuGeShu_Y>ZhuJuGeShu_X?PaiJuGeShu_Y:ZhuJuGeShu_X;
		//int Min=PaiJuGeShu_Y<ZhuJuGeShu_X?PaiJuGeShu_Y:ZhuJuGeShu_X;
		for(k=0;k<=(ZhuJuGeShu_X-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=1+2*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5+k*5*PaiJuGeShu_Y;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=1+2*PaiJuGeShu_Y*ZhuJuGeShu_X+PaiJuGeShu_Y-1+k*5*PaiJuGeShu_Y;
			for(j=1;j<=BuJuGeShu_Z-5;j++)
			{
				dy = dy + 1;
				if((j+5*k)==ZhuJuGeShu_X-1)
					break;
			}
		}
		for(k=1;k<=(BuJuGeShu_Z-5)/5;k++)//1��������ĩβ�������
		{
			zd=1+3*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5+k*5*PaiJuGeShu_Y*ZhuJuGeShu_X;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=3*PaiJuGeShu_Y*ZhuJuGeShu_X+PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y*5;
			for(j=1;j<=ZhuJuGeShu_X-1;j++)
			{
				dy = dy + 1;
				if((j+5*k)==BuJuGeShu_Z-5)
					break;
			}
		}
		/////////////////////////////0915��ͣ
		for(k=1;k<=(ZhuJuGeShu_X-1)/5;k++)//1��������ĩβ�������
		{
			zd=1+2*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5+k*5*PaiJuGeShu_Y;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=2*PaiJuGeShu_Y*ZhuJuGeShu_X+PaiJuGeShu_Y+k*5*PaiJuGeShu_Y;
			for(j=1;j<=5*k;j++)
			{
				dy = dy + 1;
				if(j==BuJuGeShu_Z-5)
					break;
			}
		}
		if((ZhuJuGeShu_X-1)%5>=3)
		{
			zd=1+2*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=3*PaiJuGeShu_Y*ZhuJuGeShu_X;
			for(j=1;j<=ZhuJuGeShu_X-1;j++)
			{
				dy = dy + 1;
				if(j==BuJuGeShu_Z-5)
					break;
			}
		}
		for(k=(ZhuJuGeShu_X-1)%5+3;k<BuJuGeShu_Z-3;k+=5)//1��������ĩβ�������
		{
			zd=1+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*PaiJuGeShu_Y*ZhuJuGeShu_X+PaiJuGeShu_Y;
			for(j=1;j+k<=BuJuGeShu_Z-2;j++)
			{
				dy = dy + 1;
				if(j==ZhuJuGeShu_X-1)
					break;
			}
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	////////////////////////���¹��̲ſ�ʼִ��������Ԫ��ģ����//////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	dy=0;
	//���1/2
	for(vc=2;vc<=c+1;vc++)
	{
		for(va=1;va<=a+1;va++)
		{
			for(qd=(va-1)*b+va+vc*dc;qd<=va-1+va*b+vc*dc;qd++)
			{
				zd=qd+1;
				dy=dy+1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
			}
		}
		
	}
	//���2/2
	for(vc=2;vc<=c+1;vc++)
	{ 
		for(qd=1+dc*vc;qd<=a*(b+1)+dc*vc;qd++)
		{
			zd=qd+b+1;
			dy=dy+1;
			str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
			File1.WriteString(str);
			File1.WriteString("\n");
		}
		
	}
	HorizPoleNum = dy;
	//����
	for(vc=0;vc<=c+1;vc++)
	{ 
		for(qd=1+dc*vc;qd<=(a+1)*(b+1)+dc*vc;qd++)
		{
			zd=qd+dc;
			dy=dy+1;
			str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
			File1.WriteString(str);
			File1.WriteString("\n");
		}
		
	}
	//File1.Close();
	//AfxMessageBox("success");
	//return;
	/*int ZCount=0;
	int ZNum[20];
	float tempZDate=0.0;
	int tempZNum=2;
	ZNum[ZCount++]=1+ZhuJuGeShu_X*PaiJuGeShu_Y*tempZNum;
	for(i=2;i<Count_Z-1;i++)
	{
	for(j=0;j<BuJuCountSave[i];j++)
	{
	tempZDate=tempZDate+BuJuDataSave[i];
	if(tempZDate>=4.8)
	{
				ZNum[ZCount++]=1+ZhuJuGeShu_X*PaiJuGeShu_Y*tempZNum;
				tempZDate=BuJuDataSave[i];
				}
				tempZNum++;
				}
				}
				if(ZNum[ZCount-1]!=1+ZhuJuGeShu_X*PaiJuGeShu_Y*(BuJuGeShu_Z-1))
				{
				ZNum[ZCount++]=1+ZhuJuGeShu_X*PaiJuGeShu_Y*(BuJuGeShu_Z-2);
	}*/
	//////////////////////ˮƽ������///////////////////////////
	for(i=0;i<ZCount;i++)
	{
		//int Max=ZhuJuGeShu_X>PaiJuGeShu_Y?ZhuJuGeShu_X:PaiJuGeShu_Y;
		//int Min=ZhuJuGeShu_X<PaiJuGeShu_Y?ZhuJuGeShu_X:PaiJuGeShu_Y;
		for(k=0;k<=(PaiJuGeShu_Y-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=ZNum[i]+k*5;
			for(j=1+5*k;j<=PaiJuGeShu_Y-1;j++)
			{
				qd=zd;
				zd=zd+PaiJuGeShu_Y+1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if((j-5*k)==ZhuJuGeShu_X-1)
					break;
			}
		}
		for(k=1;k<=(ZhuJuGeShu_X-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=ZNum[i]+k*5*PaiJuGeShu_Y;
			for(j=1+5*k;j<=ZhuJuGeShu_X-1;j++)
			{
				qd=zd;
				zd=zd+PaiJuGeShu_Y+1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if((j-5*k)==PaiJuGeShu_Y-1)
					break;
			}
		}
		for(k=1;k<=(ZhuJuGeShu_X-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=ZNum[i]+k*5*PaiJuGeShu_Y;
			for(j=1;j<=5*k;j++)
			{
				qd=zd;
				zd=zd-PaiJuGeShu_Y+1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if(j==PaiJuGeShu_Y-1)
					break;
			}
		}
		if((ZhuJuGeShu_X-1)%5>=3)
		{
			zd=ZNum[i]+ZhuJuGeShu_X*PaiJuGeShu_Y-PaiJuGeShu_Y;
			for(j=1;j<=PaiJuGeShu_Y-1;j++)
			{
				qd=zd;
				zd=zd-PaiJuGeShu_Y+1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if(j==ZhuJuGeShu_X-1)
					break;
			}
		}
		for(k=(ZhuJuGeShu_X-1)%5;k<PaiJuGeShu_Y-1;k+=5)//1��������ĩβ�������
		{
			zd=ZNum[i]+ZhuJuGeShu_X*PaiJuGeShu_Y-PaiJuGeShu_Y+k;
			for(j=1;j<=ZhuJuGeShu_X-1;j++)
			{
				qd=zd;
				zd=zd-PaiJuGeShu_Y+1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if(j+k==PaiJuGeShu_Y-1)
					break;
			}
		}
	}
	//File1.Close();
	//AfxMessageBox("success");
	//return;
	//File1.WriteString(";;�����������\n");
	
	//////////////////////////////////////////////////////////
	///////////////////////�����������//////////////////////////////
	for(i=0;i<=(ZhuJuGeShu_X-1-1)/5+1;i++)
	{
		//int Max=ZhuJuGeShu_X>PaiJuGeShu_Y?ZhuJuGeShu_X:PaiJuGeShu_Y;
		//int Min=ZhuJuGeShu_X<PaiJuGeShu_Y?ZhuJuGeShu_X:PaiJuGeShu_Y;
		for(k=0;k<=(PaiJuGeShu_Y-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=1+2*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y+k*5;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=1+2*ZhuJuGeShu_X*PaiJuGeShu_Y+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*5;
			for(j=1;j<=BuJuGeShu_Z-5;j++)
			{
				qd=zd;
				zd=zd+PaiJuGeShu_Y*ZhuJuGeShu_X*(j==1?2:1)+1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if((j+5*k)==PaiJuGeShu_Y-1)
					break;
			}
		}
		for(k=1;k<=(BuJuGeShu_Z-5)/5;k++)//1��������ĩβ�������
		{
			zd=1+3*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y*5;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=1+3*ZhuJuGeShu_X*PaiJuGeShu_Y+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y*5;
			for(j=1;j<=PaiJuGeShu_Y-1;j++)
			{
				qd=zd;
				zd=zd+PaiJuGeShu_Y*ZhuJuGeShu_X+1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if((j+5*k)==BuJuGeShu_Z-5)
					break;
			}
		}
		/////////////////////////////0915��ͣ
		for(k=1;k<=(PaiJuGeShu_Y-1)/5;k++)//1��������ĩβ�������
		{
			zd=1+2*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y+k*5;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=1+2*ZhuJuGeShu_X*PaiJuGeShu_Y+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*5;
			for(j=1;j<=5*k;j++)
			{
				qd=zd;
				zd=zd+PaiJuGeShu_Y*ZhuJuGeShu_X*(j==1?2:1)-1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if(j==BuJuGeShu_Z-5)
					break;
			}
		}
		if((PaiJuGeShu_Y-1)%5>=3)
		{
			zd=2*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y+PaiJuGeShu_Y;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=3*ZhuJuGeShu_X*PaiJuGeShu_Y;
			for(j=1;j<=PaiJuGeShu_Y-1;j++)
			{
				qd=zd;
				zd=zd+PaiJuGeShu_Y*ZhuJuGeShu_X*(j==1?2:1)-1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if(j==BuJuGeShu_Z-5)
					break;
			}
		}
		for(k=(PaiJuGeShu_Y-1)%5+3;k<BuJuGeShu_Z-3;k+=5)//1��������ĩβ�������
		{
			zd=PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y+i*5*PaiJuGeShu_Y;
			if(i==(ZhuJuGeShu_X-1-1)/5+1)
				zd=PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y;
			for(j=1;j+k<=BuJuGeShu_Z-2;j++)
			{
				qd=zd;
				zd=zd+PaiJuGeShu_Y*ZhuJuGeShu_X-1;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if(j==PaiJuGeShu_Y-1)
					break;
			}
		}
	}
	
	///////////////////////˳���������//////////////////////////////
	for(i=0;i<=(PaiJuGeShu_Y-1-1)/5+1;i++)
	{
		//int Max=PaiJuGeShu_Y>ZhuJuGeShu_X?PaiJuGeShu_Y:ZhuJuGeShu_X;
		//int Min=PaiJuGeShu_Y<ZhuJuGeShu_X?PaiJuGeShu_Y:ZhuJuGeShu_X;
		for(k=0;k<=(ZhuJuGeShu_X-1-1)/5;k++)//1��������ĩβ�������
		{
			zd=1+2*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5+k*5*PaiJuGeShu_Y;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=1+2*PaiJuGeShu_Y*ZhuJuGeShu_X+PaiJuGeShu_Y-1+k*5*PaiJuGeShu_Y;
			for(j=1;j<=BuJuGeShu_Z-5;j++)
			{
				qd=zd;
				zd=zd+ZhuJuGeShu_X*PaiJuGeShu_Y*(j==1?2:1)+PaiJuGeShu_Y;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if((j+5*k)==ZhuJuGeShu_X-1)
					break;
			}
		}
		for(k=1;k<=(BuJuGeShu_Z-5)/5;k++)//1��������ĩβ�������
		{
			zd=1+3*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5+k*5*PaiJuGeShu_Y*ZhuJuGeShu_X;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=3*PaiJuGeShu_Y*ZhuJuGeShu_X+PaiJuGeShu_Y+k*ZhuJuGeShu_X*PaiJuGeShu_Y*5;
			for(j=1;j<=ZhuJuGeShu_X-1;j++)
			{
				qd=zd;
				zd=zd+ZhuJuGeShu_X*PaiJuGeShu_Y+PaiJuGeShu_Y;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if((j+5*k)==BuJuGeShu_Z-5)
					break;
			}
		}
		/////////////////////////////0915��ͣ
		for(k=1;k<=(ZhuJuGeShu_X-1)/5;k++)//1��������ĩβ�������
		{
			zd=1+2*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5+k*5*PaiJuGeShu_Y;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=2*PaiJuGeShu_Y*ZhuJuGeShu_X+PaiJuGeShu_Y+k*5*PaiJuGeShu_Y;
			for(j=1;j<=5*k;j++)
			{
				qd=zd;
				zd=zd+ZhuJuGeShu_X*PaiJuGeShu_Y*(j==1?2:1)-PaiJuGeShu_Y;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if(j==BuJuGeShu_Z-5)
					break;
			}
		}
		if((ZhuJuGeShu_X-1)%5>=3)
		{
			zd=1+2*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=3*PaiJuGeShu_Y*ZhuJuGeShu_X;
			for(j=1;j<=ZhuJuGeShu_X-1;j++)
			{
				qd=zd;
				zd=zd+ZhuJuGeShu_X*PaiJuGeShu_Y*(j==1?2:1)-PaiJuGeShu_Y;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if(j==BuJuGeShu_Z-5)
					break;
			}
		}
		for(k=(ZhuJuGeShu_X-1)%5+3;k<BuJuGeShu_Z-3;k+=5)//1��������ĩβ�������
		{
			zd=1+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*PaiJuGeShu_Y*ZhuJuGeShu_X+i*5;
			if(i==(PaiJuGeShu_Y-1-1)/5+1)
				zd=(ZhuJuGeShu_X-1)*PaiJuGeShu_Y+k*PaiJuGeShu_Y*ZhuJuGeShu_X+PaiJuGeShu_Y;
			for(j=1;j+k<=BuJuGeShu_Z-2;j++)
			{
				qd=zd;
				zd=zd+ZhuJuGeShu_X*PaiJuGeShu_Y-PaiJuGeShu_Y;
				dy = dy + 1;
				str.Format("%d , %s ,    %d,    %d,    %d,    %d,    %d",dy,"BEAM",1,1,qd,zd,0);
				File1.WriteString(str);
				File1.WriteString("\n");
				if(j==ZhuJuGeShu_X-1)
					break;
			}
		}
	}
	
	
	
	qy = 1.1 * (GangJinHunNingTu + MoBanFangLeng);
	str.Format("%f",qy);
	
	if (DiYiCiYuYa + DiErCiYuYa + DiSanCiYuYa > 1.4) //Then
	{
		AfxMessageBox("Ԥѹ�����Ƿ����");
	}
	//************Lines = Lines & readFile("d:\��������ģ\֧���ļ�\GROUP.mct")**********//
	
	str.Format("*GROUP    ; Group; NAME, NODE_LIST, ELEM_LIST, PLANE_TYPE",1,1,qd,zd,0);
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	//*******  Lines = Lines & "��������" & "," & 1 & "to" & m1 & vbCrLf  ***********
	//ZhuJuGeShu_X*PaiJuGeShu_Y*(BuJuGeShu_Z
	m1=(PaiJuGeShu_Y-1)*ZhuJuGeShu_X*(BuJuGeShu_Z-3);
	str.Format("%s ,,   %d   %s   %d","��������",1,"to",m1);
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	//************Lines = Lines & "˳������" & "," & m1 + 1 & "to" & m2 & vbCrLf *******
	m2=m1+(ZhuJuGeShu_X-1)*PaiJuGeShu_Y*(BuJuGeShu_Z-3);
	str.Format("%s ,,    %d   %s   %d","˳������",m1+1,"to",m2);
	File1.WriteString(str);
	File1.WriteString("\n");
	
	//************Lines = Lines & "����" & "," & m2 + 1 & "to" & m3 & vbCrLf *************
	m3=m2+ZhuJuGeShu_X*PaiJuGeShu_Y*(BuJuGeShu_Z-1);
	str.Format("%s ,,    %d   %s   %d","����",m2+1,"to",m3);
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	//*********** Lines = Lines & "������" & "," & m3 + 1 & "to" & dy & vbCrLf **********
	
	str.Format("%s ,,    %d   %s   %d","������",m3+1,"to",dy);
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	//'�߽��顢�����鶨��
	//************* Lines = Lines & readFile("d:\��������ģ\֧���ļ�\BNDR-GROUP.mct") ************
	
	str=_T("*BNDR-GROUP    ; Boundary Group");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NAME");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("�ػ�֧��\n�½�\n���-����\n������-����");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*LOAD-GROUP    ; Load Group");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NAME");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("Ԥѹ��һ��");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("Ԥѹ�ڶ���");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("Ԥѹ������");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("������һ��");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("�����ڶ���");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("�����");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("֧������");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("ģ�巽���");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("���ӹ���");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("ʩ����Ա��е");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("��������");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	//'�������ԡ����涨��
	//*******  Lines = Lines & readFile("d:\��������ģ\֧���ļ�\MATERIAL.mct") ************
	str=_T("*MATERIAL    ; Material");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iMAT, TYPE, MNAME, SPHEAT, HEATCO, PLAST, TUNIT, bMASS, DAMPRATIO, [DATA1]          ; STEEL, CONC, USER");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iMAT, TYPE, MNAME, SPHEAT, HEATCO, PLAST, TUNIT, bMASS, DAMPRATIO, [DATA2], [DATA2] ; SRC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA1] : 1, DB, NAME, CODE ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA1] : 2, ELAST, POISN, THERMAL, DEN, MASS");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA1] : 3, Ex, Ey, Ez, Tx, Ty, Tz, Sxy, Sxz, Syz, Pxy, Pxz, Pyz, DEN, MASS   ; Orthotropic");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA2] : 1, DB, NAME, CODE or 2, ELAST, POISN, THERMAL, DEN, MASS");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("    1, STEEL, Q235              , 0, 0, , C, NO, 0.02, 1, GB03(S)    ,            , Q235  ");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	str=_T("*MATL-COLOR");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iMAT, W_R, W_G, W_B, HF_R, HF_G, HF_B, HE_R, HE_G, HE_B, bBLEND, FACT");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("    1, 255,   0,   0,    0, 255,   0,    0,   0, 255,  NO, 0.5");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	
	str=_T("*SECTION    ; Section");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, [DATA1], [DATA2]                    ; 1st line - DB/USER");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, BLT, D1, ..., D8, iCEL              ; 1st line - VALUE");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       AREA, ASy, ASz, Ixx, Iyy, Izz                                          ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       CyP, CyM, CzP, CzM, QyB, QzB, PERI_OUT, PERI_IN, Cy, Cz                ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Y1, Y2, Y3, Y4, Z1, Z2, Z3, Z4, Zyy, Zzz                               ; 4th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, ELAST, DEN, POIS, POIC, SF          ; 1st line - SRC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       D1, D2, [SRC]                                                          ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, 1, DB, NAME1, NAME2, D1, D2         ; 1st line - COMBINED");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, 2, D11, D12, D13, D14, D15, D21, D22, D23, D24");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET2], bSD, SHAPE, iyVAR, izVAR, STYPE                ; 1st line - TAPERED");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       DB, NAME1, NAME2                                                       ; 2nd line(STYPE=DB)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [DIM1], [DIM2]                                                         ; 2nd line(STYPE=USER)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       D11, D12, D13, D14, D15, D16, D17, D18                                 ; 2nd line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       AREA1, ASy1, ASz1, Ixx1, Iyy1, Izz1                                    ; 3rd line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       CyP1, CyM1, CzP1, CzM1, QyB1, QzB1, PERI_OUT1, PERI_IN1, Cy1, Cz1      ; 4th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Y11, Y12, Y13, Y14, Z11, Z12, Z13, Z14, Zyy1, Zyy2                     ; 5th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       D21, D22, D23, D24, D25, D26, D27, D28                                 ; 6th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       AREA2, ASy2, ASz2, Ixx2, Iyy2, Izz2                                    ; 7th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       CyP2, CyM2, CzP2, CzM2, QyB2, QzB2, PERI_OUT2, PERI_IN2, Cy2, Cz2      ; 8th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Y21, Y22, Y23, Y24, Z21, Z22, Z23, Z24, Zyy2, Zzz2                     ; 9th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       OPT1, OPT2, [JOINT]                                                    ; 2nd line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       ELAST, DEN, POIS, POIC                                                 ; 2nd line(STYPE=PSC-CMPW)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bSHEARCHK, [SCHK-I], [SCHK-J], [WT-I], [WT-J], WI, WJ, bSYM, bSIDEHOLE ; 3rd line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bSHEARCHK, bSYM, bHUNCH, [CMPWEB-I], [CMPWEB-J]                        ; 3rd line(STYPE=PSC-CMPW)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bUSERDEFMESHSIZE, MESHSIZE, bUSERINPSTIFF, [STIFF-I], [STIFF-J]        ; 4th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]-i                                                             ; 5th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]-i                                                             ; 6th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]-i                                                             ; 7th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]-i                                                             ; 8th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]-j                                                             ; 9th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]-j                                                             ; 10th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]-j                                                             ; 11th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]-j                                                             ; 12th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       GN, CTC, Bc, Tc, Hh, EsEc, DsDc, Ps, Pc, bMULTI, EsEc-L, EsEc-S        ; 2nd line(STYPE=CMP-B/I)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW_i, Hw_i, tw_i, B_i, Bf1_i, tf1_i, B2_i, Bf2_i, tf2_i                ; 3rd line(STYPE=CMP-B/I)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW_j, Hw_j, tw_j, B_j, Bf1_j, tf1_j, B2_j, Bf2_j, tf2_j                ; 4th line(STYPE=CMP-B/I)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       N1, N2, Hr, Hr2, tr1, tr2                                              ; 5th line(STYPE=CMP-B)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       GN, CTC, Bc, Tc, Hh, EgdEsb, DgdDsb, Pgd, Psb, bSYM, SW_i, SW_j        ; 2nd line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       OPT1, OPT2, [JOINT]                                                    ; 3rd line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]-i                                                             ; 4th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]-i                                                             ; 5th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]-i                                                             ; 6th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]-i                                                             ; 7th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]-j                                                             ; 8th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]-j                                                             ; 9th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]-j                                                             ; 10th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]-j                                                             ; 11th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, STYPE1, STYPE2                             ; 1st line - CONSTRUCT");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SHAPE, ...(same with other type data from shape)                       ; Before (STYPE1)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SHAPE, ...(same with other type data from shape)                       ; After  (STYPE2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE                                      ; 1st line - COMPOSITE-SB");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Hw, tw, B, Bf1, tf1, B2, Bf2, tf2                                      ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       N1, N2, Hr, Hr2, tr1, tr2                                              ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW, GN, CTC, Bc, Tc, Hh, EsEc, DsDc, Ps, Pc, bMulti, Elong, Esh        ; 4th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE                                      ; 1st line - COMPOSITE-SI");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Hw, tw, B, tf1, B2, tf2                                                ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW, GN, CTC, Bc, Tc, Hh, EsEc, DsDc, Ps, Pc, bMulti, Elong, Esh        ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE                                      ; 1st line - COMPOSITE-CI/CT");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       OPT1, OPT2, [JOINT]                                                    ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]                                                               ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]                                                               ; 4th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]                                                               ; 5th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]                                                               ; 6th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW, GN, CTC, Bc, Tc, Hh, EgdEsb, DgdDsb, Pgd, Psb                      ; 7th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE                                      ; 1st line - PSC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       OPT1, OPT2, [JOINT]                                                    ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bSHEARCHK, [SCHK], [WT], WIDTH, bSYM, bSIDEHOLE                        ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bUSERDEFMESHSIZE, MESHSIZE, bUSERINPSTIFF, [STIFF]                     ; 4th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]                                                               ; 5th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]                                                               ; 6th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]                                                               ; 7th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]                                                               ; 8th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA1] : 1, DB, NAME or 2, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA2] : CCSHAPE or iCEL or iN1, iN2");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SRC]  : 1, DB, NAME1, NAME2 or 2, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, iN1, iN2");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DIM1], [DIM2] : D1, D2, D3, D4, D5, D6, D7, D8");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [OFFSET] : OFFSET, iCENT, iREF, iHORZ, HUSER, iVERT, VUSER");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [OFFSET2]: OFFSET, iCENT, iREF, iHORZ, HUSERI, HUSERJ, iVERT, VUSERI, VUSERJ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [JOINT]  :  8(1CELL, 2CELL), 13(3CELL),  9(PSCM),  8(PSCH), 9(PSCT),  2(PSCB), 0(nCELL),  2(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SIZE-A] :  6(1CELL, 2CELL), 10(3CELL), 10(PSCM),  6(PSCH), 8(PSCT), 10(PSCB), 5(nCELL), 11(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SIZE-B] :  6(1CELL, 2CELL), 12(3CELL),  6(PSCM),  6(PSCH), 8(PSCT),  6(PSCB), 8(nCELL), 18(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SIZE-C] : 10(1CELL, 2CELL), 13(3CELL),  9(PSCM), 10(PSCH), 7(PSCT),  8(PSCB), 0(nCELL), 11(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SIZE-D] :  8(1CELL, 2CELL), 13(3CELL),  6(PSCM),  7(PSCH), 8(PSCT),  5(PSCB), 0(nCELL), 18(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [STIFF]  : AREA, ASy, ASz, Ixx, Iyy, Izz");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SCHK]   : bAUTO_Z1, Z1, bAUTO_Z3, Z3");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [WT]     : bAUTO_TOR, TOR, bAUTO_SHR1, SHR1, bAUTO_SHR2, SHR2, bAUTO_SHR3, SHR3");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [CMPWEB] : EFD, LRF, A, B, H, T");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	File1.WriteString("\n");
	CString tempstr="";
	((CEdit*)GetDlgItem(IDE_GangGuanWaiJing))->GetWindowText(tempstr);
	D=atof(tempstr);
	D_Deviation[1]=D;
	D_Deviation_Per[1]=100;
	((CEdit*)GetDlgItem(IDE_GangGuanBiHou))->GetWindowText(tempstr);
	tw=atof(tempstr);
	tw_Deviation[1]=tw;
	tw_Deviation_Per[1]=100;
	int SectionCount=1;
	for(i=1;i<=D_Deviation_Per[0];i++)
	{
		for(j=1;j<=tw_Deviation_Per[0];j++)
		{
			str.Format("    %d, DBUSER    , �ֹܽ���          , CC, 0, 0, 0, 0, 0, 0, YES, P  , 2, %.3f, %.4f, 0, 0, 0, 0, 0, 0, 0, 0\n\n",SectionCount++,D_Deviation[i],tw_Deviation[j]);
			File1.WriteString(str);
		}
	}
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	str=_T("*SECT-COLOR");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, W_R, W_G, W_B, HF_R, HF_G, HF_B, HE_R, HE_G, HE_B, bBLEND, FACT");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("    1, 255,   0,   0,    0, 255,   0,    0,   0, 255,  NO, 0.5");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	str=_T("*DGN-SECT");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, [DATA1], [DATA2]                    ; 1st line - DB/USER");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, BLT, D1, ..., D8, iCEL              ; 1st line - VALUE");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       AREA, ASy, ASz, Ixx, Iyy, Izz                                          ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       CyP, CyM, CzP, CzM, QyB, QzB, PERI_OUT, PERI_IN, Cy, Cz                ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Y1, Y2, Y3, Y4, Z1, Z2, Z3, Z4, Zyy, Zzz                               ; 4th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, ELAST, DEN, POIS, POIC, SF          ; 1st line - SRC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       D1, D2, [SRC]                                                          ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, 1, DB, NAME1, NAME2, D1, D2         ; 1st line - COMBINED");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE, 2, D11, D12, D13, D14, D15, D21, D22, D23, D24");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET2], bSD, SHAPE, iyVAR, izVAR, STYPE                ; 1st line - TAPERED");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       DB, NAME1, NAME2                                                       ; 2nd line(STYPE=DB)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [DIM1], [DIM2]                                                         ; 2nd line(STYPE=USER)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       D11, D12, D13, D14, D15, D16, D17, D18                                 ; 2nd line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       AREA1, ASy1, ASz1, Ixx1, Iyy1, Izz1                                    ; 3rd line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       CyP1, CyM1, CzP1, CzM1, QyB1, QzB1, PERI_OUT1, PERI_IN1, Cy1, Cz1      ; 4th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Y11, Y12, Y13, Y14, Z11, Z12, Z13, Z14, Zyy1, Zyy2                     ; 5th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       D21, D22, D23, D24, D25, D26, D27, D28                                 ; 6th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       AREA2, ASy2, ASz2, Ixx2, Iyy2, Izz2                                    ; 7th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       CyP2, CyM2, CzP2, CzM2, QyB2, QzB2, PERI_OUT2, PERI_IN2, Cy2, Cz2      ; 8th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Y21, Y22, Y23, Y24, Z21, Z22, Z23, Z24, Zyy2, Zzz2                     ; 9th line(STYPE=VALUE)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       OPT1, OPT2, [JOINT]                                                    ; 2nd line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       ELAST, DEN, POIS, POIC                                                 ; 2nd line(STYPE=PSC-CMPW)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bSHEARCHK, [SCHK-I], [SCHK-J], [WT-I], [WT-J], WI, WJ, bSYM, bSIDEHOLE ; 3rd line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bSHEARCHK, bSYM, bHUNCH, [CMPWEB-I], [CMPWEB-J]                        ; 3rd line(STYPE=PSC-CMPW)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bUSERDEFMESHSIZE, MESHSIZE, bUSERINPSTIFF, [STIFF-I], [STIFF-J]        ; 4th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]-i                                                             ; 5th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]-i                                                             ; 6th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]-i                                                             ; 7th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]-i                                                             ; 8th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]-j                                                             ; 9th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]-j                                                             ; 10th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]-j                                                             ; 11th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]-j                                                             ; 12th line(STYPE=PSC)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       GN, CTC, Bc, Tc, Hh, EsEc, DsDc, Ps, Pc, bMULTI, EsEc-L, EsEc-S        ; 2nd line(STYPE=CMP-B/I)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW_i, Hw_i, tw_i, B_i, Bf1_i, tf1_i, B2_i, Bf2_i, tf2_i                ; 3rd line(STYPE=CMP-B/I)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW_j, Hw_j, tw_j, B_j, Bf1_j, tf1_j, B2_j, Bf2_j, tf2_j                ; 4th line(STYPE=CMP-B/I)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       N1, N2, Hr, Hr2, tr1, tr2                                              ; 5th line(STYPE=CMP-B)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       GN, CTC, Bc, Tc, Hh, EgdEsb, DgdDsb, Pgd, Psb, bSYM, SW_i, SW_j        ; 2nd line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       OPT1, OPT2, [JOINT]                                                    ; 3rd line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]-i                                                             ; 4th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]-i                                                             ; 5th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]-i                                                             ; 6th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]-i                                                             ; 7th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]-j                                                             ; 8th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]-j                                                             ; 9th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]-j                                                             ; 10th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]-j                                                             ; 11th line(STYPE=CMP-CI/CT)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, STYPE1, STYPE2                             ; 1st line - CONSTRUCT");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SHAPE, ...(same with other type data from shape)                       ; Before (STYPE1)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SHAPE, ...(same with other type data from shape)                       ; After  (STYPE2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE                                      ; 1st line - COMPOSITE-SB");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Hw, tw, B, Bf1, tf1, B2, Bf2, tf2                                      ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       N1, N2, Hr, Hr2, tr1, tr2                                              ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW, GN, CTC, Bc, Tc, Hh, EsEc, DsDc, Ps, Pc, bMulti, Elong, Esh        ; 4th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE                                      ; 1st line - COMPOSITE-SI");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       Hw, tw, B, tf1, B2, tf2                                                ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW, GN, CTC, Bc, Tc, Hh, EsEc, DsDc, Ps, Pc, bMulti, Elong, Esh        ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE                                      ; 1st line - COMPOSITE-CI/CT");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       OPT1, OPT2, [JOINT]                                                    ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]                                                               ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]                                                               ; 4th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]                                                               ; 5th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]                                                               ; 6th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       SW, GN, CTC, Bc, Tc, Hh, EgdEsb, DgdDsb, Pgd, Psb                      ; 7th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iSEC, TYPE, SNAME, [OFFSET], bSD, SHAPE                                      ; 1st line - PSC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       OPT1, OPT2, [JOINT]                                                    ; 2nd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bSHEARCHK, [SCHK], [WT], WIDTH, bSYM, bSIDEHOLE                        ; 3rd line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       bUSERDEFMESHSIZE, MESHSIZE, bUSERINPSTIFF, [STIFF]                     ; 4th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-A]                                                               ; 5th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-B]                                                               ; 6th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-C]                                                               ; 7th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";       [SIZE-D]                                                               ; 8th line");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA1] : 1, DB, NAME or 2, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA2] : CCSHAPE or iCEL or iN1, iN2");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SRC]  : 1, DB, NAME1, NAME2 or 2, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, iN1, iN2");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DIM1], [DIM2] : D1, D2, D3, D4, D5, D6, D7, D8");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [OFFSET] : OFFSET, iCENT, iREF, iHORZ, HUSER, iVERT, VUSER");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [OFFSET2]: OFFSET, iCENT, iREF, iHORZ, HUSERI, HUSERJ, iVERT, VUSERI, VUSERJ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [JOINT]  :  8(1CELL, 2CELL), 13(3CELL),  9(PSCM),  8(PSCH), 9(PSCT),  2(PSCB), 0(nCELL),  2(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SIZE-A] :  6(1CELL, 2CELL), 10(3CELL), 10(PSCM),  6(PSCH), 8(PSCT), 10(PSCB), 5(nCELL), 11(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SIZE-B] :  6(1CELL, 2CELL), 12(3CELL),  6(PSCM),  6(PSCH), 8(PSCT),  6(PSCB), 8(nCELL), 18(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SIZE-C] : 10(1CELL, 2CELL), 13(3CELL),  9(PSCM), 10(PSCH), 7(PSCT),  8(PSCB), 0(nCELL), 11(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SIZE-D] :  8(1CELL, 2CELL), 13(3CELL),  6(PSCM),  7(PSCH), 8(PSCT),  5(PSCB), 0(nCELL), 18(nCEL2)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [STIFF]  : AREA, ASy, ASz, Ixx, Iyy, Izz");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [SCHK]   : bAUTO_Z1, Z1, bAUTO_Z3, Z3");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [WT]     : bAUTO_TOR, TOR, bAUTO_SHR1, SHR1, bAUTO_SHR2, SHR2, bAUTO_SHR3, SHR3");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [CMPWEB] : EFD, LRF, A, B, H, T");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	//str=_T("1, DBUSER    , �ֹܽ���          , CC, 0, 0, 0, 0, 0, 0, YES, P  , 2, 0.048, 0.0035, 0, 0, 0, 0, 0, 0, 0, 0\n");
	//File1.WriteString(str);
	SectionCount=1;
	for(i=1;i<=D_Deviation_Per[0];i++)
	{
		for(j=1;j<=tw_Deviation_Per[0];j++)
		{
			str.Format("    %d, DBUSER    , �ֹܽ���          , CC, 0, 0, 0, 0, 0, 0, YES, P  , 2, %.3f, %.4f, 0, 0, 0, 0, 0, 0, 0, 0\n\n",SectionCount++,D_Deviation[i],tw_Deviation[j]);
			File1.WriteString(str);
		}
	}
	
	
	
	
	
	
	
	//'���ع�������
	//*********** Lines = Lines & readFile("d:\��������ģ\֧���ļ�\STLDCASE.mct")   *************
	str=_T("*STLDCASE    ; Static Load Cases");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; LCNAME, LCTYPE, DESC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   ��ϵ����, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   �������񵷻�����, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   ʩ����Ա�����ϡ��豸, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   Ԥѹ����1, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   Ԥѹ����2, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   Ԥѹ����3, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   ��һ�ν���, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   �ڶ��ν���, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   ģ�塢֧����, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   ������ʩ�����ӹ���, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   �����, D , ");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	
	
	
	
	//'һ��߽���������
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\CONSTRAINT.mct")
	str=_T("*CONSTRAINT    ; Supports");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, CONSt(Dx,Dy,Dz,Rx,Ry,Rz),GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	//Lines = Lines & "1to" & dc & ",001000,�ػ�" & vbCrLf
	//str.Format("%s  %d  , %s", "1 to" ,dc ,"001000,�ػ�");//�ﺣ��
	dc=ZhuJuGeShu_X*PaiJuGeShu_Y;
	str.Format("%s  %d  , %s", "1 to" ,dc ,"111000,�ػ�֧��");
	File1.WriteString(str);
	File1.WriteString("\n\n");
	
	str = _T("*FRAME-RLS    ; Beam End Release\n");
	File1.WriteString(str);
	str = _T("; ELEM_LIST, bVALUE, FLAG-i, Fxi, Fyi, Fzi, Mxi, Myi, Mzi        ; 1st line\n");
	File1.WriteString(str);
	str = _T(";                    FLAG-j, Fxj, Fyj, Fzj, Mxj, Myj, Mzj, GROUP ; 2nd line\n");
	File1.WriteString(str);
	HorizPoleNum=m2;//��ʾ����˼�����
	float Mx=0.0,My=0.0;//�ﺣ���޸�
	((CEdit*)GetDlgItem(IDC_EDIT_HENG_MX))->GetWindowText(tempstr);
	Mx=atof(tempstr);
	((CEdit*)GetDlgItem(IDC_EDIT_HENG_MY))->GetWindowText(tempstr);
	My=atof(tempstr);
	for(i=1;i<=HorizPoleNum;i++)
	{
		str.Format("     %d,  YES, 000110, 0, 0, 0, %.2f, %.2f, 0\n             000110, 0, 0, 0, %.2f, %.2f, 0, ���-����\n",i,Mx,My,Mx,My);
		File1.WriteString(str);
	}
	//m3+1 to dy
	File1.WriteString("\n");
	((CEdit*)GetDlgItem(IDC_EDIT_TRIM_MX))->GetWindowText(tempstr);
	Mx=atof(tempstr);
	((CEdit*)GetDlgItem(IDC_EDIT_TRIM_MY))->GetWindowText(tempstr);
	My=atof(tempstr);
	for(i=m3+1;i<=dy;i++)
	{
		str.Format("     %d,  YES, 000110, 0, 0, 0, %.2f, %.2f, 0\n             000110, 0, 0, 0, %.2f, %.2f, 0, ������-����\n",i,Mx,My,Mx,My);
		File1.WriteString(str);
	}

	File1.WriteString("\n");
	
	//'֧�����ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\SELFWEIGHT.mct")
	str=_T("*USE-STLD, ��ϵ����");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	str=_T("; *SELFWEIGHT, X, Y, Z, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("*SELFWEIGHT, 0, 0, -1, ֧������");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	str=_T("; End of data for load case [��ϵ����] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	
	
	
	//'�������񵷻��������ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-q5.mct")
	str=_T("*USE-STLD, �������񵷻�����");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	//	a=ZhuJuGeShu_X-1;
	//	b=PaiJuGeShu_Y-1;
	//	c=BuJuGeShu_Z-3;
	
	//qq5 = -JiaoZhuZhenDao/((b - 1) * (a + 1));
	qq5 = -JiaoZhuZhenDao/((PaiJuGeShu_Y - 2) *ZhuJuGeShu_X);
	
	for (int yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		for ( u = (BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+2+yyy*PaiJuGeShu_Y;u<=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+(PaiJuGeShu_Y-1)+yyy*PaiJuGeShu_Y;u++)
		{
			//Lines = Lines & u & ",0,0," & qq5 & ",0,0,0,��������" & vbCrLf
			str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qq5,0,0,0,"��������");
			File1.WriteString(str);
			File1.WriteString("\n");
		}
	}
	
	//'ʩ����Ա���ϻ�е���ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-q4.mct")
	str=_T("; End of data for load case [�������񵷻�����] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*USE-STLD, ʩ����Ա�����ϡ��豸");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	//	a=ZhuJuGeShu_X-1;
	//	b=PaiJuGeShu_Y-1;
	//	c=BuJuGeShu_Z-3;
	
	
	qq4 = -RenChaiJi/((PaiJuGeShu_Y-2)*ZhuJuGeShu_X);
	for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		for (u=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+2+yyy*PaiJuGeShu_Y;u<=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+(PaiJuGeShu_Y-1)+yyy*PaiJuGeShu_Y;u++)
		{
			//Lines = Lines & u & ",0,0," & qq4 & ",0,0,0,ʩ����Ա��е" & vbCrLf
			str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qq4,0,0,0,"ʩ����Ա��е");
			File1.WriteString(str);
			File1.WriteString("\n");
		}
	}
	//'��һ��Ԥѹ���ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-y1.mct")
	str=_T("; End of data for load case [ʩ����Ա�����ϡ��豸] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*USE-STLD, Ԥѹ����1");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	
	//	a=ZhuJuGeShu_X-1;
	//	b=PaiJuGeShu_Y-1;
	//	c=BuJuGeShu_Z-3;
	
	qy1 = -DiYiCiYuYa * qy / ((PaiJuGeShu_Y-6) * ZhuJuGeShu_X);
	for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		for (u=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+4+yyy*PaiJuGeShu_Y;u<=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X-2+(PaiJuGeShu_Y-1)+yyy*PaiJuGeShu_Y;u++)
		{//u = (c + 2) * dc + 4 + yyy * (b + 1) ;u<= (c + 2) * dc + b - 2 + yyy * (b + 1);u++
			//Lines = Lines & u & ",0,0," & qy1 & ",0,0,0,Ԥѹ��һ��" & vbCrLf
			str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qy1,0,0,0,"Ԥѹ��һ��");
			File1.WriteString(str);
			File1.WriteString("\n");
		}
	}
	//'�ڶ���Ԥѹ���ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-y2.mct")
	str=_T("; End of data for load case [Ԥѹ����1] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*USE-STLD, Ԥѹ����2");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	
	qy2 = -DiErCiYuYa * qy / ((PaiJuGeShu_Y-6) * ZhuJuGeShu_X);
	for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		for (u=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+4+yyy*PaiJuGeShu_Y;u<=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X-2+(PaiJuGeShu_Y-1)+yyy*PaiJuGeShu_Y;u++)
		{
			//Lines = Lines & u & ",0,0," & qy2 & ",0,0,0,Ԥѹ�ڶ���" & vbCrLf
			str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qy2,0,0,0,"Ԥѹ�ڶ���");
			File1.WriteString(str);
			File1.WriteString("\n");
		}
	}
	//'������Ԥѹ���ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-y3.mct")
	str=_T("; End of data for load case [Ԥѹ����2] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*USE-STLD, Ԥѹ����3");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	qy3 = -DiSanCiYuYa * qy / ((PaiJuGeShu_Y-6) * ZhuJuGeShu_X);
	for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		for (u=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+4+yyy*PaiJuGeShu_Y;u<=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X-2+(PaiJuGeShu_Y-1)+yyy*PaiJuGeShu_Y;u++)
		{
			//Lines = Lines & u & ",0,0," & qy3 & ",0,0,0,Ԥѹ������" & vbCrLf
			str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qy3,0,0,0,"Ԥѹ������");
			File1.WriteString(str);
			File1.WriteString("\n");
		}
	}
	//'��һ�ν������ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-j1.mct")
	str=_T("; End of data for load case [Ԥѹ����3] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*USE-STLD, ��һ�ν���");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	
	qj1 = -DiYiCiJiaoZhu * GangJinHunNingTu / ((PaiJuGeShu_Y-6) * ZhuJuGeShu_X);
	for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		for (u=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+4+yyy*PaiJuGeShu_Y;u<=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X-2+(PaiJuGeShu_Y-1)+yyy*PaiJuGeShu_Y;u++)
		{
			//Lines = Lines & u & ",0,0," & qj1 & ",0,0,0,������һ��" & vbCrLf
			str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qj1,0,0,0,"������һ��");
			File1.WriteString(str);
			File1.WriteString("\n");
		}
	}
	
	//'�ڶ��ν������ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-j2.mct")
	str=_T("; End of data for load case [��һ�ν���] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*USE-STLD, �ڶ��ν���");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	
	qj2 = -DiErCiJiaoZhu * GangJinHunNingTu / ((PaiJuGeShu_Y-6) * ZhuJuGeShu_X);
	for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		for (u=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+4+yyy*PaiJuGeShu_Y;u<=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X-2+(PaiJuGeShu_Y-1)+yyy*PaiJuGeShu_Y;u++)
		{
			//Lines = Lines & u & ",0,0," & qj2 & ",0,0,0,�����ڶ���" & vbCrLf
			str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qj2,0,0,0,"�����ڶ���");
			File1.WriteString(str);
			File1.WriteString("\n");
		}
	}
	
	//Print #2, Lines
	//Lines = ""
	
	//'ģ��֧�������ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-q2.mct")
	str=_T("; End of data for load case [�ڶ��ν���] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*USE-STLD, ģ�塢֧����");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	
	
	qq2 = -MoBanFangLeng / ((PaiJuGeShu_Y-2) * ZhuJuGeShu_X);
	for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		for (u=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+2+yyy*PaiJuGeShu_Y;u<=(BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X+(PaiJuGeShu_Y-1)+yyy*PaiJuGeShu_Y;u++)
		{
			//Lines = Lines & u & ",0,0," & qq2 & ",0,0,0,ģ�巽���" & vbCrLf 
			str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qq2,0,0,0,"ģ�巽���");
			File1.WriteString(str);
			File1.WriteString("\n");
		}
	}
	//'���ӹ����Ⱥ��ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-q3.mct")
	str=_T("; End of data for load case [ģ�塢֧����] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*USE-STLD, ������ʩ�����ӹ���");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	
	qq3 = -FuJiaGouJian / (2*ZhuJuGeShu_X);
	for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		u = (BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X + 1 + yyy * PaiJuGeShu_Y;
		//Lines = Lines & u & ",0,0," & qq3 & ",0,0,0,���ӹ���" & vbCrLf
		str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qq3,0,0,0,"���ӹ���");
		File1.WriteString(str);
		File1.WriteString("\n");
	}
	
	for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
	{
		u = (BuJuGeShu_Z-1)*PaiJuGeShu_Y*ZhuJuGeShu_X + PaiJuGeShu_Y + yyy * PaiJuGeShu_Y;
		//Lines = Lines & u & ",0,0," & qq3 & ",0,0,0,���ӹ���" & vbCrLf
		str.Format("%d , %d , %d , %f , %d , %d , %d , %s",u,0,0,qq3,0,0,0,"���ӹ���");
		File1.WriteString(str);
		File1.WriteString("\n");
	}
	
	//'����ض���
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\USE-STLD-f.mct")
	str=_T("; End of data for load case [������ʩ�����ӹ���] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*USE-STLD, �����");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*CONLOAD    ; Nodal Loads");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NODE_LIST, FX, FY, FZ, MX, MY, MZ, GROUP");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	
	//	a=ZhuJuGeShu_X-1;
	//	b=PaiJuGeShu_Y-1;
	//	c=BuJuGeShu_Z-3;
	
	
	qq6 = FengHeZai / (3 * ZhuJuGeShu_X);
	for (int xxx = 0 ;xxx<= 2;xxx++)
	{
		for (yyy = 0 ;yyy<ZhuJuGeShu_X;yyy++)
		{
			u = (BuJuGeShu_Z-3)*ZhuJuGeShu_X*PaiJuGeShu_Y + 1 + yyy * PaiJuGeShu_Y + ZhuJuGeShu_X*PaiJuGeShu_Y * xxx;
			//Lines = Lines & u & ",0," & qq6 & ",0,0,0,0,�����" & vbCrLf 
			str.Format("%d , %d , %f , %d , %d , %d , %d , %s",u,0,qq6,0,0,0,0,"�����");
			File1.WriteString(str);
			File1.WriteString("\n");
		}
	}
	//'�������
	//Lines = Lines & readFile("d:\��������ģ\֧���ļ�\LOADCOMB.mct")
	str=_T("; End of data for load case [�����] -------------------------");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	File1.WriteString("\n");
	str=_T("*LOADCOMB    ; Combinations");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; NAME=NAME, KIND, ACTIVE, bES, iTYPE, DESC, iSERV-TYPE, nLCOMTYPE   ; line 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";      ANAL1, LCNAME1, FACT1, ...                                    ; from line 2");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   NAME=��һ��Ԥѹ, GEN, ACTIVE, 0, 0, , 0, 0");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ��ϵ����, 1, ST, Ԥѹ����1, 1, ST, ģ�塢֧����, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ������ʩ�����ӹ���, 1, ST, �����, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   NAME=�ڶ���Ԥѹ, GEN, ACTIVE, 0, 0, , 0, 0");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ��ϵ����, 1, ST, Ԥѹ����1, 1, ST, Ԥѹ����2, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ģ�塢֧����, 1, ST, ������ʩ�����ӹ���, 1, ST, �����, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   NAME=������Ԥѹ, GEN, ACTIVE, 0, 0, , 0, 0");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ��ϵ����, 1, ST, Ԥѹ����1, 1, ST, Ԥѹ����2, 1, ST, Ԥѹ����3, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ģ�塢֧����, 1, ST, ������ʩ�����ӹ���, 1, ST, �����, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   NAME=��һ�ν���, GEN, ACTIVE, 0, 0, , 0, 0");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ��ϵ����, 1, ST, ��һ�ν���, 1, ST, �������񵷻�����, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ʩ����Ա�����ϡ��豸, 1, ST, ģ�塢֧����, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ������ʩ�����ӹ���, 1, ST, �����, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("   NAME=�ڶ��ν���, GEN, ACTIVE, 0, 0, , 0, 0");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ��ϵ����, 1, ST, ��һ�ν���, 1, ST, �ڶ��ν���, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, �������񵷻�����, 1, ST, ʩ����Ա�����ϡ��豸, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("        ST, ģ�塢֧����, 1, ST, ������ʩ�����ӹ���, 1, ST, �����, 1");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	
	str=_T("*LC-COLOR    ; Diagram Color for Load Case");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; ANAL, LCNAME, iR1(ALL), iG1(ALL), iB1(ALL), iR2(MIN), iG2(MIN), iB2(MIN), iR3(MAX), iG2(MAX), iB2(MAX)");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, Ԥѹ����1, 0, 192, 192, 0, 128, 57, 255, 255, 87");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, Ԥѹ����2, 163, 255, 160, 210, 210, 210, 0, 128, 192");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, ��ϵ����, 160, 192, 255, 148, 87, 255, 0, 192, 128");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" CB, ��һ��Ԥѹ, 192, 192, 0, 0, 192, 192, 192, 192, 192");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" CB, �ڶ���Ԥѹ, 78, 0, 255, 0, 157, 192, 160, 255, 255");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" CB, ������Ԥѹ, 192, 0, 128, 192, 0, 128, 93, 255, 87");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, Ԥѹ����3, 93, 255, 87, 0, 128, 192, 0, 192, 192");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, ģ�塢֧����, 255, 160, 255, 146, 0, 255, 163, 255, 160");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, �������񵷻�����, 0, 192, 128, 0, 128, 192, 0, 192, 128");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, ʩ����Ա�����ϡ��豸, 148, 87, 255, 192, 128, 0, 192, 128, 0");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" CB, ��һ�ν���, 255, 160, 255, 210, 210, 210, 255, 0, 128");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, ��һ�ν���, 163, 160, 255, 93, 255, 87, 192, 192, 192");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, �ڶ��ν���, 192, 0, 192, 0, 128, 255, 212, 160, 255");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, ������ʩ�����ӹ���, 0, 128, 57, 0, 192, 128, 0, 192, 128");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" CB, �ڶ��ν���, 192, 72, 0, 148, 87, 255, 192, 0, 192");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(" ST, �����, 255, 128, 0, 192, 0, 192, 85, 0, 192");
	File1.WriteString(str);
	File1.WriteString("\n");
	File1.WriteString("\n");
	
	
	str=_T("*DGN-MATL    ; Modify Steel(Concrete) Material");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iMAT, TYPE, MNAME, [DATA1]                                    ; STEEL");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iMAT, TYPE, MNAME, [DATA2], [R-DATA], FCI, bSERV, SHORT, LONG ; CONC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iMAT, TYPE, MNAME, [DATA3], [DATA2], [R-DATA]                 ; SRC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; iMAT, TYPE, MNAME, [DATA5]                                    ; STEEL(None) & KSCE-ASD05");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA1] : 1, DB, CODE, NAME or 2, ELAST, POISN, FU, FY1, FY2, FY3, FY4");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";           FY5, FY6, AFT, AFT2, AFT3, FY, AFV, AFV2, AFV3");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA2] : 1, DB, CODE, NAME or 2, FC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA3] : 1, DB, CODE, NAME or 2, ELAST, FU, FY1, FY2, FY3, FY4");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";              FY5, FY6, AFT, AFT2, AFT3, FY, AFV, AFV2, AFV3");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA4] : 1, DB, CODE, NAME or 2, FC");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [DATA5] : 3, ELAST, POISN, AL1, AL2, AL3, AL4, AL5, AL6, AL7, AL8, AL9, AL10");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T(";              MIN1, MIN2, MIN3");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("; [R-DATA]: RBCODE, RBMAIN, RBSUB, FY(R), FYS");
	File1.WriteString(str);
	File1.WriteString("\n");
	str=_T("    1, STEEL, Q235              , 1, GB03(S)    ,            ,Q235          ");
	File1.WriteString(str);
	File1.WriteString("\n");
	
	//Print #2, Lines
	//Lines = ""
	
	//End Sub
	
	
	num=1;
	
	File1.Close();
	AfxMessageBox("success");
	return;
	
	//AfxMessageBox("�����ɹ���");
	
}

void CSet::init()
{
	int q;
	for(q=0;q<10;q++)
	{
		PaiJuDealSave[q]=0;
	}
	for(q=0;q<10;q++)
	{
		PaiJuCountSave[q]=0;
	}
	for(q=0;q<10;q++)
	{
		PaiJuDataSave[q]=0;
	}
	
	
}

BOOL CSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitVal();
	//m_Control_BuJu_Z.enablein
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//m_Control_ZhuJu_X
	//m_button_Output.SetSkin(IDB_PUTONG_WAICENG,IDB_PUTONG_WAICENG,IDB_PUTONG_WAICENG,IDB_MASK_WAICENG,0,IDB_MASK_WAICENG,0,0,0);
	//m_button_Clear.SetSkin(IDB_PUTONG_WAICENG,IDB_PUTONG_WAICENG,IDB_PUTONG_WAICENG,IDB_MASK_WAICENG,0,IDB_MASK_WAICENG,0,0,0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSet::OnClear() 
{
    BuJuGeShu_Z=0;
	ZhuJuGeShu_X=0;
	PaiJuGeShu_Y=0;
	init();
	
   	m_ZhuJuX.Empty();
	m_PaiJu_Y.Empty();
	m_BujuZ.Empty();
	m_DingCengXuanBi.Empty();
	m_SaoDiGanGaoDu.Empty();
	m_GangJinHunNingTu.Empty();
	m_MoBanFangLeng.Empty();
	m_FuJiaGouJian.Empty();
	m_RenChaiJi.Empty();
	m_JiaoZhuZhenDao.Empty();
	m_FengHeZai.Empty();
    m_DiYiCiYuYa.Empty();
	m_DiErCiYuYa.Empty();
	m_DiSanCiYuYa.Empty();
	m_DiYiCiJiaoZhu.Empty();
	m_DiErCiJiaoZhu.Empty();
	
	
	
	m_Control_ZhuJu_X.SetCurSel(-1);
	m_Control_BuJu_Z.SetCurSel(-1);
	Sort=0;
	PaiJuCount=0;
	ZhuJuGeShu_X=0;
	BuJuGeShu_Z=0;
	PaiJuGeShu_Y=0;
	NodeZongShu=0;
	Length_X=0;
	Length_Y=0;
	Length_Z=0;
	
	
	ini_GangJinHunNingTu=0.0;
	ini_MoBanFangLeng=0.0;
	ini_FuJiaGouJian=0.0;
	ini_RenChaiJi=0.0;
	ini_JiaoZhuZhenDao=0.0;
	ini_FengHeZai=0.0;
	
	
	//************************�޸�VB�����趨�ı���************************//
	a=0;
	c=0;;
	b=0;
	dy=1;               //��Ԫ���
	dc=0      ;            //����ڵ���
	qd=  0      ;           //��Ԫǰ�ڵ�
	zd=  0      ;           //��Ԫ��ڵ�
	
	//************************�޸�VB����б��Ԫ�趨�ı���****************************//
	
	J1=1;
	j2=1;
	i1=1;
	i2=1;
	is1=0;
	s1=1;
	s2=1;
	k1=0;
	k2=0;
	k3=0;
	k4=0;
	
	//************************ѭ�������趨*************************//
	xx=0;     //רҵѭ������
	yy=0;     //רҵѭ������
	zz=0;     //רҵѭ������
	rr=0; 
	tt=0;
	kk=0;
	yj1=0;
	jy1=0;
	hh=0;
	ee=0;
	ff=0;
	cc=0;
	xi1=0;
	
	m1=0;
	m2=0;
	m3=0;
	u=0;
	qy=0;
	
	
	
	UpdateData(FALSE);
	
}

void CSet::OnButtonInputexcel() 
{
	CFileDialog file(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("EXCEL�ļ�t(*.xls;*.xlsx)|*.xls;*.xlsx||"),AfxGetMainWnd());
	if(file.DoModal()!=IDOK)
	{   
		AfxMessageBox("ѡ�񴰿�δ��");
		return;
	}
	CString strFile=file.GetPathName();
	m_Path.SetWindowText(strFile);
	int i=0,j=0,k=0;
	CString tempstr = "";
	vector < CString > CellsVal(20);
	CellsVal.resize(20);
	//CellsVal[0]="123";
	//memset(CellsVal,0,sizeof(CellsVal)/sizeof(CellsVal[0][0]));
	//GetRangeVal(&strFile,NULL,"J3","J20",&CellsVal);
	for(i=0;i<20;i++)
	{
		tempstr = tempstr+CellsVal[i]+"||";
	}
	//AfxMessageBox(tempstr);
	//return;
	_ApplicationE app;
	_Workbook book;
	_Worksheet sheet;
	Workbooks books;
	Worksheets sheets;
	Range range;
	LPDISPATCH lpDisp;
	COleVariant vResult;
	COleVariant covTrue((short)TRUE);
	COleVariant covFalse((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);	
	//����Excel������(����Excel)
	if(!app.CreateDispatch("Excel.Application"))
	{
		AfxMessageBox("�޷�����Excel������!");
		return;
	}
	app.SetVisible(FALSE);          //ʹExcel���ɼ�	
	books.AttachDispatch(app.GetWorkbooks());
	//CString strFile = "E:\\Desktop\\����ԪӦ��0611.xlsx";
	lpDisp = books.Open(strFile, 
		covOptional, covFalse, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional);
	
	//�õ�Workbook
	book.AttachDispatch(lpDisp);
	//CString bookname = book.GetName();
	
	//�õ�Worksheets
	//CString tempstr = "����ԪӦ��";
	//sheets.Select(COleVariant(tempstr));
	sheets.AttachDispatch(book.GetWorksheets());//
	//CString sheetname = "";
	for(i=0;;i++)
	{
		lpDisp=sheets.GetItem(COleVariant(short(i+1)));//book.GetActiveSheet();
		sheet.AttachDispatch(lpDisp);
		if(sheet.GetName()=="Sheet1")
			break;	
	}
	//sheetname.Format("sheet num = %d",i);
	//AfxMessageBox(sheetname);
	
	int SheetNum = i;
	int m_ValCount[8];
	memset(m_ValCount,0,sizeof(m_ValCount)/sizeof(m_ValCount[0])*sizeof(int));
	vector < vector < CString > > m_GetCVal;
	vector < vector < CString > > m_GetDVal;
	vector < vector < CString > > m_GetHVal;
	vector < vector < CString > > m_GetJVal;
	/*	vector < CString > m_GetCVal0;
	vector < CString > m_GetDVal0;
	vector < CString > m_GetHVal0;
	vector < CString > GetIVal0;
	vector < CString > m_GetJVal0;*/
	GetCVal.clear();
	GetDVal.clear();
	GetHVal.clear();
	GetJVal.clear();
	GetCVal.resize(20);
	GetDVal.resize(20);
	GetHVal.resize(20);
	GetJVal.resize(20);
	m_GetCVal.clear();
	m_GetDVal.clear();
	m_GetHVal.clear();
	m_GetJVal.clear();
	m_GetCVal.resize(SheetNum);
	m_GetDVal.resize(SheetNum);
	m_GetHVal.resize(SheetNum);
	m_GetJVal.resize(SheetNum);
	for(i=0;i<SheetNum;i++)
	{
		m_GetCVal[i].resize(20);
	}
	for(i=0;i<SheetNum;i++)
	{
		m_GetDVal[i].resize(20);
	}
	for(i=0;i<SheetNum;i++)
	{
		m_GetHVal[i].resize(20);
	}
	for(i=0;i<SheetNum;i++)
	{
		m_GetJVal[i].resize(20);
	}
	Range usedRange;
	long RowNum=0;
	long ColNum=0;
	CString EndCellCode = "";
	VARIANT key1; // these lines set up first arg (key1) to sort
	Range iRange;
	CString tempSCell = "";
	CString tempECell = "";
	VARIANT varRead;
	COleSafeArray olesaRead;
	CString minJcodeCVal = "";
	CString maxJcodeCVal = "";
	int SRow = 0;
	float tempJVal=0.0;
	VARIANT TempvarRead;
	//�õ���ǰ��Ծsheet
	//����е�Ԫ�������ڱ༭״̬�У��˲������ܷ��أ���һֱ�ȴ�
	SetProcess(0);
	for(i=0;i<SheetNum;i++)
	{
		lpDisp=sheets.GetItem(COleVariant(short(i+1)));//book.GetActiveSheet();
		sheet.AttachDispatch(lpDisp);
		//CString sheetname = sheet.GetName();
		
		//��ȡ�Ѿ�ʹ���������Ϣ�������Ѿ�ʹ�õ���������������ʼ�С���ʼ��
		usedRange.AttachDispatch(sheet.GetUsedRange());
		range.AttachDispatch(usedRange.GetRows());
		RowNum=range.GetCount();                   //�Ѿ�ʹ�õ�����
		range.ReleaseDispatch();
		range.AttachDispatch(usedRange.GetColumns());	
		ColNum=range.GetCount()-1;               //��ȡ��Ч����Ŀ����ȡ����ܱ�ʵ�ʶ�1
		EndCellCode.Format("%s%d",TranslateColName(ColNum),RowNum);
		
		V_VT(&key1) = VT_DISPATCH;                           // ����ʱ���ؼ��ֵ�vt����ΪVT_DISPATCH
		
		V_DISPATCH(&key1) = sheet.GetRange(COleVariant("J1"),COleVariant("J1"));   // ���ð��ĸ��ؼ��ֽ������� ѡ��Ԫ��Ϊ�������У����У�Ϊ���ؼ��ֽ�������	
		//range=sheet.GetRange(COleVariant(L"A1"),COleVariant(CellName));
		if(i==0)// ѡ�����Щ�����ڵĵ�Ԫ���������
		{
			iRange = sheet.GetRange(COleVariant("C3"),COleVariant(EndCellCode));
			tempSCell.Format("C3");
			tempECell.Format("C4");
		}
		else
		{
			iRange = sheet.GetRange(COleVariant("C2"),COleVariant(EndCellCode));
			tempSCell.Format("C2");
			tempECell.Format("C3");
		}
		iRange.Sort(key1, xlAscending, vOpt, vOpt, xlAscending, vOpt,xlAscending,
			xlNoHeader,vOpt,xlIgnoreCase,xlTopToBottom,xlPinYin,0,0,0); //�������� �ޱ���ʱһ��Ҫ����ΪxlNoHeader  ����������
		
		////////////////////////////////////////////////////////////////////////////
		lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
		iRange.AttachDispatch(lpDisp);
		olesaRead.Clear();
		varRead = iRange.GetValue2();
		olesaRead.Attach(varRead);
		GetValFromArry(&olesaRead,&CellsVal);
		olesaRead.Detach();
		minJcodeCVal = CellsVal[0];
		//AfxMessageBox(minJcodeCVal);
		
		
		tempSCell.Format("C%d",RowNum);
		tempECell.Format("C%d",RowNum+1);
		lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
		iRange.AttachDispatch(lpDisp);
		olesaRead.Clear();
		varRead = iRange.GetValue2();
		olesaRead.Attach(varRead);
		GetValFromArry(&olesaRead,&CellsVal);
		maxJcodeCVal = CellsVal[0];
		//AfxMessageBox(maxJcodeCVal);
		V_DISPATCH(&key1) = sheet.GetRange(COleVariant("C1"),COleVariant("C1"));   // ���ð��ĸ��ؼ��ֽ������� ѡ��Ԫ��Ϊ�������У����У�Ϊ���ؼ��ֽ�������	
		if(i==0)
			lpDisp = sheet.GetRange(COleVariant("C3"), COleVariant(EndCellCode));
		else
			lpDisp = sheet.GetRange(COleVariant("C2"), COleVariant(EndCellCode));
		iRange.AttachDispatch(lpDisp);
		iRange.Sort(key1, xlAscending, vOpt, vOpt, xlAscending, vOpt,xlAscending,
			xlNoHeader,vOpt,xlIgnoreCase,xlTopToBottom,xlPinYin,0,0,0); //�������� �ޱ���ʱһ��Ҫ����ΪxlNoHeader  ����������
		
		m_ValCount[i]=0;
		if(i==0)
			SRow=3;
		else
			SRow=2;
		for(;SRow<=RowNum;SRow++)
		{
			SetProcess(50);
			tempSCell.Format("C%d",SRow);
			tempECell.Format("C%d",SRow+1);
			lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
			iRange.AttachDispatch(lpDisp);
			VARIANT varRead = iRange.GetValue2();
			COleSafeArray olesaRead(varRead);
			GetValFromArry(&olesaRead,&CellsVal);
			olesaRead.Detach();
			if((minJcodeCVal == CellsVal[0])||(maxJcodeCVal == CellsVal[0]))
			{
				COleSafeArray olesaRead;
				m_GetCVal[i][m_ValCount[i]].Format("%d",_ttoi(CellsVal[0]));
				tempSCell.Format("D%d",SRow);
				tempECell.Format("D%d",SRow+1);
				lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
				iRange.AttachDispatch(lpDisp);
				TempvarRead = iRange.GetValue2();
				olesaRead.Attach(TempvarRead);
				GetValFromArry(&olesaRead,&CellsVal);
				olesaRead.Detach();
				m_GetDVal[i][m_ValCount[i]]=CellsVal[0];
				
				tempSCell.Format("H%d",SRow);
				tempECell.Format("H%d",SRow+1);
				lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
				iRange.AttachDispatch(lpDisp);
				TempvarRead = iRange.GetValue2();
				olesaRead.Attach(TempvarRead);
				GetValFromArry(&olesaRead,&CellsVal);
				olesaRead.Detach();
				m_GetHVal[i][m_ValCount[i]]=CellsVal[0];
				
				tempSCell.Format("J%d",SRow);
				tempECell.Format("J%d",SRow+1);
				lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
				iRange.AttachDispatch(lpDisp);
				TempvarRead = iRange.GetValue2();
				olesaRead.Attach(TempvarRead);
				GetValFromArry(&olesaRead,&CellsVal);
				olesaRead.Detach();
				tempJVal = atof(CellsVal[0]);
				m_GetJVal[i][m_ValCount[i]++].Format("%.4f",tempJVal/1000);
				
			}
			SetProcess(100);
		}
	}
	
	
	//book.Save();
    book.Close(covFalse,COleVariant(strFile),covOptional);
    books.Close();      
    app.Quit();
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	tempstr = "";
	//float FinalVal[8][20];
	CString FinalMax = m_GetJVal[0][0];
	CString FinalMin = m_GetJVal[0][0];
	for(j=0;j<SheetNum;j++)
	{
		for(i=0;i<m_ValCount[j];i++)
		{
			//FinalVal[j][i]=atof(m_GetJVal[j][i]);
			FinalMax = atof(FinalMax)>atof(m_GetJVal[j][i])?FinalMax:m_GetJVal[j][i];
			FinalMin = atof(FinalMin)<atof(m_GetJVal[j][i])?FinalMin:m_GetJVal[j][i];
			tempstr = tempstr+ m_GetCVal[j][i]+","+m_GetDVal[j][i]+","+m_GetHVal[j][i]+","+m_GetJVal[j][i]+"\n";
		}
		tempstr = tempstr+"\n";
	}
	//AfxMessageBox(tempstr);
	//tempstr.Format("max = %s,min = %s",FinalMax,FinalMin);
	//AfxMessageBox(tempstr);
	int l=0;
	ValCount = 0;
	for(j=0;j<SheetNum;j++)
	{
		for(i=0;i<m_ValCount[j];i++)
		{
			if(m_GetJVal[j][i]==FinalMax||m_GetJVal[j][i]==FinalMin)
			{
				//m_GetCVal[j][i]
				for(k=0;k<SheetNum;k++)
				{
					for(l=0;l<m_ValCount[k];l++)
					{
						if(m_GetCVal[j][i]==m_GetCVal[k][l])
						{
							GetCVal[ValCount] = m_GetCVal[k][l];
							GetDVal[ValCount] = m_GetDVal[k][l];
							GetHVal[ValCount] = m_GetHVal[k][l];
							GetJVal[ValCount++] = m_GetJVal[k][l];
						}
					}
				}
			}
		}
	}
	for(i=0;i<ValCount;i++)
	{
		//FinalVal[j][i]=atof(m_GetJVal[j][i]);
		//FinalMax = atof(FinalMax)>atof(m_GetJVal[j][i])?FinalMax:m_GetJVal[j][i];
		//FinalMin = atof(FinalMin)<atof(m_GetJVal[j][i])?FinalMin:m_GetJVal[j][i];
		//tempstr = tempstr+ GetCVal[i]+","+GetDVal[i]+","+GetHVal[i]+","+GetJVal[i]+"\n";
	}
	//AfxMessageBox(tempstr);
	AfxMessageBox("��ȡӦ�����ݳɹ���");
	return;
}



void CSet::OnRadioG1() 
{
	GradeID=5;	
	((CButton*)GetDlgItem(IDC_RADIO_G1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_G2))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_G3))->SetCheck(FALSE);
}

void CSet::OnRadioG2() 
{
	GradeID=3;	
	((CButton*)GetDlgItem(IDC_RADIO_G2))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_G1))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_G3))->SetCheck(FALSE);
}

void CSet::OnRadioG3() 
{
	GradeID=2;	
	((CButton*)GetDlgItem(IDC_RADIO_G3))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_G2))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_G1))->SetCheck(FALSE);
}

CString CSet::TranslateColName(long ColNum)
{
	char ColumnCode[3]={0};
	ColumnCode[1]=ColNum%26+'A'-1;
	if(ColNum>26)
	{
		ColumnCode[0]=ColNum/26+'A'-1;
	}
	else
	{
		ColumnCode[0]=ColumnCode[1];
		ColumnCode[1]=0;
	}
	CString result("");
	result.Format("%s",ColumnCode);
	return result;
	
}

void CSet::GetValFromArry(COleSafeArray* olesaRead, vector < CString >* Valbuf)
{
	
    VARIANT varItem;
    CString strItem;
    long index[2] = {0, 0};
    long lFirstLBound = 0;
    long lFirstUBound = 0;
    long lSecondLBound = 0;
    long lSecondUBound = 0;
	int i=0,j=0,k=0;
    lFirstLBound = 0;
    lFirstUBound = 0;
    lSecondLBound = 0;
    lSecondUBound = 0;
    olesaRead->GetLBound(1, &lFirstLBound);
    olesaRead->GetUBound(1, &lFirstUBound);
    olesaRead->GetLBound(2, &lSecondLBound);
    olesaRead->GetUBound(2, &lSecondUBound);
    memset(index, 0, 2 * sizeof(long));
	CString tempstr = "";
    for (i = lFirstLBound; i <= lFirstUBound; i++)
    {
        index[0] = i;
        for (j = lSecondLBound; j <= lSecondUBound; j++)
        {
            index[1] = j;
            olesaRead->GetElement(index, &varItem);
			
            switch (varItem.vt)
            {
            case VT_R8:
                {
                    strItem.Format(_T("%.4f"), varItem.dblVal);
					break;
                }
            case VT_R4:
                {
                    strItem.Format(_T("%.2f"), varItem.fltVal);
					break;
                }
            case VT_BSTR:
                {
                    strItem = varItem.bstrVal;
					break;
                }
            case VT_I2:
                {
                    strItem.Format(_T("%d"), (int)varItem.iVal);
					break;
                }
            case VT_I4:
                {
                    strItem.Format(_T("%ld"), (int)varItem.lVal);
					break;
                }
            default:
                {
					strItem="0";
                }
            }
			(*Valbuf)[k++] = strItem;
        }
    }
}
void CSet::OnButtonOutputword() 
{	//���ȵ���xls�ļ���ȡӦ����ֵ����Ԫ��
	int m=PaiJuGeShu_Y-1;//y��Ԫ��
	int n=ZhuJuGeShu_X-1;//x��Ԫ��
	int r=BuJuGeShu_Z-1;//z��Ԫ��
	if(PaiJuGeShu_Y==0||ZhuJuGeShu_X==0||BuJuGeShu_Z==0)
	{
		AfxMessageBox("֧�ܸ˼�xyz������һ������Ϊ0,�ṹ���������ɼ�ⷽ��\n��ȷ��ִ�й�[����MCT]");
		return;
	}
	if(ValCount==0)
	{
		if(ValCount0==0)
		{
			if(IDNO==AfxMessageBox("δ����Ӧ����λ��Excel�ļ�,�Ƿ�������ɼ�ⷽ��?",MB_YESNO))
			{
				return;
			}
		}
		else
		{
			if(IDNO==AfxMessageBox("δ����Ӧ��Excel�ļ�,�Ƿ�������ɼ�ⷽ��?",MB_YESNO))
			{
				return;
			}
		}
	}
	else
	{
		if(ValCount0==0)
		{
			if(IDNO==AfxMessageBox("δ����λ��Excel�ļ�,�Ƿ�������ɼ�ⷽ��?",MB_YESNO))
			{
				return;
			}
		}
	}
	int L1_L6[5][6];
	memset(L1_L6,0,sizeof(L1_L6)/sizeof(L1_L6[0][0])*sizeof(int));
	int i=0,j=0,k=0;
	int temp1;
	switch(GradeID)
	{
	case 5:
		{
			for(i=0;i<5;i++)
			{
				for(j=0;j<6;j++)
				{
					k=j/3;
					temp1=int(n/4.0+0.5);
					if(!k)
						L1_L6[i][j] = (m+1)*(n+1)*2+n*(m+1)*(r-1)+m*(n+1)*(r-1)+int(m/4.0*(j+1)+0.5)+m*(temp1>n?n:temp1)*i;
					else
						L1_L6[i][j] = (m+1)*(n+1)*(r-3)+n*(m+1)*(r-1)+m*(n+1)*(r-1)+int(m/4.0*(j-2)+0.5)+m*(temp1>n?n:temp1)*i;
				}
			}
		}
		break;
	case 3:
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<6;j++)
				{
					k=j/3;
					temp1=int(n/4.0+0.5);
					if(!k)
						L1_L6[i][j] = (m+1)*(n+1)*2+n*(m+1)*(r-1)+m*(n+1)*(r-1)+int(m/4.0*(j+1)+0.5)+m*(temp1>n?n:temp1)*i;
					else
						L1_L6[i][j] = (m+1)*(n+1)*(r-3)+n*(m+1)*(r-1)+m*(n+1)*(r-1)+int(m/4.0*(j-2)+0.5)+m*(temp1>n?n:temp1)*i;
				}
			}		 
		}
		break;
	case 2:
		{
			for(i=1;i<3;i++)
			{
				for(j=0;j<6;j++)
				{
					k=j/3;
					temp1=int(n/4.0+0.5);
					if(!k)
						L1_L6[i][j] = (m+1)*(n+1)*2+n*(m+1)*(r-1)+m*(n+1)*(r-1)+int(m/4.0*(j+1)+0.5)+m*(temp1>n?n:temp1)*i;
					else
						L1_L6[i][j] = (m+1)*(n+1)*(r-3)+n*(m+1)*(r-1)+m*(n+1)*(r-1)+int(m/4.0*(j-2)+0.5)+m*(temp1>n?n:temp1)*i;
				}
			}	 
		}
		break;
	default:break;
	}
	
	int L1_L3[2][3];
	memset(L1_L3,0,sizeof(L1_L3)/sizeof(L1_L3[0][0])*sizeof(int));
	for(i=0;i<2;i++)
	{
		for(j=0;j<3;j++)
		{
			temp1=int(n/2.0*j+0.5);
			if(temp1==0)
				temp1=1;
			if(i==0)
				L1_L3[i][j]=m*(n+1)*(r-1)+n*(m+1)*(r-2)+(temp1>n?n:temp1);
			else
				L1_L3[i][j]=m*(n+1)*(r-1)+n*(m+1)*(r-1)-n+(temp1>n?n:temp1);
		}
	}
	
	CFileDialog dlg(FALSE,NULL,"*.doc",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.doc",NULL);
	dlg.m_ofn.lpstrTitle = _T("������..."); 
	int rc= dlg.DoModal();
	if(rc != IDOK)
    {
		if(rc==IDCANCEL)
		{
			//m_Word.CloseApp();
			return;
		}
		AfxMessageBox("���洰�ڴ�ʧ�ܣ�");
		return;
	}
	if(rc == IDOK)
	{
		CWordOffice m_Word;
		m_Word.Create();
		m_Word.AddParagraph("���ʽ����֧�ܼ�ⷽ��\n\n",22,TRUE,"����",1,0);
		
		m_Word.AddParagraph("1.Ӧ����㲼�÷���\n",12,TRUE,"����",0,2);
		m_Word.AddParagraph("����Midas/Civil����Ԫ����������������"
			"�������ʽ����֧��Ӧ������㲼�÷���������ʾ��\n",12,FALSE,"����",0,2);
		CString tempLastCVal ="";
		int tempCount = 0;
		for(i=0;i<ValCount;i++)
		{
			if(tempLastCVal==GetCVal[i])
				tempCount++;
			tempLastCVal=GetCVal[i];
		}
		if(ValCount>0)
		{
			ValCount=ValCount-tempCount;
			tempLastCVal=GetCVal[0];
		}
		m_Word.InsertTable(ValCount*5+1+GradeID*6*5, 5);
		m_Word.SetTableText(m_Word.m_wdTable,1,1,"���",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,2,"��Ԫ���",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,3,"����",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,4,"���ؽ׶�",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,5,"Ӧ��ֵ(MPa)",12,FALSE,"����",1);
		CString OrderNum = "";
		for(i=0,j=0;i<ValCount+GradeID*6;i++)	
		{
			OrderNum.Format("%d",i+1);
			//m_Word.SetTableText(m_Word.m_wdTable,i+2,1,OrderNum,12,FALSE,"����",1);
			m_Word.CellsMerge(m_Word.m_wdTable,i*5+2,1,i*5+6,1,OrderNum);
			m_Word.CellsMerge(m_Word.m_wdTable,i*5+2,2,i*5+6,2,"��Ԫ��");
			m_Word.CellsMerge(m_Word.m_wdTable,i*5+2,3,i*5+6,3,"x,y,z");
			m_Word.SetTableText(m_Word.m_wdTable,i*5+2,4,"��һ��Ԥѹ",12,FALSE,"����",1);
			m_Word.SetTableText(m_Word.m_wdTable,i*5+3,4,"�ڶ���Ԥѹ",12,FALSE,"����",1);
			m_Word.SetTableText(m_Word.m_wdTable,i*5+4,4,"������Ԥѹ",12,FALSE,"����",1);
			m_Word.SetTableText(m_Word.m_wdTable,i*5+5,4,"��һ�ν���",12,FALSE,"����",1);
			m_Word.SetTableText(m_Word.m_wdTable,i*5+6,4,"�ڶ��ν���",12,FALSE,"����",1);
			//continue;
			if(i<ValCount)
			{
				for(;j<ValCount+tempCount;)
				{
					if(tempLastCVal==GetCVal[j])
					{
						m_Word.SetTableText(m_Word.m_wdTable,i*5+2,2,tempLastCVal,12,FALSE,"����",1);
						m_Word.SetTableText(m_Word.m_wdTable,i*5+2,3,GetXYZ(atoi(tempLastCVal),m,n,r),12,FALSE,"����",1);
						if(GetDVal[j]=="��һ��Ԥѹ")
							m_Word.SetTableText(m_Word.m_wdTable,i*5+2,5,GetJVal[j],12,FALSE,"����",1);
						else if(GetDVal[j]=="�ڶ���Ԥѹ")
							m_Word.SetTableText(m_Word.m_wdTable,i*5+3,5,GetJVal[j],12,FALSE,"����",1);
						else if(GetDVal[j]=="������Ԥѹ")
							m_Word.SetTableText(m_Word.m_wdTable,i*5+4,5,GetJVal[j],12,FALSE,"����",1);
						else if(GetDVal[j]=="��һ�ν���")
							m_Word.SetTableText(m_Word.m_wdTable,i*5+5,5,GetJVal[j],12,FALSE,"����",1);
						else if(GetDVal[j]=="�ڶ��ν���")
							m_Word.SetTableText(m_Word.m_wdTable,i*5+6,5,GetJVal[j],12,FALSE,"����",1);
						else
						{};
						j++;
					}
					else
					{
						tempLastCVal=GetCVal[j];
						break;
					}
				}
				//m_Word.SetTableText(m_Word.m_wdTable,i+2,3,"x,y,z",12,FALSE,"����",1);
				//m_Word.SetTableText(m_Word.m_wdTable,i+2,4,GetDVal[i],12,FALSE,"����",1);
				//m_Word.SetTableText(m_Word.m_wdTable,i+2,5,GetJVal[i],12,FALSE,"����",1);
			}
			else
			{
				OrderNum.Format("%d",L1_L6[(i-ValCount)/6][(i-ValCount)%6]);
				m_Word.SetTableText(m_Word.m_wdTable,i*5+2,2,OrderNum,12,FALSE,"����",1);
				m_Word.SetTableText(m_Word.m_wdTable,i*5+2,3,GetXYZ(atoi(OrderNum),m,n,r),12,FALSE,"����",1);
			}
		}
		m_Word.SetColWidth(m_Word.m_wdTable,1,8.5);
		m_Word.SetColWidth(m_Word.m_wdTable,2,12.9);
		m_Word.SetColWidth(m_Word.m_wdTable,3,12.9);
		m_Word.SetColWidth(m_Word.m_wdTable,4,15.2);
		
		tempLastCVal ="";
		tempCount = 0;
		for(i=0;i<ValCount0;i++)
		{
			if(tempLastCVal==GetCVal0[i])
				tempCount++;
			tempLastCVal=GetCVal0[i];
		}
		if(ValCount0>0)
		{
			ValCount0=ValCount0-tempCount;
			tempLastCVal=GetCVal0[0];
		}
		
		m_Word.AddParagraph("2.λ�Ʋ�㲼�÷���\n",12,TRUE,"����",0,2);
		m_Word.AddParagraph("����Midas/Civil����Ԫ����������������"
			"�������ʽ����֧��Ӧ������㲼�÷���������ʾ��\n",12,FALSE,"����",0,2);
		
		m_Word.InsertTable(ValCount0*5+1+6*5, 7);
		m_Word.SetTableText(m_Word.m_wdTable,1,1,"���",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,2,"��Ԫ���",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,3,"λ��",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,4,"���ؽ׶�",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,5,"Dx(mm)",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,6,"Dy(mm)",12,FALSE,"����",1);
		m_Word.SetTableText(m_Word.m_wdTable,1,7,"Dz(mm)",12,FALSE,"����",1);
		
		for(i=0,j=0;i<ValCount0+6;i++)	
		{
			OrderNum = "";
			OrderNum.Format("%d",i+1);
			//m_Word.SetTableText(m_Word.m_wdTable,i+2,1,OrderNum,12,FALSE,"����",1);
			m_Word.CellsMerge(m_Word.m_wdTable,i*5+2,1,i*5+6,1,OrderNum);
			m_Word.CellsMerge(m_Word.m_wdTable,i*5+2,2,i*5+6,2,"��Ԫ��");
			m_Word.CellsMerge(m_Word.m_wdTable,i*5+2,3,i*5+6,3,"x,y,z");
			m_Word.SetTableText(m_Word.m_wdTable,i*5+2,4,"��һ��Ԥѹ",12,FALSE,"����",1);
			m_Word.SetTableText(m_Word.m_wdTable,i*5+3,4,"�ڶ���Ԥѹ",12,FALSE,"����",1);
			m_Word.SetTableText(m_Word.m_wdTable,i*5+4,4,"������Ԥѹ",12,FALSE,"����",1);
			m_Word.SetTableText(m_Word.m_wdTable,i*5+5,4,"��һ�ν���",12,FALSE,"����",1);
			m_Word.SetTableText(m_Word.m_wdTable,i*5+6,4,"�ڶ��ν���",12,FALSE,"����",1);
			//continue;
			if(i<ValCount0)
			{
				for(;j<ValCount0+tempCount;)
				{
					if(tempLastCVal==GetCVal0[j])
					{
						m_Word.SetTableText(m_Word.m_wdTable,i*5+2,2,tempLastCVal,12,FALSE,"����",1);
						m_Word.SetTableText(m_Word.m_wdTable,i*5+2,3,GetXYZ(atoi(tempLastCVal),m,n,r),12,FALSE,"����",1);
						if(GetDVal0[j]=="��һ��Ԥѹ")
						{
							m_Word.SetTableText(m_Word.m_wdTable,i*5+2,5,GetHVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+2,6,GetIVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+2,7,GetJVal0[j],12,FALSE,"����",1);
						}
						else if(GetDVal0[j]=="�ڶ���Ԥѹ")
						{
							m_Word.SetTableText(m_Word.m_wdTable,i*5+3,5,GetHVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+3,6,GetIVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+3,7,GetJVal0[j],12,FALSE,"����",1);
						}
						else if(GetDVal0[j]=="������Ԥѹ")
						{
							m_Word.SetTableText(m_Word.m_wdTable,i*5+4,5,GetHVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+4,6,GetIVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+4,7,GetJVal0[j],12,FALSE,"����",1);
						}
						else if(GetDVal0[j]=="��һ�ν���")
						{
							m_Word.SetTableText(m_Word.m_wdTable,i*5+5,5,GetHVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+5,6,GetIVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+5,7,GetJVal0[j],12,FALSE,"����",1);
						}
						else if(GetDVal0[j]=="�ڶ��ν���")
						{
							m_Word.SetTableText(m_Word.m_wdTable,i*5+6,5,GetHVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+6,6,GetIVal0[j],12,FALSE,"����",1);
							m_Word.SetTableText(m_Word.m_wdTable,i*5+6,7,GetJVal0[j],12,FALSE,"����",1);
						}
						else
						{};
						j++;
					}
					else
					{
						tempLastCVal=GetCVal0[j];
						break;
					}
				}
				//m_Word.SetTableText(m_Word.m_wdTable,i+2,3,"x,y,z",12,FALSE,"����",1);
				//m_Word.SetTableText(m_Word.m_wdTable,i+2,4,GetDVal[i],12,FALSE,"����",1);
				//m_Word.SetTableText(m_Word.m_wdTable,i+2,5,GetJVal[i],12,FALSE,"����",1);
			}
			else
			{
				OrderNum.Format("%d",L1_L3[(i-ValCount0)/3][(i-ValCount0)%3]);
				m_Word.SetTableText(m_Word.m_wdTable,i*5+2,2,OrderNum,12,FALSE,"����",1);
				m_Word.SetTableText(m_Word.m_wdTable,i*5+2,3,GetXYZ(atoi(OrderNum),m,n,r),12,FALSE,"����",1);
			}
		}		
		m_Word.SetColWidth(m_Word.m_wdTable,1,8.5);
		m_Word.SetColWidth(m_Word.m_wdTable,2,12.9);
		m_Word.SetColWidth(m_Word.m_wdTable,3,12.9);
		m_Word.SetColWidth(m_Word.m_wdTable,4,16.0);
		
		
		if(m_Word.SaveDocumentAs(dlg.GetPathName()))
		{
		/*			if(IDOK==AfxMessageBox("�����ɹ����Ƿ�������?",MB_YESNO))
		{
		m_Word.ShowApp();
		m_Word.OpenDocument(dlg.GetPathName());
		return;
		}*/
			AfxMessageBox("�����ɹ���");
		}
		else
			AfxMessageBox("����ʧ�ܣ�");
		m_Word.CloseApp();
	}
	
	
}

CString CSet::GetXYZ(int Num,int m,int n,int r)
{
	int x,y,z;
	CString result = "";
	if(Num<=m*(n+1)*(r-1))
	{
		x=((int)(ceil((0.0+Num)/m)))%(n+1);
		if(x==0)
			x=n+1;
		z=ceil((ceil((0.0+Num)/m))/(n+1.0));
		y=Num-((z-1)*(n+1)+x-1)*m;
		result.Format("%d,%d,%d\ny��",x,y,z);
		return result;
		
	}
	if(Num<=m*(n+1)*(r-1)+n*(m+1)*(r-1))
	{
		y=((int)(ceil(((Num-m*(n+1.0)*(r-1.0)))/n)))%(m+1);
		if(y==0)
			y=m+1;
		z=ceil((ceil(((Num-m*(n+1.0)*(r-1.0)))/n))/(m+1.0));
		x=Num-m*(n+1)*(r-1)-((z-1)*(m+1)+y-1)*n;
		result.Format("%d,%d,%d\nx��",x,y,z);
		return result;
		
	}
	else
	{
		z=ceil(((Num-m*(n+1.0)*(r-1.0)-n*(m+1)*(r-1)))/((n+1)*(m+1)));
		y=(Num-m*(n+1)*(r-1)-n*(m+1)*(r-1)-(z-1)*(m+1)*(n+1))%m;
		if(y==0)
			y=m+1;
		//ceil((ceil(((float)(Num-m*(n+1)*(r-1)))/n))/((float)(m+1)));
		x=ceil(((Num-m*(n+1.0)*(r-1.0)-n*(m+1)*(r-1)-(z-1)*(m+1)*(n+1)))/m);
		result.Format("%d,%d,%d\nz��",x,y,z);
		return result;
	}
	
}

void CSet::OnButtonInputexcel2() 
{
	CFileDialog file(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("EXCEL�ļ�t(*.xls;*.xlsx)|*.xls;*.xlsx||"),AfxGetMainWnd());
	file.m_ofn.lpstrTitle = _T("����λ���ļ�...");
	if(file.DoModal()!=IDOK)
	{   
		AfxMessageBox("ѡ�񴰿ڴ�ʧ��");
		return;
	}
	CString strFile=file.GetPathName();
	m_Path.SetWindowText(strFile);
	int i=0,j=0,k=0;
	CString tempstr = "";
	vector < CString > CellsVal(20);
	CellsVal.resize(20);
	//CellsVal[0]="123";
	//memset(CellsVal,0,sizeof(CellsVal)/sizeof(CellsVal[0][0]));
	//GetRangeVal(&strFile,NULL,"J3","J20",&CellsVal);
	for(i=0;i<20;i++)
	{
		tempstr = tempstr+CellsVal[i]+"||";
	}
	tempstr = "";
	//AfxMessageBox(tempstr);
	//return;
	_ApplicationE app;
    _Workbook book;
    _Worksheet sheet;
    Workbooks books;
    Worksheets sheets;
    Range range;
    LPDISPATCH lpDisp;
    COleVariant vResult;
    COleVariant covTrue((short)TRUE);
    COleVariant covFalse((short)FALSE);
    COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);	
    //����Excel������(����Excel)
    if(!app.CreateDispatch("Excel.Application"))
    {
        AfxMessageBox("�޷�����Excel������!");
        return;
    }
    app.SetVisible(FALSE);          //ʹExcel���ɼ�	
	books.AttachDispatch(app.GetWorkbooks());
	//CString strFile = "E:\\Desktop\\����ԪӦ��0611.xlsx";
    lpDisp = books.Open(strFile, 
        covOptional, covFalse, covOptional, covOptional, covOptional,
        covOptional, covOptional, covOptional, covOptional, covOptional,
        covOptional, covOptional, covOptional, covOptional);
	
    //�õ�Workbook
    book.AttachDispatch(lpDisp);
	//CString bookname = book.GetName();
	
    //�õ�Worksheets
	//CString tempstr = "����ԪӦ��";
	//sheets.Select(COleVariant(tempstr));
    sheets.AttachDispatch(book.GetWorksheets());//
	for(i=0;;i++)
	{
		lpDisp=sheets.GetItem(COleVariant(short(i+1)));//book.GetActiveSheet();
		sheet.AttachDispatch(lpDisp);
		if(sheet.GetName()=="Sheet1")
			break;	
	}
	
	int SheetNum = i;
	int m_ValCount0[8];
	memset(m_ValCount0,0,sizeof(m_ValCount0)/sizeof(m_ValCount0[0])*sizeof(int));
	Range usedRange;
	long RowNum=0;
	long ColNum=0;
	CString EndCellCode = "";
	VARIANT key1; // these lines set up first arg (key1) to sort
	Range iRange;
	CString tempSCell = "";
	CString tempECell = "";
	VARIANT varRead ;
	COleSafeArray olesaRead;	//�õ���ǰ��Ծsheet
	CString minHcodeCVal0;
	CString maxHcodeCVal0 ;
	CString minIcodeCVal0;
	CString maxIcodeCVal0;
	CString minJcodeCVal0;
	int SRow = 0;
	GetCVal0.clear();
	GetDVal0.clear();
	GetHVal0.clear();
	GetIVal0.clear();
	GetJVal0.clear();
	GetCVal0.resize(60);
	GetDVal0.resize(60);
	GetHVal0.resize(60);
	GetIVal0.resize(60);
	GetJVal0.resize(60);
	ValCount0=0;
	vector < vector < CString > > m_GetCVal0;
	vector < vector < CString > > m_GetDVal0;
	vector < vector < CString > > m_GetHVal0;
	vector < vector < CString > > m_GetIVal0;
	vector < vector < CString > > m_GetJVal0;
	m_GetCVal0.clear();
	m_GetDVal0.clear();
	m_GetHVal0.clear();
	m_GetIVal0.clear();
	m_GetJVal0.clear();
	m_GetCVal0.resize(SheetNum);
	m_GetDVal0.resize(SheetNum);
	m_GetHVal0.resize(SheetNum);
	m_GetIVal0.resize(SheetNum);
	m_GetJVal0.resize(SheetNum);
	for(i=0;i<SheetNum;i++)
	{
		m_GetCVal0[i].resize(40);
	}
	for(i=0;i<SheetNum;i++)
	{
		m_GetDVal0[i].resize(40);
	}
	for(i=0;i<SheetNum;i++)
	{
		m_GetHVal0[i].resize(40);
	}
	for(i=0;i<SheetNum;i++)
	{
		m_GetIVal0[i].resize(40);
	}
	for(i=0;i<SheetNum;i++)
	{
		m_GetJVal0[i].resize(40);
	}
	
	//����е�Ԫ�������ڱ༭״̬�У��˲������ܷ��أ���һֱ�ȴ�
	SetProcess(0);
	for(i=0;i<SheetNum;i++)
	{
		lpDisp=sheets.GetItem(COleVariant(short(i+1)));//book.GetActiveSheet();
		sheet.AttachDispatch(lpDisp);
		//CString sheetname = sheet.GetName();
		
		//��ȡ�Ѿ�ʹ���������Ϣ�������Ѿ�ʹ�õ���������������ʼ�С���ʼ��
		usedRange.AttachDispatch(sheet.GetUsedRange());
		range.AttachDispatch(usedRange.GetRows());
		RowNum=range.GetCount();                   //�Ѿ�ʹ�õ�����
		range.ReleaseDispatch();
		range.AttachDispatch(usedRange.GetColumns());	
		ColNum=range.GetCount()-1;               //��ȡ��Ч����Ŀ����ȡ����ܱ�ʵ�ʶ�1
		EndCellCode.Format("%s%d",TranslateColName(ColNum),RowNum);
		
		V_VT(&key1) = VT_DISPATCH;                           // ����ʱ���ؼ��ֵ�vt����ΪVT_DISPATCH
		
		V_DISPATCH(&key1) = sheet.GetRange(COleVariant("H1"),COleVariant("H1"));   // ���ð��ĸ��ؼ��ֽ������� ѡ��Ԫ��Ϊ�������У����У�Ϊ���ؼ��ֽ�������	
		//range=sheet.GetRange(COleVariant(L"A1"),COleVariant(CellName));              // ѡ�����Щ�����ڵĵ�Ԫ���������
		if(i==0)// ѡ�����Щ�����ڵĵ�Ԫ���������
		{
			iRange = sheet.GetRange(COleVariant("C3"),COleVariant(EndCellCode));
			tempSCell.Format("C3");
			tempECell.Format("C4");
		}
		else
		{
			iRange = sheet.GetRange(COleVariant("C2"),COleVariant(EndCellCode));
			tempSCell.Format("C2");
			tempECell.Format("C3");
		}
		iRange.Sort(key1, xlAscending, vOpt, vOpt, xlAscending, vOpt,xlAscending,
			xlNoHeader,vOpt,xlIgnoreCase,xlTopToBottom,xlPinYin,0,0,0); //�������� �ޱ���ʱһ��Ҫ����ΪxlNoHeader  ����������
		
		lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
		iRange.AttachDispatch(lpDisp);
		varRead = iRange.GetValue2();
		olesaRead.Attach(varRead);
		GetValFromArry(&olesaRead,&CellsVal);
		olesaRead.Detach();
		minHcodeCVal0 = CellsVal[0];
		//AfxMessageBox(minHcodeCVal0);
		
		
		tempSCell.Format("C%d",RowNum);
		tempECell.Format("C%d",RowNum+1);
		lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
		iRange.AttachDispatch(lpDisp);
		olesaRead.Clear();
		varRead = iRange.GetValue2();
		olesaRead.Attach(varRead);
		GetValFromArry(&olesaRead,&CellsVal);
		maxHcodeCVal0 = CellsVal[0];
		//AfxMessageBox(maxJcodeCVal);
		/*	V_DISPATCH(&key1) = sheet.GetRange(COleVariant("C1"),COleVariant("C1"));   // ���ð��ĸ��ؼ��ֽ������� ѡ��Ԫ��Ϊ�������У����У�Ϊ���ؼ��ֽ�������	
		lpDisp = sheet.GetRange(COleVariant("C3"), COleVariant(EndCellCode));
		iRange.AttachDispatch(lpDisp);
		iRange.Sort(key1, xlAscending, vOpt, vOpt, xlAscending, vOpt,xlAscending,
		xlNoHeader,vOpt,xlIgnoreCase,xlTopToBottom,xlPinYin,0,0,0);*/ //�������� �ޱ���ʱһ��Ҫ����ΪxlNoHeader  ����������
		/////////////////////////////////////////////////////////////////////////////////////////
		
		V_DISPATCH(&key1) = sheet.GetRange(COleVariant("I1"),COleVariant("I1"));   // ���ð��ĸ��ؼ��ֽ������� ѡ��Ԫ��Ϊ�������У����У�Ϊ���ؼ��ֽ�������	
		//range=sheet.GetRange(COleVariant(L"A1"),COleVariant(CellName));              // ѡ�����Щ�����ڵĵ�Ԫ���������
		if(i==0)
		{
			lpDisp = sheet.GetRange(COleVariant("C3"), COleVariant(EndCellCode));
			tempSCell.Format("C3");
			tempECell.Format("C4");
		}
		else
		{
			lpDisp = sheet.GetRange(COleVariant("C2"), COleVariant(EndCellCode));
			tempSCell.Format("C2");
			tempECell.Format("C3");
		}
		iRange.AttachDispatch(lpDisp);
		iRange.Sort(key1, xlAscending, vOpt, vOpt, xlAscending, vOpt,xlAscending,
			xlNoHeader,vOpt,xlIgnoreCase,xlTopToBottom,xlPinYin,0,0,0); //�������� �ޱ���ʱһ��Ҫ����ΪxlNoHeader  ����������
		
		lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
		iRange.AttachDispatch(lpDisp);
		varRead = iRange.GetValue2();
		olesaRead.Attach(varRead);
		GetValFromArry(&olesaRead,&CellsVal);
		olesaRead.Detach();
		minIcodeCVal0 = CellsVal[0];
		//AfxMessageBox(minJcodeCVal);
		
		
		tempSCell.Format("C%d",RowNum);
		tempECell.Format("C%d",RowNum+1);
		lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
		iRange.AttachDispatch(lpDisp);
		olesaRead.Clear();
		varRead = iRange.GetValue2();
		olesaRead.Attach(varRead);
		GetValFromArry(&olesaRead,&CellsVal);
		maxIcodeCVal0 = CellsVal[0];
		//AfxMessageBox(maxJcodeCVal);
		/*	V_DISPATCH(&key1) = sheet.GetRange(COleVariant("C1"),COleVariant("C1"));   // ���ð��ĸ��ؼ��ֽ������� ѡ��Ԫ��Ϊ�������У����У�Ϊ���ؼ��ֽ�������	
		lpDisp = sheet.GetRange(COleVariant("C3"), COleVariant(EndCellCode));
		iRange.AttachDispatch(lpDisp);
		iRange.Sort(key1, xlAscending, vOpt, vOpt, xlAscending, vOpt,xlAscending,
		xlNoHeader,vOpt,xlIgnoreCase,xlTopToBottom,xlPinYin,0,0,0);*/ //�������� �ޱ���ʱһ��Ҫ����ΪxlNoHeader  ����������
		///////////////////////////////////////////////////////////////////////////////////
		
		V_DISPATCH(&key1) = sheet.GetRange(COleVariant("J1"),COleVariant("J1"));   // ���ð��ĸ��ؼ��ֽ������� ѡ��Ԫ��Ϊ�������У����У�Ϊ���ؼ��ֽ�������	
		//range=sheet.GetRange(COleVariant(L"A1"),COleVariant(CellName)); 
		if(i==0)// ѡ�����Щ�����ڵĵ�Ԫ���������
		{
			iRange = sheet.GetRange(COleVariant("C3"),COleVariant(EndCellCode));
			tempSCell.Format("C3");
			tempECell.Format("C4");
		}
		else
		{
			iRange = sheet.GetRange(COleVariant("C2"),COleVariant(EndCellCode));
			tempSCell.Format("C2");
			tempECell.Format("C3");
		}
		iRange.Sort(key1, xlAscending, vOpt, vOpt, xlAscending, vOpt,xlAscending,
			xlNoHeader,vOpt,xlIgnoreCase,xlTopToBottom,xlPinYin,0,0,0); //�������� �ޱ���ʱһ��Ҫ����ΪxlNoHeader  ����������
		
		lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
		iRange.AttachDispatch(lpDisp);
		varRead = iRange.GetValue2();
		olesaRead.Attach(varRead);
		GetValFromArry(&olesaRead,&CellsVal);
		olesaRead.Detach();
		minJcodeCVal0 = CellsVal[0];
		//AfxMessageBox(minJcodeCVal);
		
		
		tempSCell.Format("C%d",RowNum);
		tempECell.Format("C%d",RowNum+1);
		lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
		iRange.AttachDispatch(lpDisp);
		olesaRead.Clear();
		varRead = iRange.GetValue2();
		olesaRead.Attach(varRead);
		GetValFromArry(&olesaRead,&CellsVal);
		CString maxJcodeCVal0 = CellsVal[0];
		//AfxMessageBox(maxJcodeCVal0);
		V_DISPATCH(&key1) = sheet.GetRange(COleVariant("C1"),COleVariant("C1"));   // ���ð��ĸ��ؼ��ֽ������� ѡ��Ԫ��Ϊ�������У����У�Ϊ���ؼ��ֽ�������	
		if(i==0)
			lpDisp = sheet.GetRange(COleVariant("C3"), COleVariant(EndCellCode));
		else
			lpDisp = sheet.GetRange(COleVariant("C2"), COleVariant(EndCellCode));
		iRange.AttachDispatch(lpDisp);
		iRange.Sort(key1, xlAscending, vOpt, vOpt, xlAscending, vOpt,xlAscending,
			xlNoHeader,vOpt,xlIgnoreCase,xlTopToBottom,xlPinYin,0,0,0); //�������� �ޱ���ʱһ��Ҫ����ΪxlNoHeader  ����������
		///////////////////////////////////////////////////////////////////////////////////
		//tempstr.Format("%d",RowNum);
		//AfxMessageBox(tempstr);
		if(i==0)
			SRow = 3;
		else
			SRow = 2;
		for(SRow=3;SRow<=RowNum;SRow++)
		{
			SetProcess((i*RowNum+SRow)/(SheetNum*(RowNum+1.0))*100);
			tempSCell.Format("C%d",SRow);
			tempECell.Format("C%d",SRow+1);
			lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
			iRange.AttachDispatch(lpDisp);
			varRead = iRange.GetValue2();
			olesaRead.Attach(varRead);
			GetValFromArry(&olesaRead,&CellsVal);
			olesaRead.Detach();
			if((minHcodeCVal0 == CellsVal[0])||(maxHcodeCVal0 == CellsVal[0])||(minIcodeCVal0 == CellsVal[0])||(maxIcodeCVal0 == CellsVal[0])||(minJcodeCVal0 == CellsVal[0])||(maxJcodeCVal0 == CellsVal[0]))
			{
				m_GetCVal0[i][m_ValCount0[i]].Format("%d",atoi(CellsVal[0]));
				//AfxMessageBox(minJcodeCVal0+maxJcodeCVal0);
				//return;
				tempSCell.Format("D%d",SRow);
				tempECell.Format("D%d",SRow+1);
				lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
				iRange.AttachDispatch(lpDisp);
				varRead = iRange.GetValue2();
				olesaRead.Attach(varRead);
				GetValFromArry(&olesaRead,&CellsVal);
				olesaRead.Detach();
				m_GetDVal0[i][m_ValCount0[i]]=CellsVal[0];
				
				tempSCell.Format("H%d",SRow);
				tempECell.Format("H%d",SRow+1);
				lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
				iRange.AttachDispatch(lpDisp);
				varRead = iRange.GetValue2();
				olesaRead.Attach(varRead);
				GetValFromArry(&olesaRead,&CellsVal);
				olesaRead.Detach();
				m_GetHVal0[i][m_ValCount0[i]]=CellsVal[0];
				
				tempSCell.Format("I%d",SRow);
				tempECell.Format("I%d",SRow+1);
				lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
				iRange.AttachDispatch(lpDisp);
				varRead = iRange.GetValue2();
				olesaRead.Attach(varRead);
				GetValFromArry(&olesaRead,&CellsVal);
				olesaRead.Detach();
				m_GetIVal0[i][m_ValCount0[i]] = CellsVal[0];
				
				tempSCell.Format("J%d",SRow);
				tempECell.Format("J%d",SRow+1);
				lpDisp = sheet.GetRange(COleVariant(tempSCell), COleVariant(tempECell));
				iRange.AttachDispatch(lpDisp);
				varRead = iRange.GetValue2();
				olesaRead.Attach(varRead);
				GetValFromArry(&olesaRead,&CellsVal);
				olesaRead.Detach();
				m_GetJVal0[i][m_ValCount0[i]++] = CellsVal[0];
				
			}
		}
	}
	
	
	//book.Save();
    book.Close(covFalse,COleVariant(strFile),covOptional);
    books.Close();      
    app.Quit();
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	CString FinalHMax = m_GetHVal0[0][0];
	CString FinalIMax = m_GetIVal0[0][0];
	CString FinalJMax = m_GetJVal0[0][0];
	//double tempdouble = 0.0;
	for(j=0;j<SheetNum;j++)
	{
		for(i=0;i<m_ValCount0[j];i++)
		{
			//FinalVal[j][i]=atof(m_GetJVal[j][i]);
			FinalHMax = fabs(atof(m_GetHVal0[j][i]))>fabs(atof(FinalHMax))?m_GetHVal0[j][i]:FinalHMax;
			FinalIMax = fabs(atof(m_GetIVal0[j][i]))>fabs(atof(FinalIMax))?m_GetIVal0[j][i]:FinalIMax;
			FinalJMax = fabs(atof(m_GetJVal0[j][i]))>fabs(atof(FinalJMax))?m_GetJVal0[j][i]:FinalJMax;
			//FinalMax = atof(FinalMax)>atof(m_GetJVal[j][i])?FinalMax:m_GetJVal[j][i];
			//FinalMin = atof(FinalMin)<atof(m_GetJVal[j][i])?FinalMin:m_GetJVal[j][i];
			tempstr = tempstr+ m_GetCVal0[j][i]+","+m_GetDVal0[j][i]+","+m_GetHVal0[j][i]+","+m_GetIVal0[j][i]+","+m_GetJVal0[j][i]+"\n";
		}
		tempstr = tempstr+"\n";
	}
	//	AfxMessageBox(tempstr);
	tempstr = FinalHMax+"\n"+FinalIMax+"\n"+FinalJMax;
	//AfxMessageBox(tempstr);
	int l=0;
	ValCount0 = 0;
	for(j=0;j<SheetNum;j++)
	{
		for(i=0;i<m_ValCount0[j];i++)
		{
			if(m_GetHVal0[j][i]==FinalHMax||m_GetIVal0[j][i]==FinalIMax||m_GetJVal0[j][i]==FinalJMax)
			{
				//m_GetCVal[j][i]
				for(k=0;k<SheetNum;k++)
				{
					for(l=0;l<m_ValCount0[k];l++)
					{
						if(m_GetCVal0[j][i]==m_GetCVal0[k][l])//||m_GetIVal0[j][i]==m_GetIVal0[k][l]||m_GetJVal0[j][i]==m_GetJVal0[k][l])
						{
							//CString tempi = "";
							
							//tempi.Format("ValCount0 = %d",ValCount0);
							//AfxMessageBox(tempi);
							GetCVal0[ValCount0] = m_GetCVal0[k][l];
							GetDVal0[ValCount0] = m_GetDVal0[k][l];
							GetHVal0[ValCount0] = m_GetHVal0[k][l];
							GetIVal0[ValCount0] = m_GetHVal0[k][l];
							GetJVal0[ValCount0++] = m_GetJVal0[k][l];
						}
					}
				}
			}
		}
	}
	tempstr = "";
	for(i=0;i<ValCount0;i++)
	{
		tempstr = tempstr+ GetCVal0[i]+","+GetDVal0[i]+","+GetHVal0[i]+","+GetIVal0[i]+","+GetJVal0[i]+"\n";
	}
	//AfxMessageBox(tempstr);
	AfxMessageBox("��ȡλ�����ݳɹ���");
	
	return;
}


void CSet::OnButtonCaclu() 
{
	CWinThread *pThread=AfxBeginThread(RUNTIME_CLASS(CUIThread));
}




void CSet::SetProcess(int process)
{
	//UpdateData(TRUE);
	//Info.pctrlProgress=&m_ProgressTest;
	//����MFC�߳�
	//CProgressCtrl* lpctrlProgress=
	/*Info.pctrlProgress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	Process=process;
	UpdateData(TRUE);
	AfxBeginThread(ThreadFunc,&Info);*/
	
}

void CSet::OnChangeZhuJuX1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CSet::OnChangePaiJuY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CSet::OnButton1() 
{
	int BB,BB1,ZZ,ZZ1,PP,PP1;
    Deal_PaiJu_Y();
    Deal_ZhuJu_X();
    Deal_BuJu_Z();
	int tempBu=0;
	int tempZhu=0;
	int tempPai=0;
	CString filename="h:\\midas.txt";
	//filename=filename+".mct";
	CStdioFile File;
	File.Open(filename,CFile::modeCreate|CFile::modeReadWrite);//����ļ����Ȳ����ڵĻ�������ҪCFile::modeCreate������Ͳ���Ҫ��
	CString TxtStr="";
	float CurZVal = 0.0;
	for(BB=-1;BB<Count_Z;BB++)
	{
		if(BB==-1)
			tempBu=1;
		else
			tempBu=BuJuCountSave[BB];
		for(BB1=0;BB1<tempBu;BB1++)
		{
			if(BB==-1)
				CurZVal=0.0;
			else
				CurZVal=CurZVal+BuJuDataSave[BB];
			float CurXVal = 0.0;
			for(ZZ=-1;ZZ<Count_X;ZZ++)
			{
				if(ZZ==-1)
					tempZhu=1;
				else
					tempZhu=ZhuJuCountSave[ZZ];
				for(ZZ1=0;ZZ1<tempZhu;ZZ1++)
				{
					if(ZZ==-1)
						CurXVal=0.0;
					else
						CurXVal=CurXVal+ZhuJuDataSave[ZZ];
					float CurYVal=0.0;
					for(PP=-1;PP<Count_Y;PP++)
					{
						if(PP==-1)
							tempPai=1;
						else
							tempPai=PaiJuCountSave[PP];
						for(PP1=0;PP1<tempPai;PP1++)
						{
							if(PP==-1)
								CurYVal=0.0;
							else
								CurYVal=CurYVal+PaiJuDataSave[PP];
							TxtStr.Format("%.2f,%.2f,%.2f\n",CurXVal,CurYVal,CurZVal);
							File.WriteString(TxtStr);
						}
					}
				}
			}
		}
	}
	File.Close();
	AfxMessageBox("���");
}

void CSet::OnChangeXiaTuoChengGaoDu() 
{
	CString str; 
	UpdateData(TRUE);
	GetDlgItemText(IDE_XiaTuoChengGaoDu,str);
	XiaBuTuoChengGaoDu=atof(str);
	return;
	
}


void CSet::OnAddWaijing() 
{
	CString tempstr;
	CListCtrl* m_list=NULL;
	((CEdit*)GetDlgItem(IDE_WaiJingZhi))->GetWindowText(tempstr);
	double Val=atof(tempstr);
	((CEdit*)GetDlgItem(IDE_WaiJingBaiFenBi))->GetWindowText(tempstr);
	int Per=atoi(tempstr);
	if(Val>2*D)
	{
		AfxMessageBox("����⾶����");
		return;
	}
	if(Val<0.5*D)
	{
		AfxMessageBox("����⾶��С");
		return;
	}
	if(Val==D)
	{
		AfxMessageBox("����⾶�������׼�⾶��ͬ");
		return;
	}
	if(Per<0)
	{
		AfxMessageBox("����ʲ���Ϊ����");
		return;
	}
	m_list=(CListCtrl*)GetDlgItem(IDC_LIST_WAIJING_WUCHA);
	int i=0;
	for(i=0;i<m_list->GetItemCount();i++)
	{
		tempstr=m_list->GetItemText(i,0);
		if(atof(tempstr)==Val)
		{
			tempstr.Format("Val���%d���ظ�",i+1);
			AfxMessageBox(tempstr);
			return;
		}
	}
	if(Per>20)
	{
		tempstr.Format("����ʹ���!");
		MessageBox(tempstr,"����",MB_ICONWARNING);
		//	return;
	}
	tempstr.Format("%.4f",Val);
	m_list->InsertItem(0,"");
	m_list->SetItemText(0,0,tempstr);
	tempstr.Format("%d",Per);
	m_list->SetItemText(0,1,tempstr);
	
	
}

void CSet::OnDelWaijing() 
{
	CListCtrl* m_list=NULL;
	m_list=(CListCtrl*)GetDlgItem(IDC_LIST_WAIJING_WUCHA);
	while(m_list->GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_list->GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_list->DeleteItem(nItem);
	}
}

void CSet::OnAddBihou() 
{
	CString tempstr;
	CListCtrl* m_list=NULL;
	((CEdit*)GetDlgItem(IDE_BiHouZhi))->GetWindowText(tempstr);
	double Val=atof(tempstr);
	((CEdit*)GetDlgItem(IDE_BiHouBaiFenBi))->GetWindowText(tempstr);
	int Per=atoi(tempstr);
	if(Val>2*tw)
	{
		AfxMessageBox("���	�ں����");
		return;
	}
	if(Val<0.5*tw)
	{
		AfxMessageBox("���ں��С");
		return;
	}
	if(Val==tw)
	{
		AfxMessageBox("���ں������׼�ں���ͬ");
		return;
	}
	if(Per<0)
	{
		AfxMessageBox("����ʲ���Ϊ����");
		return;
	}
	m_list=(CListCtrl*)GetDlgItem(IDC_LIST_BIHOU_WUCHA);
	int i=0;
	for(i=0;i<m_list->GetItemCount();i++)
	{
		tempstr=m_list->GetItemText(i,0);
		if(atof(tempstr)==Val)
		{
			tempstr.Format("Val���%d���ظ�",i+1);
			AfxMessageBox(tempstr);
			return;
		}
	}
	if(Per>20)
	{
		tempstr.Format("����ʹ���!");
		MessageBox(tempstr,"����",MB_ICONWARNING);
		//	return;
	}
	tempstr.Format("%.4f",Val);
	m_list->InsertItem(0,"");
	m_list->SetItemText(0,0,tempstr);
	tempstr.Format("%d",Per);
	m_list->SetItemText(0,1,tempstr);	
}

void CSet::OnDelBihou() 
{
	CListCtrl* m_list=NULL;
	m_list=(CListCtrl*)GetDlgItem(IDC_LIST_BIHOU_WUCHA);
	while(m_list->GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_list->GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_list->DeleteItem(nItem);
	}
}

BOOL CSet::AddDeviation()
{
	CListCtrl* m_list=NULL;
	int i=0;
	int Per=0;
	CString tempstr="";
	m_list=(CListCtrl*)GetDlgItem(IDC_LIST_WAIJING_WUCHA);
	D_Deviation_Per[0]=m_list->GetItemCount()+1;
	if(D_Deviation_Per[0]>=20)
	{
		AfxMessageBox("����⾶ֵ����18��,�뱣�ֵ���18��");
		return FALSE;
	}
	for(i=0;i<D_Deviation_Per[0]-1;i++)
	{
		tempstr=m_list->GetItemText(i,0);
		D_Deviation[i+2]=atof(tempstr);
		tempstr=m_list->GetItemText(i,1);
		D_Deviation_Per[i+2]=atoi(tempstr);
		Per=Per+D_Deviation_Per[i+2];
	}
	if(Per>30)
	{
		if(IDYES!=MessageBox("��ǰ����ʳ���30%,�Ƿ����?","����",MB_YESNO))
			return FALSE;
	}
	Per=0;
	m_list=(CListCtrl*)GetDlgItem(IDC_LIST_BIHOU_WUCHA);
	tw_Deviation_Per[0]=m_list->GetItemCount()+1;
	if(tw_Deviation_Per[0]>=20)
	{
		AfxMessageBox("���ں�ֵ����18��,�뱣�ֵ���18��");
		return FALSE;
	}
	for(i=0;i<tw_Deviation_Per[0]-1;i++)
	{
		tempstr=m_list->GetItemText(i,0);
		tw_Deviation[i+2]=atof(tempstr);
		tempstr=m_list->GetItemText(i,1);
		tw_Deviation_Per[i+2]=atoi(tempstr);
		Per=Per+tw_Deviation_Per[i+2];
	}
	if(Per>30)
	{
		if(IDYES!=MessageBox("��ǰ����ʳ���30%,�Ƿ����?","����",MB_YESNO))
			return FALSE;
	}
	return TRUE;
	
}

void CSet::OnBtnTestzero() 
{
/*typedef double (_stdcall * AddProc)(double,double);//���庯��ָ������

  HINSTANCE hInst;
  
	hInst=LoadLibrary("Zero.dll");//��̬����Dll
	
	  AddProc Max=(AddProc)GetProcAddress(hInst,"max");//��ȡDll�ĵ�������
	  
		if(!Max)
		{
		MessageBox("��ȡMax������ַʧ�ܣ�");
		}
		
		  //double guess=Rand::Gauss(0.5,1.5);
		  CString str="";
		  str.Format("guess=%.4f",Max(1.5,2.6));
		  AfxMessageBox(str);
	::FreeLibrary(hInst);//�ͷ�Dll����*/
}

void CSet::OnBtnSection() 
{
	CSection dlg;
	dlg.DoModal();
}

void CSet::InitVal()
{
	SectionFlag=0;
	Count_X=0;
	Count_Y=0;
	Count_Z=0;
	GradeID=5;
	ValCount0=0;
	ValCount=0;
	XiaBuTuoChengGaoDu=0;
	//memset(ValCount,0,sizeof(ValCount)/sizeof(ValCount[0])*sizeof(int));
	((CButton*)GetDlgItem(IDC_RADIO_G1))->SetCheck(TRUE);
	CListCtrl* m_list=(CListCtrl*)GetDlgItem(IDC_LIST_WAIJING_WUCHA);
	m_list->InsertColumn(0,"�⾶",LVCFMT_CENTER,50);
	m_list->InsertColumn(1,"%",LVCFMT_CENTER,30);
	m_list->InsertColumn(2,"ToTal(%)",LVCFMT_CENTER,70);
	m_list->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	
	m_list=(CListCtrl*)GetDlgItem(IDC_LIST_BIHOU_WUCHA);
	m_list->InsertColumn(0,"�ں�",LVCFMT_CENTER,50);
	m_list->InsertColumn(1,"%",LVCFMT_CENTER,30);
	m_list->InsertColumn(2,"ToTal(%)",LVCFMT_CENTER,70);
	m_list->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	
	PaiJuGeShu_Y=0;
	ZhuJuGeShu_X=0;
	BuJuGeShu_Z=0;	// TODO: Add extra initialization here
	D=0.048;//DΪ��׼�⾶
	tw=0.0035;//twΪ��׼�ں�
	CString tempstr="";
	tempstr.Format("%.3f",D);
	((CEdit*)GetDlgItem(IDE_GangGuanWaiJing))->SetWindowText(tempstr);
	tempstr.Format("%.4f",tw);
	((CEdit*)GetDlgItem(IDE_GangGuanBiHou))->SetWindowText(tempstr);
	memset(D_Deviation,0,sizeof(D_Deviation)/sizeof(D_Deviation[0])*sizeof(double));
	memset(D_Deviation_Per,0,sizeof(D_Deviation_Per)/sizeof(D_Deviation_Per[0])*sizeof(int));
	memset(tw_Deviation,0,sizeof(tw_Deviation)/sizeof(tw_Deviation[0])*sizeof(double));
	memset(tw_Deviation_Per,0,sizeof(tw_Deviation_Per)/sizeof(tw_Deviation_Per[0])*sizeof(int));

	int i=0;
	SectionVal[i++]=20;
	SectionVal[i++]=50;
	SectionVal[i++]=110;

	SectionVal[i++]=200;
	SectionVal[i++]=50;
	SectionVal[i++]=250;
	SectionVal[i++]=50;
	SectionVal[i++]=250;
	SectionVal[i++]=50;

	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;

	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
	SectionVal[i++]=30;
}