#pragma once
#ifndef _Cad_CurveTools_Header
#define _Cad_CurveTools_Header

#include <Cad_Module.hxx>

#include <Standard_Handle.hxx>

class Geom_Curve;

#include <vector>

namespace tnbLib
{

	// Forward Declarations [5/14/2023 Payvand]
	class Pnt3d;

	class Cad_CurveTools
	{

	public:

		static TnbCad_EXPORT Handle(Geom_Curve) 
			Interpolation
			(
				const std::vector<Pnt3d>& theQ,
				const Standard_Boolean thePeriodic = Standard_False,
				const Standard_Real theTol = 1.0E-6
			);

	};

}

#endif // !_Cad_CurveTools_Header
