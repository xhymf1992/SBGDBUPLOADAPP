#include "windows.h"
#include "Python.h"
#include "EsTEMySQLAPI.h"


const char* module_name = "http_seismological_bureau_api";

const char* err_URLError = "URLError";
const char* err_HTTPError = "HTTPError";

const char* func_add_collected_epimechanismresult = "api_add_collected_epimechanismresult";
const char* func_add_collected_relocationiscatalog = "api_add_collected_relocationiscatalog";

//url net
//const char* url_add_collected_epimechanismresult = "https://49.5.11.154/mysql/seismological_bureau/add_collected_epimechanismresult/";
//const char* url_add_collected_relocationiscatalog = "https://49.5.11.154/mysql/seismological_bureau/add_collected_relocationiscatalog/";


//url local
const char* url_add_collected_epimechanismresult = "http://127.0.0.1:5000/seismological_bureau/add_collected_epimechanismresult/";
const char* url_add_collected_relocationiscatalog = "http://127.0.0.1:5000/seismological_bureau/add_collected_relocationiscatalog/";

string WstringToString(const wstring str)
{
	unsigned len = unsigned(str.size() * 4);
	setlocale(LC_CTYPE, "");
	char *p = new char[len];
	wcstombs(p, str.c_str(), len);
	std::string str1(p);
	delete[] p;
	return str1;
}

PyObject* StringToPy(string p_obj )
{
	int wlen=::MultiByteToWideChar(CP_ACP,NULL, p_obj.c_str(), int(p_obj.length()), NULL, 0);
	wchar_t* wszString=new wchar_t[wlen+1];
	::MultiByteToWideChar(CP_ACP, NULL, p_obj.c_str(), int(p_obj.length()), wszString, wlen);
	wszString[wlen]='\0';
	PyObject* pb=PyUnicode_FromUnicode((const Py_UNICODE*)wszString, wlen);
	delete wszString;
	return pb;
}

bool EsLoginToTransparentEarth(const string& strUserName, const string& strPassWord, vector<pair<string, int>>& vecPairSpaceNameAndId)
{
	if(strUserName == "test" && strPassWord == "grid1501")
	{
		string strSpaceName = "test";
		int nSId = 1;
		vecPairSpaceNameAndId.clear();
		vecPairSpaceNameAndId.push_back(make_pair(strSpaceName, nSId));

		return true;	
	}

	return false;
}

bool EsAddCollectedEpiMechanismResultToNetDB(const int nSId, const vector<_COLLECTEDEPIMECHANISMRESULT>& vec_CollectedEpiMechanismResult)
{
	if(vec_CollectedEpiMechanismResult.empty())
	{
		return false;
	}

	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");//这一步很重要，修改Python路径
	PyObject* pModule = NULL;
	PyObject* pFunc = NULL;
	pModule = PyImport_ImportModule(module_name);
	if (pModule == NULL)
	{
		return false;
	}

	int nRecordNum = int(vec_CollectedEpiMechanismResult.size());

	pFunc = PyObject_GetAttrString(pModule, func_add_collected_epimechanismresult);
	if(pFunc == NULL)
	{
		return false;
	}

	PyObject* args = PyTuple_New(29);

	PyObject* pyTupleURL = PyTuple_New(1);
	PyObject* pyTupleSID = PyTuple_New(1);
	PyObject* pyTuplePoints = PyTuple_New(nRecordNum);
	PyObject* pyTupleIds = PyTuple_New(nRecordNum);
	PyObject* pyTupleOccurrencedates = PyTuple_New(nRecordNum);
	PyObject* pyTupleOccurrencetimes = PyTuple_New(nRecordNum);
	PyObject* pyTupleLocationnames = PyTuple_New(nRecordNum);
	PyObject* pyTupleLons = PyTuple_New(nRecordNum);
	PyObject* pyTupleLats = PyTuple_New(nRecordNum);
	PyObject* pyTupleMagnitudes = PyTuple_New(nRecordNum);
	PyObject* pyTupleUnits = PyTuple_New(nRecordNum);
	PyObject* pyTupleDepths = PyTuple_New(nRecordNum);
	PyObject* pyTupleShazimuths = PyTuple_New(nRecordNum);
	PyObject* pyTupleStressregimes = PyTuple_New(nRecordNum);
	PyObject* pyTuplePlane1strikes = PyTuple_New(nRecordNum);
	PyObject* pyTuplePlane1dips = PyTuple_New(nRecordNum);
	PyObject* pyTuplePlane1slips = PyTuple_New(nRecordNum);
	PyObject* pyTuplePlane2strikes = PyTuple_New(nRecordNum);
	PyObject* pyTuplePlane2dips = PyTuple_New(nRecordNum);
	PyObject* pyTuplePlane2slips = PyTuple_New(nRecordNum);
	PyObject* pyTuplePazimuths = PyTuple_New(nRecordNum);
	PyObject* pyTuplePplunges = PyTuple_New(nRecordNum);
	PyObject* pyTupleTazimuths = PyTuple_New(nRecordNum);
	PyObject* pyTupleTplunges = PyTuple_New(nRecordNum);
	PyObject* pyTupleBazimuths = PyTuple_New(nRecordNum);
	PyObject* pyTupleBplunges = PyTuple_New(nRecordNum);
	PyObject* pyTupleMethods = PyTuple_New(nRecordNum);
	PyObject* pyTupleReferences = PyTuple_New(nRecordNum);
	PyObject* pyTupleCommentinfos = PyTuple_New(nRecordNum);

	//url
	PyTuple_SetItem(pyTupleURL, 0, StringToPy(url_add_collected_epimechanismresult));

	//sid
	PyTuple_SetItem(pyTupleSID, 0, Py_BuildValue("i", nSId));
	
	for (int idx = 0; idx < nRecordNum; idx++)
	{
		//point
		PyObject* pyTuplePoint = PyTuple_New(3);
		PyTuple_SetItem(pyTuplePoint, 0, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._point._x));
		PyTuple_SetItem(pyTuplePoint, 1, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._point._y));
		PyTuple_SetItem(pyTuplePoint, 2, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._point._z));
		PyTuple_SetItem(pyTuplePoints, idx, pyTuplePoint);

		//
		PyTuple_SetItem(pyTupleIds, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._baseinfo._ID)));
		PyTuple_SetItem(pyTupleOccurrencedates, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._OccurrenceDate)));
		PyTuple_SetItem(pyTupleOccurrencetimes, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._OccurrenceTime)));
		PyTuple_SetItem(pyTupleLocationnames, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._LocationName)));
		PyTuple_SetItem(pyTupleLons, idx, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._Lon));
		PyTuple_SetItem(pyTupleLats, idx, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._Lat));
		PyTuple_SetItem(pyTupleMagnitudes, idx, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._Magnitude));
		PyTuple_SetItem(pyTupleUnits, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._Unit)));
		PyTuple_SetItem(pyTupleDepths, idx, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._Depth));
		PyTuple_SetItem(pyTupleShazimuths, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._SHAzimuth));
		PyTuple_SetItem(pyTupleStressregimes, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._StressRegime));
		PyTuple_SetItem(pyTuplePlane1strikes, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane1Strike));
		PyTuple_SetItem(pyTuplePlane1dips, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane1Dip));
		PyTuple_SetItem(pyTuplePlane1slips, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane1Slip));		
		PyTuple_SetItem(pyTuplePlane2strikes, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane2Strike));
		PyTuple_SetItem(pyTuplePlane2dips, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane2Dip));		
	    PyTuple_SetItem(pyTuplePlane2slips, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane2Slip));
		PyTuple_SetItem(pyTuplePazimuths, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._PAzimuth));
		PyTuple_SetItem(pyTuplePplunges, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._PPlunge));
		PyTuple_SetItem(pyTupleTazimuths, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._TAzimuth));
		PyTuple_SetItem(pyTupleTplunges, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._TPlunge));
		PyTuple_SetItem(pyTupleBazimuths, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._BAzimuth));
		PyTuple_SetItem(pyTupleBplunges, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._BPlunge));
		PyTuple_SetItem(pyTupleMethods, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._Method)));
		PyTuple_SetItem(pyTupleReferences, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._Reference)));		
		PyTuple_SetItem(pyTupleCommentinfos, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._baseinfo._CommentInfo)));
	}

	PyTuple_SetItem(args, 0, pyTupleURL);
	PyTuple_SetItem(args, 1, pyTupleSID);
	PyTuple_SetItem(args, 2, pyTuplePoints);
	PyTuple_SetItem(args, 3, pyTupleIds);
	PyTuple_SetItem(args, 4, pyTupleOccurrencedates);
	PyTuple_SetItem(args, 5, pyTupleOccurrencetimes);
	PyTuple_SetItem(args, 6, pyTupleLocationnames);
	PyTuple_SetItem(args, 7, pyTupleLons);
	PyTuple_SetItem(args, 8, pyTupleLats);
	PyTuple_SetItem(args, 9, pyTupleMagnitudes);
	PyTuple_SetItem(args, 10, pyTupleUnits);
	PyTuple_SetItem(args, 11, pyTupleDepths);
	PyTuple_SetItem(args, 12, pyTupleShazimuths);
	PyTuple_SetItem(args, 13, pyTupleStressregimes);
	PyTuple_SetItem(args, 14, pyTuplePlane1strikes);
	PyTuple_SetItem(args, 15, pyTuplePlane1dips);
	PyTuple_SetItem(args, 16, pyTuplePlane1slips);
	PyTuple_SetItem(args, 17, pyTuplePlane2strikes);
	PyTuple_SetItem(args, 18, pyTuplePlane2dips);
	PyTuple_SetItem(args, 19, pyTuplePlane2slips);
	PyTuple_SetItem(args, 20, pyTuplePazimuths);
	PyTuple_SetItem(args, 21, pyTuplePplunges);
	PyTuple_SetItem(args, 22, pyTupleTazimuths);
	PyTuple_SetItem(args, 23, pyTupleTplunges);
	PyTuple_SetItem(args, 24, pyTupleBazimuths);
	PyTuple_SetItem(args, 25, pyTupleBplunges);
	PyTuple_SetItem(args, 26, pyTupleMethods);
	PyTuple_SetItem(args, 27, pyTupleReferences);
	PyTuple_SetItem(args, 28, pyTupleCommentinfos);	

	PyObject* pRet = PyEval_CallObject(pFunc, args);
	const char* szRet = pRet->ob_type->tp_name;
	if(*szRet == *err_URLError || *szRet == *err_HTTPError)
		return false;

	Py_Finalize();

	return true;
}

bool EsAddCollectedRelocationISCatalogToNetDB(const int nSId, const vector<_COLLECTEDRELOCATIONISCATALOG>& vec_CollectedRelocationISCatalog)
{
	//if(vec_CollectedRelocationISCatalog.empty())
	//{
	//	return false;
	//}

	//Py_Initialize();
	//PyRun_SimpleString("import sys");
	//PyRun_SimpleString("sys.path.append('./')");//这一步很重要，修改Python路径
	//PyObject* pModule = NULL;
	//PyObject* pFunc = NULL;
	//pModule = PyImport_ImportModule(module_name);
	//if (pModule == NULL)
	//{
	//	return false;
	//}

	//int nRecordNum = int(vec_CollectedRelocationISCatalog.size());

	//pFunc = PyObject_GetAttrString(pModule, func_add_collected_relocationiscatalog);
	//if(pFunc == NULL)
	//{
	//	return false;
	//}

	//PyObject* args = PyTuple_New(29);

	//PyObject* pyTupleURL = PyTuple_New(1);
	//PyObject* pyTupleSID = PyTuple_New(1);
	//PyObject* pyTuplePoints = PyTuple_New(nRecordNum);
	//PyObject* pyTupleIds = PyTuple_New(nRecordNum);
	//PyObject* pyTupleOccurrencedates = PyTuple_New(nRecordNum);
	//PyObject* pyTupleOccurrencetimes = PyTuple_New(nRecordNum);
	//PyObject* pyTupleLocationnames = PyTuple_New(nRecordNum);
	//PyObject* pyTupleLons = PyTuple_New(nRecordNum);
	//PyObject* pyTupleLats = PyTuple_New(nRecordNum);
	//PyObject* pyTupleMagnitudes = PyTuple_New(nRecordNum);
	//PyObject* pyTupleUnits = PyTuple_New(nRecordNum);
	//PyObject* pyTupleDepths = PyTuple_New(nRecordNum);
	//PyObject* pyTupleShazimuths = PyTuple_New(nRecordNum);
	//PyObject* pyTupleStressregimes = PyTuple_New(nRecordNum);
	//PyObject* pyTuplePlane1strikes = PyTuple_New(nRecordNum);
	//PyObject* pyTuplePlane1dips = PyTuple_New(nRecordNum);
	//PyObject* pyTuplePlane1slips = PyTuple_New(nRecordNum);
	//PyObject* pyTuplePlane2strikes = PyTuple_New(nRecordNum);
	//PyObject* pyTuplePlane2dips = PyTuple_New(nRecordNum);
	//PyObject* pyTuplePlane2slips = PyTuple_New(nRecordNum);
	//PyObject* pyTuplePazimuths = PyTuple_New(nRecordNum);
	//PyObject* pyTuplePplunges = PyTuple_New(nRecordNum);
	//PyObject* pyTupleTazimuths = PyTuple_New(nRecordNum);
	//PyObject* pyTupleTplunges = PyTuple_New(nRecordNum);
	//PyObject* pyTupleBazimuths = PyTuple_New(nRecordNum);
	//PyObject* pyTupleBplunges = PyTuple_New(nRecordNum);
	//PyObject* pyTupleMethods = PyTuple_New(nRecordNum);
	//PyObject* pyTupleReferences = PyTuple_New(nRecordNum);
	//PyObject* pyTupleCommentinfos = PyTuple_New(nRecordNum);

	////url
	//PyTuple_SetItem(pyTupleURL, 0, StringToPy(url_add_collected_epimechanismresult));

	////sid
	//PyTuple_SetItem(pyTupleSID, 0, Py_BuildValue("i", nSId));

	//for (int idx = 0; idx < nRecordNum; idx++)
	//{
	//	//point
	//	PyObject* pyTuplePoint = PyTuple_New(3);
	//	PyTuple_SetItem(pyTuplePoint, 0, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._point._x));
	//	PyTuple_SetItem(pyTuplePoint, 1, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._point._y));
	//	PyTuple_SetItem(pyTuplePoint, 2, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._point._z));
	//	PyTuple_SetItem(pyTuplePoints, idx, pyTuplePoint);

	//	//
	//	PyTuple_SetItem(pyTupleIds, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._baseinfo._ID)));
	//	PyTuple_SetItem(pyTupleOccurrencedates, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._OccurrenceDate)));
	//	PyTuple_SetItem(pyTupleOccurrencetimes, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._OccurrenceDate)));
	//	PyTuple_SetItem(pyTupleLocationnames, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._LocationName)));
	//	PyTuple_SetItem(pyTupleLons, idx, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._Lon));
	//	PyTuple_SetItem(pyTupleLats, idx, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._Lat));
	//	PyTuple_SetItem(pyTupleMagnitudes, idx, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._Magnitude));
	//	PyTuple_SetItem(pyTupleUnits, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._Unit)));
	//	PyTuple_SetItem(pyTupleDepths, idx, PyFloat_FromDouble(vec_CollectedEpiMechanismResult[idx]._Depth));
	//	PyTuple_SetItem(pyTupleShazimuths, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._SHAzimuth));
	//	PyTuple_SetItem(pyTupleStressregimes, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._StressRegime));
	//	PyTuple_SetItem(pyTuplePlane1strikes, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane1Strike));
	//	PyTuple_SetItem(pyTuplePlane1dips, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane1Dip));
	//	PyTuple_SetItem(pyTuplePlane1slips, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane1Slip));		
	//	PyTuple_SetItem(pyTuplePlane2strikes, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane2Strike));
	//	PyTuple_SetItem(pyTuplePlane2dips, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane2Dip));		
	//	PyTuple_SetItem(pyTuplePlane2slips, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._Plane2Slip));
	//	PyTuple_SetItem(pyTuplePazimuths, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._PAzimuth));
	//	PyTuple_SetItem(pyTuplePplunges, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._PPlunge));
	//	PyTuple_SetItem(pyTupleTazimuths, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._TAzimuth));
	//	PyTuple_SetItem(pyTupleTplunges, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._TPlunge));
	//	PyTuple_SetItem(pyTupleBazimuths, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._BAzimuth));
	//	PyTuple_SetItem(pyTupleBplunges, idx, Py_BuildValue("i", vec_CollectedEpiMechanismResult[idx]._BPlunge));
	//	PyTuple_SetItem(pyTupleMethods, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._Method)));
	//	PyTuple_SetItem(pyTupleReferences, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._Reference)));		
	//	PyTuple_SetItem(pyTupleCommentinfos, idx, StringToPy(WstringToString(vec_CollectedEpiMechanismResult[idx]._baseinfo._CommentInfo)));
	//}

	//PyTuple_SetItem(args, 0, pyTupleURL);
	//PyTuple_SetItem(args, 1, pyTupleSID);
	//PyTuple_SetItem(args, 2, pyTuplePoints);
	//PyTuple_SetItem(args, 3, pyTupleIds);
	//PyTuple_SetItem(args, 4, pyTupleOccurrencedates);
	//PyTuple_SetItem(args, 5, pyTupleOccurrencetimes);
	//PyTuple_SetItem(args, 6, pyTupleLocationnames);
	//PyTuple_SetItem(args, 7, pyTupleLons);
	//PyTuple_SetItem(args, 8, pyTupleLats);
	//PyTuple_SetItem(args, 9, pyTupleMagnitudes);
	//PyTuple_SetItem(args, 10, pyTupleUnits);
	//PyTuple_SetItem(args, 11, pyTupleDepths);
	//PyTuple_SetItem(args, 12, pyTupleShazimuths);
	//PyTuple_SetItem(args, 13, pyTupleStressregimes);
	//PyTuple_SetItem(args, 14, pyTuplePlane1strikes);
	//PyTuple_SetItem(args, 15, pyTuplePlane1dips);
	//PyTuple_SetItem(args, 16, pyTuplePlane1slips);
	//PyTuple_SetItem(args, 17, pyTuplePlane2strikes);
	//PyTuple_SetItem(args, 18, pyTuplePlane2dips);
	//PyTuple_SetItem(args, 19, pyTuplePlane2slips);
	//PyTuple_SetItem(args, 20, pyTuplePazimuths);
	//PyTuple_SetItem(args, 21, pyTuplePplunges);
	//PyTuple_SetItem(args, 22, pyTupleTazimuths);
	//PyTuple_SetItem(args, 23, pyTupleTplunges);
	//PyTuple_SetItem(args, 24, pyTupleBazimuths);
	//PyTuple_SetItem(args, 25, pyTupleBplunges);
	//PyTuple_SetItem(args, 26, pyTupleMethods);
	//PyTuple_SetItem(args, 27, pyTupleReferences);
	//PyTuple_SetItem(args, 28, pyTupleCommentinfos);	

	//PyObject* pRet = PyEval_CallObject(pFunc, args);
    //const char* szRet = pRet->ob_type->tp_name;
    //if(*szRet == *err_URLError || *szRet == *err_HTTPError)
    //return false;

	//Py_Finalize();

	return true;
}
