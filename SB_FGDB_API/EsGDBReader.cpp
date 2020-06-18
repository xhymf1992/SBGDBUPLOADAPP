#include <windows.h>
#include <comdef.h> 
#include "EsGDBReader.h"


Geodatabase EsGDBReader::m_obGDB;

EsGDBReader::EsGDBReader()
	: m_strError("")
{

}

EsGDBReader::~EsGDBReader()
{

}

bool EsGDBReader::EsGDBInit(const string& strFilePath)
{
	const wstring wstrFilePath = StringToWString(strFilePath);

	fgdbError hr;
	if((hr = OpenGeodatabase(wstrFilePath, m_obGDB)) != S_OK)
	{
		return false;
	}

	return true;
}

bool EsGDBReader::EsTableOpen(const string& strTableName, Table& obTable)
{
	const wstring wstrTableName = StringToWString(strTableName);

	fgdbError hr;
	wstring wstrErrorText;
	if((hr = m_obGDB.OpenTable(wstrTableName, obTable)) != S_OK)
	{
		ErrorInfo::GetErrorDescription(hr, wstrErrorText);
		EsSetError(wstrErrorText);
		return false;
	}

	return true;
}

bool EsGDBReader::EsTableSearchAll(Table& obTable, EnumRows& obRows)
{
	wstring wstrSearchFileds = StringToWString("*");
	wstring wstrSearchClause = StringToWString("");

	fgdbError hr;
	wstring wstrErrorText;
	if ((hr = obTable.Search(wstrSearchFileds, wstrSearchClause, true, obRows)) != S_OK)
	{
		ErrorInfo::GetErrorDescription(hr, wstrErrorText);
		EsSetError(wstrErrorText);
		return false;
	}

	return true;
}

void EsGDBReader::EsSetError(const wstring& strError)
{
	m_strError = ws2s(strError);
}

wstring EsGDBReader::StringToWString(const string& str) 
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	std::wstring w_str(wide);
	delete[] wide;
	return w_str;
}

string EsGDBReader::WStringToString(const wstring &wstr)
{
	std::string str;
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');
	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);
	if (nResult == 0)
	{
		return "";
	}
	return str;
}

char* EsGDBReader::ws2s(const wstring& ws)  
{  
	_bstr_t t = ws.c_str();   
	char* pchar = (char*)t;   
	string result = pchar;  
	char* charTmp = new char;  
	strcpy_s(charTmp, strlen(result.c_str())+1, result.c_str());  
	pchar = NULL;  
	delete pchar;  
	return charTmp;  
}