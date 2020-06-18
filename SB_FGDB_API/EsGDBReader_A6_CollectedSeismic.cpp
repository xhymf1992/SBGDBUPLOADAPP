#include <windows.h>
#include "EsGDBReader.h"
#include "EsSBData_A6_CollectedSeismic.h"


bool EsGDBReader::EsGetCollectedEpiMechanismResult(vector<_COLLECTEDEPIMECHANISMRESULT>& vec_CollectedEpiMechanismResult)
{
	const string strTableName = "CollectedEpiMechanismResult";

	Table obTable;
	if(!EsTableOpen(strTableName, obTable))
	{
		return false;
	}

	EnumRows obRows;
	if(!EsTableSearchAll(obTable, obRows))
	{
		return false;
	}

	Row obRow;
	while (obRows.Next(obRow) == S_OK)
	{
		_COLLECTEDEPIMECHANISMRESULT _CollectedEpiMechanismResult;
		obRow.GetOID(_CollectedEpiMechanismResult._baseinfo._OBJECTID);	

		PointShapeBuffer obPoint;
		obRow.GetGeometry(obPoint);

		fgdbError hr;
		Point* point;
		if((hr = obPoint.GetPoint(point)) == S_OK)
		{
			_CollectedEpiMechanismResult._point._x = point->x;
			_CollectedEpiMechanismResult._point._y = point->y;
		}

		obRow.GetString(L"ID", _CollectedEpiMechanismResult._baseinfo._ID);
		obRow.GetString(L"OccurrenceDate", _CollectedEpiMechanismResult._OccurrenceDate);
		obRow.GetString(L"OccurrenceTime", _CollectedEpiMechanismResult._OccurrenceTime);
		obRow.GetString(L"LocationName", _CollectedEpiMechanismResult._LocationName);
		obRow.GetDouble(L"Lon", _CollectedEpiMechanismResult._Lon);
		obRow.GetDouble(L"Lat", _CollectedEpiMechanismResult._Lat);
		obRow.GetDouble(L"Magnitude", _CollectedEpiMechanismResult._Magnitude);
		obRow.GetString(L"Unit", _CollectedEpiMechanismResult._Unit);
		obRow.GetDouble(L"Depth", _CollectedEpiMechanismResult._Depth);
		obRow.GetInteger(L"SHAzimuth", _CollectedEpiMechanismResult._SHAzimuth);
		obRow.GetInteger(L"StressRegime", _CollectedEpiMechanismResult._StressRegime);	
		obRow.GetInteger(L"Plane1Strike", _CollectedEpiMechanismResult._Plane1Strike);
		obRow.GetInteger(L"Plane1Dip", _CollectedEpiMechanismResult._Plane1Dip);
		obRow.GetInteger(L"Plane1Slip", _CollectedEpiMechanismResult._Plane1Slip);
		obRow.GetInteger(L"Plane2Strike", _CollectedEpiMechanismResult._Plane2Strike);
		obRow.GetInteger(L"Plane2Dip", _CollectedEpiMechanismResult._Plane2Dip);
		obRow.GetInteger(L"Plane2Slip", _CollectedEpiMechanismResult._Plane2Slip);
		obRow.GetInteger(L"PAzimuth", _CollectedEpiMechanismResult._PAzimuth);
		obRow.GetInteger(L"PPlunge", _CollectedEpiMechanismResult._PPlunge);
		obRow.GetInteger(L"TAzimuth", _CollectedEpiMechanismResult._TAzimuth);
		obRow.GetInteger(L"TPlunge", _CollectedEpiMechanismResult._TPlunge);
		obRow.GetInteger(L"BAzimuth", _CollectedEpiMechanismResult._BAzimuth);
		obRow.GetInteger(L"BPlunge", _CollectedEpiMechanismResult._BPlunge);
		obRow.GetString(L"Method", _CollectedEpiMechanismResult._Method);
		obRow.GetString(L"Reference", _CollectedEpiMechanismResult._Reference);
		obRow.GetString(L"CommentInfo", _CollectedEpiMechanismResult._baseinfo._CommentInfo);

		vec_CollectedEpiMechanismResult.push_back(_CollectedEpiMechanismResult);
	}

	_COLLECTEDEPIMECHANISMRESULT _CollectedEpiMechanismResult;
	
	_CollectedEpiMechanismResult._point._x = 106.28;
	_CollectedEpiMechanismResult._point._y = 35.97;
	

	_CollectedEpiMechanismResult._baseinfo._ID = L"640400102#######3";
	_CollectedEpiMechanismResult._OccurrenceDate = L"19891102";
	_CollectedEpiMechanismResult._OccurrenceTime = L"NA";
	_CollectedEpiMechanismResult._LocationName = L"ÄþÏÄ¹ÌÔ­";
	_CollectedEpiMechanismResult._Lon = 106.28;
	_CollectedEpiMechanismResult._Lat = 35.97;
	_CollectedEpiMechanismResult._Magnitude = 5.0;
	_CollectedEpiMechanismResult._Unit = L"NA";
	_CollectedEpiMechanismResult._Depth = -9999.0;
	_CollectedEpiMechanismResult._SHAzimuth = -9999;
	_CollectedEpiMechanismResult._StressRegime	= 240021;
	_CollectedEpiMechanismResult._Plane1Strike = 188;
	_CollectedEpiMechanismResult._Plane1Dip = 70;
	_CollectedEpiMechanismResult._Plane1Slip = 173;
	_CollectedEpiMechanismResult._Plane2Strike = 280;
	_CollectedEpiMechanismResult._Plane2Dip = 83;
	_CollectedEpiMechanismResult._Plane2Slip = 20;
	_CollectedEpiMechanismResult._PAzimuth = 53;
	_CollectedEpiMechanismResult._PPlunge = 9;
	_CollectedEpiMechanismResult._TAzimuth = 146;
	_CollectedEpiMechanismResult._TPlunge = 19;
	_CollectedEpiMechanismResult._BAzimuth = 298;
	_CollectedEpiMechanismResult._BPlunge = 69;
	_CollectedEpiMechanismResult._Method = L"NA";
	_CollectedEpiMechanismResult._Reference = L"NA";
	_CollectedEpiMechanismResult._baseinfo._CommentInfo = L"NA";

	vec_CollectedEpiMechanismResult.push_back(_CollectedEpiMechanismResult);

	obRows.Close();

	return true;
}

bool EsGDBReader::EsGetCollectedRelocationISCatalog(vector<_COLLECTEDRELOCATIONISCATALOG>& vec_CollectedRelocationISCatalog)
{
	const string strTableName = "CollectedRelocationISCatalog";

	Table obTable;
	if(!EsTableOpen(strTableName, obTable))
	{
		return false;
	}

	EnumRows obRows;
	if(!EsTableSearchAll(obTable, obRows))
	{
		return false;
	}

	Row obRow;
	while (obRows.Next(obRow) == S_OK)
	{
		_COLLECTEDRELOCATIONISCATALOG _CollectedRelocationISCatalog;
		obRow.GetOID(_CollectedRelocationISCatalog._baseinfo._OBJECTID);	

		PointShapeBuffer obPoint;
		obRow.GetGeometry(obPoint);

		fgdbError hr;
		Point* point;
		if((hr = obPoint.GetPoint(point)) == S_OK)
		{
			_CollectedRelocationISCatalog._point._x = point->x;
			_CollectedRelocationISCatalog._point._y = point->y;
		}

		obRow.GetString(L"ID", _CollectedRelocationISCatalog._baseinfo._ID);
		obRow.GetString(L"OccurrenceDate", _CollectedRelocationISCatalog._OccurrenceDate);
		obRow.GetString(L"OccurrenceTime", _CollectedRelocationISCatalog._OccurrenceTime);
		obRow.GetString(L"LocationName", _CollectedRelocationISCatalog._LocationName);
		obRow.GetDouble(L"Lon", _CollectedRelocationISCatalog._Lon);
		obRow.GetDouble(L"Lat", _CollectedRelocationISCatalog._Lat);
		obRow.GetDouble(L"MagnitudeMl", _CollectedRelocationISCatalog._MagnitudeMl);
		obRow.GetString(L"MagnitudeMs", _CollectedRelocationISCatalog._MagnitudeMs);
		obRow.GetDouble(L"Depth", _CollectedRelocationISCatalog._Depth);
		obRow.GetInteger(L"Epicenter", _CollectedRelocationISCatalog._Epicenter);
		obRow.GetDouble(L"LastAngle", _CollectedRelocationISCatalog._LastAngle);
		obRow.GetString(L"CommentInfo", _CollectedRelocationISCatalog._baseinfo._CommentInfo);

		vec_CollectedRelocationISCatalog.push_back(_CollectedRelocationISCatalog);
	}

	obRows.Close();

	return true;
}