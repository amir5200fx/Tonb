#pragma once
#ifndef _Cad_ApprxMetricCriterion_MinMax_Header
#define _Cad_ApprxMetricCriterion_MinMax_Header

#include <Cad_ApprxMetricCriterion.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		class ApprxMetricCriterion_MinMax
			: public Cad_ApprxMetricCriterion
		{

			/*Private Data*/

		public:

			// default constructor [12/26/2021 Amir]

			ApprxMetricCriterion_MinMax()
			{}


			// constructors [12/26/2021 Amir]

			ApprxMetricCriterion_MinMax
			(
				const Standard_Real theTol,
				const std::shared_ptr<Cad_MetricCalculator>& theCalculator
			)
				: Cad_ApprxMetricCriterion(theTol, theCalculator)
			{}

			// public functions and operators [12/26/2021 Amir]

			TnbCad_EXPORT Standard_Boolean Subdivide
			(
				const Entity2d_Box& theDomain,
				const std::shared_ptr<Geo2d_SamplePoints>& theSamples,
				const Handle(Geom_Surface)& theGeometry
			) const override;
		};
	}
}

#endif // !_Cad_ApprxMetricCriterion_MinMax_Header
