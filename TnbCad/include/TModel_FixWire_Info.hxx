#pragma once
#ifndef _TModel_FixWire_Info_Header
#define _TModel_FixWire_Info_Header

#include <Cad_Module.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class TModel_FixWire_Info
	{

		/*Private Data*/

		Standard_Real thePrecision_;
		Standard_Real theMaxTolerance_;
		Standard_Real theMinTolerance_;

		Standard_Real theTolerance_;

	public:

		static TnbCad_EXPORT const Standard_Real DEFAULT_PRECISION;
		static TnbCad_EXPORT const Standard_Real DEFAULT_MAX_TOLERANCE;
		static TnbCad_EXPORT const Standard_Real DEFAULT_MIN_TOLERANCE;
		static TnbCad_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		TModel_FixWire_Info()
			: thePrecision_(DEFAULT_PRECISION)
			, theMinTolerance_(DEFAULT_MIN_TOLERANCE)
			, theMaxTolerance_(DEFAULT_MAX_TOLERANCE)
			, theTolerance_(DEFAULT_TOLERANCE)
		{}

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Precision)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, MaxTolerance)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, MinTolerance)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Tolerance)
	};
}

#endif // !_TModel_FixWire_Info_Header
