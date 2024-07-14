#pragma once
#ifndef _Cad_MetricCalculator_SizeFun_Header
#define _Cad_MetricCalculator_SizeFun_Header

#include <Cad_MetricCalculator.hxx>

#include <functional>
#include <Pnt3d.hxx>

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

		public:

			typedef std::function<Standard_Real(const Pnt3d&)> SizeFunction;

			/*Private Data*/

			SizeFunction theSizeFunction_;

		public:

			// default constructor [1/1/2022 Amir]

			MetricCalculator_SizeFun()
			{}


			// constructors [1/1/2022 Amir]

			explicit MetricCalculator_SizeFun(const SizeFunction& theSizeFunction)
				: theSizeFunction_(theSizeFunction)
			{}

			// public functions and operators [1/1/2022 Amir]

			void SetSizeFunction(const SizeFunction& theSizeFunction)
			{
				theSizeFunction_ = theSizeFunction;
			}

			// override functions and operators [1/1/2022 Amir]

			TnbCad_EXPORT Entity2d_Metric1 CalcMetric(const Pnt2d&, const Handle(Geom_Surface)&) const override;
			TnbCad_EXPORT Entity2d_Metric1 CalcMetric(const Standard_Real, const Standard_Real, const Handle(Geom_Surface)&) const override;
		};
	}
}

#endif // !_Cad_MetricCalculator_SizeFun_Header
