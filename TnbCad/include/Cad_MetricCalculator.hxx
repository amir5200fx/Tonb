#pragma once
#ifndef _Cad_MetricCalculator_Header
#define _Cad_MetricCalculator_Header

#include <Standard_Handle.hxx>

#include <Cad_Module.hxx>

// Forward Declarations [12/31/2021 Amir]
class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [12/31/2021 Amir]
	class Entity2d_Metric1;
	class Pnt2d;

	class Cad_MetricCalculator
	{

		/*Private Data*/

	protected:

		// default constructor [12/31/2021 Amir]

		Cad_MetricCalculator()
		{}

		// constructors [12/31/2021 Amir]


	public:

		virtual ~Cad_MetricCalculator()
		{}

		// public functions and operators [12/31/2021 Amir]

		
		virtual Entity2d_Metric1 CalcMetric(const Pnt2d&, const Handle(Geom_Surface)&) const = 0;
		virtual Entity2d_Metric1 CalcMetric(const Standard_Real, const Standard_Real, const Handle(Geom_Surface)&) const = 0;

	};
}

#endif // !_Cad_MetricCalculator_Header
