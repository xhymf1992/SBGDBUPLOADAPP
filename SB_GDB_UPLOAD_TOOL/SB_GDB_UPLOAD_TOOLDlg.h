
// SB_GDB_UPLOAD_TOOLDlg.h : 头文件
//

#pragma once
#include <vector>
#include <string>

using namespace std;

// CSB_GDB_UPLOAD_TOOLDlg 对话框
class CSB_GDB_UPLOAD_TOOLDlg : public CDialogEx
{
// 构造
public:
	CSB_GDB_UPLOAD_TOOLDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SB_GDB_UPLOAD_TOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	//
	afx_msg void OnOpenGDBDir();
	afx_msg void OnSignIn();
	afx_msg void OnUpload();
	afx_msg void OnCancel();

	DECLARE_MESSAGE_MAP()

protected:

	void EsReset();

	//init gdbreader
	bool EsInitGDBReader();

	//A6_CollectedEpiMechanismResult
	bool EsUploadCollectedEpiMechanismResult();

	//A6_CollectedRelocationISCatalog
	bool EsUploadCollectedRelocationISCatalog();

private:
	int m_nSId;

	CString m_strUserName;
	CString m_strPassWord;
	CString m_strGDBDir;

	CComboBox m_comboSpaceList;
	vector<pair<string, int>> m_vecPairSpaceNameAndId;
};
