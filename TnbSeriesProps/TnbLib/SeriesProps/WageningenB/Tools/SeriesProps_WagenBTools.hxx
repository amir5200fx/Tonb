#pragma once
#ifndef _SeriesProps_WagenBTools_Header
#define _SeriesProps_WagenBTools_Header

#include <Standard_TypeDef.hxx>
#include <SeriesProps_Module.hxx>

namespace tnbLib
{

	// Forward Declarations [1/11/2022 Amir]
	class Pnt2d;
	class Global_Table;

	class SeriesProps_WagenBTools
	{

	public:

		static Standard_Real RetrieveLinearTabValue(const Standard_Real rPerR, const Standard_Real P, const Global_Table&);

		static TnbSeriesProps_EXPORT Standard_Real 
			Yface
			(
				const Standard_Real v1,
				const Standard_Real tMax,
				const Standard_Real tte,
				const Standard_Real tle,
				const Standard_Real p
			);

		static TnbSeriesProps_EXPORT Standard_Real
			Yback
			(
				const Standard_Real v1,
				const Standard_Real v2, 
				const Standard_Real tMax, 
				const Standard_Real tte,
				const Standard_Real tle,
				const Standard_Real p
			);

		static void Check(const Standard_Real rPerR, const Standard_Real P, const Global_Table&);
	};
}

#endif // !_SeriesProps_WagenBTools_Header
