
// SB_GDB_UPLOAD_TOOLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SB_GDB_UPLOAD_TOOL.h"
#include "SB_GDB_UPLOAD_TOOLDlg.h"
#include "afxdialogex.h"
#include "EsGDBReader.h"
#include "EsTEMySQLAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSB_GDB_UPLOAD_TOOLDlg 对话框



CSB_GDB_UPLOAD_TOOLDlg::CSB_GDB_UPLOAD_TOOLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSB_GDB_UPLOAD_TOOLDlg::IDD, pParent)
	, m_nSId(1)
	, m_strUserName("")
	, m_strPassWord("")
	, m_strGDBDir("")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSB_GDB_UPLOAD_TOOLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_PASS_WORD, m_strPassWord);
	DDX_Text(pDX, IDC_EDIT_GDB_DIR, m_strGDBDir);
	DDX_Control(pDX, IDC_COMBO_SPACE_LIST, m_comboSpaceList);
}

BEGIN_MESSAGE_MAP(CSB_GDB_UPLOAD_TOOLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_DIR, &CSB_GDB_UPLOAD_TOOLDlg::OnOpenGDBDir)
	ON_BN_CLICKED(IDC_BUTTON_SIGN_IN, &CSB_GDB_UPLOAD_TOOLDlg::OnSignIn)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CSB_GDB_UPLOAD_TOOLDlg::OnUpload)
	ON_BN_CLICKED(IDCANCEL, &CSB_GDB_UPLOAD_TOOLDlg::OnCancel)
END_MESSAGE_MAP()


// CSB_GDB_UPLOAD_TOOLDlg 消息处理程序

BOOL CSB_GDB_UPLOAD_TOOLDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_COMBO_SPACE_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OPEN_DIR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSB_GDB_UPLOAD_TOOLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSB_GDB_UPLOAD_TOOLDlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSB_GDB_UPLOAD_TOOLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSB_GDB_UPLOAD_TOOLDlg::OnOpenGDBDir()
{
	BROWSEINFO bi;                                 //BROWSEINFO结构体
	TCHAR Buffer[512] = _T("");
	TCHAR FullPaths[512] = _T("");
	bi.hwndOwner = m_hWnd;                         //m_hWnd你的程序主窗口
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;                    //返回选择的目录名的缓冲区
	bi.lpszTitle = _T("请选择GDB文件夹");          //弹出的窗口的文字提示
	bi.ulFlags = NULL;                             //BIF_RETURNONLYFSDIRS|BIF_EDITBOX|BIF_BROWSEFORCOMPUTER ;    //只返回目录。其他标志看MSDN
	bi.lpfn = NULL;                                //回调函数，有时很有用
	bi.lParam = 0;
	bi.iImage = 0;
	ITEMIDLIST* pidl = ::SHBrowseForFolder (&bi);  //显示弹出窗口，ITEMIDLIST很重要
	::SHGetPathFromIDList (pidl,FullPaths);        //在ITEMIDLIST中得到目录名的整个路径
	if(FullPaths[0]!=NULL)
	{
		m_strGDBDir=FullPaths;
		UpdateData(FALSE);
	}
}

void CSB_GDB_UPLOAD_TOOLDlg::OnSignIn()
{
	UpdateData(TRUE);

	if(m_strUserName.IsEmpty())
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(_T("用户名不能为空！\r\n"));
		return;
	}

	if(m_strPassWord.IsEmpty())
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(_T("密码不能为空！\r\n"));
		return;
	}

	string strUserName = CT2A(m_strUserName.GetString());
	string strPassWord = CT2A(m_strPassWord.GetString());
	
	if(!EsLoginToTransparentEarth(strUserName, strPassWord, m_vecPairSpaceNameAndId))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(_T("登陆失败！\r\n"));
		EsReset();
		return;
	}

	if(!m_vecPairSpaceNameAndId.empty())
	{
		m_comboSpaceList.ResetContent();
		for(auto pair : m_vecPairSpaceNameAndId)
		{
			m_comboSpaceList.AddString(LPCTSTR(pair.first.c_str()));
		}
		m_comboSpaceList.SetCurSel(0);
	}
	
	GetDlgItem(IDC_COMBO_SPACE_LIST)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_OPEN_DIR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(TRUE);

	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("登陆成功！\r\n");
}

void CSB_GDB_UPLOAD_TOOLDlg::OnUpload()
{
	//先重置
	m_nSId = -1;

	//获取sid
	int nCurIdx = m_comboSpaceList.GetCurSel();
	CString strSpaceNameSel = "";
	m_comboSpaceList.GetLBText(nCurIdx, strSpaceNameSel);

	for(auto pair : m_vecPairSpaceNameAndId)
	{
		if(pair.first.c_str() == strSpaceNameSel)
		{
			m_nSId = pair.second;
			break;
		}	
	}

	if(m_nSId == -1)
	{
		return;
	}

	//
	if(!EsInitGDBReader())
	{
		return;
	}

	//
	if(!EsUploadCollectedEpiMechanismResult())
	{
		return;
	}	

	//
}

void CSB_GDB_UPLOAD_TOOLDlg::OnCancel()
{
	CDialogEx::OnCancel();
}

void CSB_GDB_UPLOAD_TOOLDlg::EsReset()
{
	GetDlgItem(IDC_COMBO_SPACE_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OPEN_DIR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_UPLOAD)->EnableWindow(FALSE);

	m_comboSpaceList.ResetContent();
	m_strGDBDir = "";
	m_nSId = -1;

	UpdateData(FALSE);
}

bool CSB_GDB_UPLOAD_TOOLDlg::EsInitGDBReader()
{
	if(m_strGDBDir.IsEmpty())
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("请先选择GDB目录！\r\n");
		return false;
	}

	string strFilePath = CT2A(m_strGDBDir.GetString());

	EsGDBReader obReader;
	if(!obReader.EsGDBInit(strFilePath))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("GDB读取失败，请检查目录是否正确！\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		return false;
	}

	return true;
}

bool CSB_GDB_UPLOAD_TOOLDlg::EsUploadCollectedEpiMechanismResult()
{
	EsGDBReader obReader;

	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("正在获取收集震源机制解...\r\n");
	vector<_COLLECTEDEPIMECHANISMRESULT> vec_CollectedEpiMechanismResult;
	if(!obReader.EsGetCollectedEpiMechanismResult(vec_CollectedEpiMechanismResult))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("收集震源机制解获取失败！\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("\r\n");
		return false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("收集震源机制解获取成功！\r\n");
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("正在上传收集震源机制解...\r\n");
	if(!EsAddCollectedEpiMechanismResultToNetDB(m_nSId, vec_CollectedEpiMechanismResult))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("收集震源机制解上传失败！\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("\r\n");
		return false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("收集震源机制解上传成功！\r\n");

	return true;
}

bool CSB_GDB_UPLOAD_TOOLDlg::EsUploadCollectedRelocationISCatalog()
{
	EsGDBReader obReader;

	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("正在获取收集小震重定位目录...\r\n");
	vector<_COLLECTEDRELOCATIONISCATALOG> vec_CollectedRelocationISCatalog;
	if(!obReader.EsGetCollectedRelocationISCatalog(vec_CollectedRelocationISCatalog))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("收集小震重定位目录获取失败！\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("\r\n");
		return false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("收集小震重定位目录获取成功！\r\n");
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("正在上传收集小震重定位目录...\r\n");
	if(!EsAddCollectedRelocationISCatalogToNetDB(m_nSId, vec_CollectedRelocationISCatalog))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("收集小震重定位目录上传失败！\r\n");
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel(obReader.EsGetError());
		((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("\r\n");
		return false;
	}
	((CEdit*)GetDlgItem(IDC_EDIT_PROCESS_INFO))->ReplaceSel("收集小震重定位目录上传成功！\r\n");

	return true;
}