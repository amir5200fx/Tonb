#pragma once
#ifndef _VoyageGeo_MetricFun_Header
#define _VoyageGeo_MetricFun_Header

#include <Entity2d_Metric1.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	class VoyageGeo_MetricFun
	{

		/*Private Data*/

	protected:

		// default constructor [7/10/2023 Payvand]

		VoyageGeo_MetricFun()
		{}

		// constructors [7/10/2023 Payvand]


	public:

		// Public functions and operators [7/10/2023 Payvand]

		virtual Entity2d_Metric1 Value(const Pnt2d& theCoord) const = 0;

	};

}

#endif // !_VoyageGeo_MetricFun_Header
