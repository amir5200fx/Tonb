#pragma once
#ifndef _PlnOpert_IntsctCurveCurve_Info_Header
#define _PlnOpert_IntsctCurveCurve_Info_Header

#include <Cad2d_Module.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class PlnOpert_IntsctCurveCurve_Info
	{

		/*Private Data*/

		Standard_Real theTolerance_;

	public:

		static TnbCad2d_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		PlnOpert_IntsctCurveCurve_Info()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}

		//- Macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Tolerance)
	};
}

#endif // !_PlnOpert_IntsctCurveCurve_Info_Header
