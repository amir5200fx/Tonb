#pragma once
#ifndef _Cad_MetricCalculator_Std_Header
#define _Cad_MetricCalculator_Std_Header

#include <Cad_MetricCalculator.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		class MetricCalculator_Std
			: public Cad_MetricCalculator
		{

			/*Private Data*/

		public:

			// default constructor [12/31/2021 Amir]

			MetricCalculator_Std()
			{}

			// constructors [12/31/2021 Amir]


			// public functions and operators [12/31/2021 Amir]


			// override functions and operators [12/31/2021 Amir]

			TnbCad_EXPORT Entity2d_Metric1 CalcMetric(const Pnt2d&, const Handle(Geom_Surface)&) const override;
			TnbCad_EXPORT Entity2d_Metric1 CalcMetric(const Standard_Real, const Standard_Real, const Handle(Geom_Surface)&) const override;
		};
	}
}

#endif // !_Cad_MetricCalculator_Std_Header
