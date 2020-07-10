
// A_simple_testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "A_simple_test.h"
#include "A_simple_testDlg.h"
#include "afxdialogex.h"
#include "zauxdll2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


ZMC_HANDLE       g_handle = NULL;				//控制器链接句柄
CString ipadress;
char* ipadressChar;
int m_nAxis = 0;



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CA_simple_testDlg 对话框



CA_simple_testDlg::CA_simple_testDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_A_SIMPLE_TEST_DIALOG, pParent)
	, input_Speed(0)
	, input_positive_acc(0)
	, input_negative_acc(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CA_simple_testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_show_if_connected, text_show_if_connected);
	DDX_Control(pDX, IDC_BUTTON_disconnect, button_disconnect);
	DDX_Control(pDX, IDC_BUTTON_connect, button_connect);
	DDX_Control(pDX, IDC_input_IPAdress, input_ipadress);
	DDX_Control(pDX, IDC_BUTTON_connect, button_connect);
	DDX_Control(pDX, IDC_show_CPosition, show_CPosition);
	DDX_Control(pDX, IDC_show_CSpeed, show_CSpeed);

	DDX_Control(pDX, IDC_BUTTON_move, button_move);
	DDX_Control(pDX, IDC_BUTTON_stop, button_stop);
	DDX_Text(pDX, IDC_input_Speed, input_Speed);
	DDV_MinMaxFloat(pDX, input_Speed, 0, 100);
	DDX_Text(pDX, IDC_input_positive_acc, input_positive_acc);
	DDV_MinMaxFloat(pDX, input_positive_acc, 0, 20);
	DDX_Text(pDX, IDC_input_negative_acc, input_negative_acc);
	DDV_MinMaxFloat(pDX, input_negative_acc, 0, 20);
}

BEGIN_MESSAGE_MAP(CA_simple_testDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_connect, &CA_simple_testDlg::OnBnClickedButtonconnect)
	ON_BN_CLICKED(IDC_BUTTON_disconnect, &CA_simple_testDlg::OnBnClickedButtondisconnect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_move, &CA_simple_testDlg::OnBnClickedButtonmove)
	ON_BN_CLICKED(IDC_BUTTON_stop, &CA_simple_testDlg::OnBnClickedButtonstop)
END_MESSAGE_MAP()


// CA_simple_testDlg 消息处理程序

BOOL CA_simple_testDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_nAxis = 0; //选择轴1
	
	input_ipadress.SetWindowTextW(TEXT("请输入仿真器IP地址"));		//初始化 输入IP地址 文本输入框中的字符显示
	show_CPosition.SetWindowTextW(TEXT("暂未获得位置数据"));		//初始化 显示位置 文本输入框中的字符显示
	show_CSpeed.SetWindowTextW(TEXT("暂未获得速度数据"));			//初始化 显示速度 文本输入框中的字符显示

	input_Speed=0;				//初始化 设置速度 文本输入框中的字符显示
	input_positive_acc=0;		//初始化 设置正向加速度 文本输入框中的字符显示
	input_negative_acc=0;		//初始化 设置反向加速度 文本输入框中的字符显示

	UpdateData(FALSE);          //将程序内的数据上传到控件





	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CA_simple_testDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CA_simple_testDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CA_simple_testDlg::OnClose() 
{ 
	if (NULL != g_handle)
	{
		KillTimer(1);						//关定时器
		ZAux_Close(g_handle);
		g_handle = NULL;
		
	}
		CDialog::OnClose();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CA_simple_testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CA_simple_testDlg::OnBnClickedButtonconnect()
{
		
	if (NULL != g_handle)
	{
		ZAux_Close(g_handle);
		g_handle = NULL;
	}
	
	input_ipadress.GetWindowTextW(ipadress);  //获取ip地址输入框中的ip地址，但不能直接使用

	// 从这里开始进行 CString 到 char* 的转化，这是一个宏定义
	USES_CONVERSION;
	//进行转换
	ipadressChar = T2A(ipadress.GetBuffer(0));
	ipadress.ReleaseBuffer();
	//转化结束
	int32 connectresult;
	connectresult=ZAux_OpenEth(ipadressChar, &g_handle);    //尝试连接到仿真器，返回连接结果

	
	if (ERR_SUCCESS != connectresult)
	{
		g_handle = NULL;
		//若没有成功连接到仿真器，则弹出窗口提示重试尝试连接
		MessageBox(TEXT("请尝试重新连接到仿真器"), TEXT("未成功连接"));
		return;
	}

	
	text_show_if_connected.SetWindowTextW(TEXT("已连接")); //若连接到仿真器，则显示连接状态为已连接
	button_connect.EnableWindow(FALSE); //连接后禁用连接按钮，防止重连

	SetTimer(1, 100, NULL);//打开定时器

}


void CA_simple_testDlg::OnBnClickedButtondisconnect()
{
	if (NULL != g_handle)
	{
		KillTimer(1);						//关定时器
		ZAux_Close(g_handle);
		g_handle = NULL;
		text_show_if_connected.SetWindowTextW(TEXT("已断开")); //显示连接状态为已断开
		show_CPosition.SetWindowTextW(TEXT("暂未获得位置数据")); //初始化 显示位置 文本输入框中的字符显示
		show_CSpeed.SetWindowTextW(TEXT("暂未获得速度数据")); //初始化 显示速度 文本输入框中的字符显示
		button_connect.EnableWindow(TRUE); //恢复连接按钮
	}
}


void CA_simple_testDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (NULL == g_handle)
	{
		MessageBox(_T("与仿真器未连接"));                                  //提示与仿真器断开连接
		return;
	}
	if (1 == nIDEvent)
	{
		
		
		CString stringPosition;
		CString stringSpeed;
		float position = 0;
		ZAux_Direct_GetDpos(g_handle, m_nAxis, &position);          //获取当前轴位置
		stringPosition.Format(_T("%.2f"), position);
		show_CPosition.SetWindowTextW(stringPosition);

		float NowSp = 0;
		ZAux_Direct_GetVpSpeed(g_handle, m_nAxis, &NowSp);          //获取当前轴速度
		stringSpeed.Format(_T("%.2f"), NowSp);
		show_CSpeed.SetWindowTextW(stringSpeed);
				
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CA_simple_testDlg::OnBnClickedButtonmove()
{
	if (NULL == g_handle)
	{
		MessageBox(_T("链接断开状态"));
		return;
	}

	UpdateData(TRUE);//读入对话框上的参数

	int status = 0;
	ZAux_Direct_GetIfIdle(g_handle, m_nAxis, &status);           //判断当前轴是否已经开始运动

	if (status == 0) //已经在运动中
		return;
	
	//设定轴类型 1 也即脉冲方向方式的步进或伺服	
	ZAux_Direct_SetAtype(g_handle,m_nAxis, 1);

	//设定脉冲模式及逻辑方向 0表示（脉冲+方向）	
	ZAux_Direct_SetInvertStep(g_handle,m_nAxis, 0);

	//设置脉冲当量	1表示以一个脉冲为单位 ，设置为1MM的脉冲个数，这度量单位为MM
	ZAux_Direct_SetUnits(g_handle,m_nAxis, 1);

	//设定速度，加减速
	ZAux_Direct_SetLspeed(g_handle,m_nAxis, 0);		//设定起始速度为零
	ZAux_Direct_SetSpeed(g_handle, m_nAxis, input_Speed);
	ZAux_Direct_SetAccel(g_handle, m_nAxis, input_positive_acc);
	ZAux_Direct_SetDecel(g_handle, m_nAxis, input_negative_acc);


	//设定S曲线时间 设置为0表示梯形加减速，大于0为S型运动，此处为10
	ZAux_Direct_SetSramp(g_handle, m_nAxis, 10);

	//持续驱动(速度模式)
	//ZAux_Direct_Singl_Vmove(g_handle, m_nAxis, m_bLogic ? 1 : 0);
	//若m_bLogic为true则为正向运动，反之为反向运动，这里默认只有正向运动功能
	ZAux_Direct_Singl_Vmove(g_handle, m_nAxis, true ? 1 : 0);
	
	UpdateData(FALSE);
}


void CA_simple_testDlg::OnBnClickedButtonstop()
{
	if (NULL == g_handle)
	{
		MessageBox(_T("链接断开状态"));
		return;
	}

	ZAux_Direct_Singl_Cancel(g_handle, m_nAxis, 2);//命令伺服驱动器停止
}


void CA_simple_testDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
