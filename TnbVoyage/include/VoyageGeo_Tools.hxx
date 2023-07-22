#pragma once
#ifndef _VoyageGeo_Tools_Header
#define _VoyageGeo_Tools_Header

#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/11/2023 Payvand]

	class VoyageGeo_SizeFun;
	class VoyageGeo_MetricFun;

	class VoyageGeo_Tools
	{

	public:

		static void CalcUnitLengthVector(const Pnt2d& theP0, Pnt2d& theP1, const std::shared_ptr<VoyageGeo_MetricFun>&, const Standard_Real theSize);

	};
}

#endif // !_VoyageGeo_Tools_Header
