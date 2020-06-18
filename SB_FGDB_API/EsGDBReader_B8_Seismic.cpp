#include <windows.h>
#include "EsGDBReader.h"
#include "EsSBData_B8_Seismic.h"


bool EsGDBReader::EsGetEpiMechanismResult(vector<_EPIMECHANISMRESULT>& vec_EpiMechanismResult)
{
	const string strTableName = "EpiMechanismResult";

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
		_EPIMECHANISMRESULT _EpiMechanismResult;
		obRow.GetOID(_EpiMechanismResult._baseinfo._OBJECTID);	

		PointShapeBuffer obPoint;
		obRow.GetGeometry(obPoint);

		fgdbError hr;
		Point* point;
		if((hr = obPoint.GetPoint(point)) == S_OK)
		{
			_EpiMechanismResult._point._x = point->x;
			_EpiMechanismResult._point._y = point->y;
		}

		obRow.GetString(L"ID", _EpiMechanismResult._baseinfo._ID);
		obRow.GetString(L"ProjectID", _EpiMechanismResult._ProjectID);
		obRow.GetString(L"OccurrenceDate", _EpiMechanismResult._OccurrenceDate);
		obRow.GetString(L"OccurrenceTime", _EpiMechanismResult._OccurrenceTime);
		obRow.GetString(L"LocationName", _EpiMechanismResult._LocationName);
		obRow.GetDouble(L"Lon", _EpiMechanismResult._Lon);
		obRow.GetDouble(L"Lat", _EpiMechanismResult._Lat);
		obRow.GetDouble(L"Magnitude", _EpiMechanismResult._Magnitude);
		obRow.GetString(L"Unit", _EpiMechanismResult._Unit);
		obRow.GetDouble(L"Depth", _EpiMechanismResult._Depth);
		obRow.GetInteger(L"SHAzimuth", _EpiMechanismResult._SHAzimuth);
		obRow.GetInteger(L"StressRegime", _EpiMechanismResult._StressRegime);	
		obRow.GetInteger(L"Plane1Strike", _EpiMechanismResult._Plane1Strike);
		obRow.GetInteger(L"Plane1Dip", _EpiMechanismResult._Plane1Dip);
		obRow.GetInteger(L"Plane1Slip", _EpiMechanismResult._Plane1Slip);
		obRow.GetInteger(L"Plane2Strike", _EpiMechanismResult._Plane2Strike);
		obRow.GetInteger(L"Plane2Dip", _EpiMechanismResult._Plane2Dip);
		obRow.GetInteger(L"Plane2Slip", _EpiMechanismResult._Plane2Slip);
		obRow.GetInteger(L"PAzimuth", _EpiMechanismResult._PAzimuth);
		obRow.GetInteger(L"PPlunge", _EpiMechanismResult._PPlunge);
		obRow.GetInteger(L"TAzimuth", _EpiMechanismResult._TAzimuth);
		obRow.GetInteger(L"TPlunge", _EpiMechanismResult._TPlunge);
		obRow.GetInteger(L"BAzimuth", _EpiMechanismResult._BAzimuth);
		obRow.GetInteger(L"BPlunge", _EpiMechanismResult._BPlunge);
		obRow.GetString(L"Method", _EpiMechanismResult._Method);
		obRow.GetString(L"Reference", _EpiMechanismResult._Reference);
		obRow.GetString(L"CommentInfo", _EpiMechanismResult._baseinfo._CommentInfo);

		vec_EpiMechanismResult.push_back(_EpiMechanismResult);
	}

	obRows.Close();

	return true;
}

bool EsGDBReader::EsGetRelocationISCatalog(vector<_RELOCATIONISCATALOG>& vec_RelocationISCatalog)
{
	const string strTableName = "RelocationISCatalog";

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
		_RELOCATIONISCATALOG _RelocationISCatalog;
		obRow.GetOID(_RelocationISCatalog._baseinfo._OBJECTID);	

		PointShapeBuffer obPoint;
		obRow.GetGeometry(obPoint);

		fgdbError hr;
		Point* point;
		if((hr = obPoint.GetPoint(point)) == S_OK)
		{
			_RelocationISCatalog._point._x = point->x;
			_RelocationISCatalog._point._y = point->y;
		}

		obRow.GetString(L"ID", _RelocationISCatalog._baseinfo._ID);
		obRow.GetString(L"ProjectID", _RelocationISCatalog._ProjectID);
		obRow.GetString(L"OccurrenceDate", _RelocationISCatalog._OccurrenceDate);
		obRow.GetString(L"OccurrenceTime", _RelocationISCatalog._OccurrenceTime);
		obRow.GetString(L"LocationName", _RelocationISCatalog._LocationName);
		obRow.GetDouble(L"Lon", _RelocationISCatalog._Lon);
		obRow.GetDouble(L"Lat", _RelocationISCatalog._Lat);
		obRow.GetDouble(L"MagnitudeMl", _RelocationISCatalog._MagnitudeMl);
		obRow.GetString(L"MagnitudeMs", _RelocationISCatalog._MagnitudeMs);
		obRow.GetDouble(L"Depth", _RelocationISCatalog._Depth);
		obRow.GetInteger(L"Epicenter", _RelocationISCatalog._Epicenter);
		obRow.GetDouble(L"LastAngle", _RelocationISCatalog._LastAngle);
		obRow.GetString(L"CommentInfo", _RelocationISCatalog._baseinfo._CommentInfo);

		vec_RelocationISCatalog.push_back(_RelocationISCatalog);
	}

	obRows.Close();

	return true;
}