#pragma once
#ifndef _Cad_MetricCalculator_SizeFun_Header
#define _Cad_MetricCalculator_SizeFun_Header

#include <Cad_MetricCalculator.hxx>

namespace tnbLib
{

	// Forward Declarations [1/1/2022 Amir]
	class Pnt3d;
	class Pnt2d;

	namespace cadLib
	{

		class MetricCalculator_SizeFun
			: public Cad_MetricCalculator
		{

			/*Private Data*/

			Standard_Real(*SizeFunction)(const Pnt3d&);

		public:

			// default constructor [1/1/2022 Amir]

			MetricCalculator_SizeFun()
			{}


			// constructors [1/1/2022 Amir]

			explicit MetricCalculator_SizeFun(Standard_Real(*sizeFun)(const Pnt3d&))
				: SizeFunction(sizeFun)
			{}

			// public functions and operators [1/1/2022 Amir]

			void SetSizeFunction(Standard_Real(*sizeFun)(const Pnt3d&))
			{
				SizeFunction = sizeFun;
			}

			// override functions and operators [1/1/2022 Amir]

			TnbCad_EXPORT Entity2d_Metric1 CalcMetric(const Pnt2d&, const Handle(Geom_Surface)&) const override;
			TnbCad_EXPORT Entity2d_Metric1 CalcMetric(const Standard_Real, const Standard_Real, const Handle(Geom_Surface)&) const override;
		};
	}
}

#endif // !_Cad_MetricCalculator_SizeFun_Header
