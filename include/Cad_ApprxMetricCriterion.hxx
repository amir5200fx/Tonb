#pragma once
#ifndef _Cad_ApproxMetricCriterion_Header
#define _Cad_ApproxMetricCriterion_Header

#include <Cad_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

#include <memory>

// Forward Declarations [12/26/2021 Amir]
class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [12/26/2021 Amir]
	class Geo2d_SamplePoints;
	class Cad_MetricCalculator;

	class Cad_ApprxMetricCriterion
	{

		/*Private Data*/

		Standard_Real theTolerance_;

		std::shared_ptr<Cad_MetricCalculator> theCalculator_;

	protected:

		// default constructor [12/26/2021 Amir]

		Cad_ApprxMetricCriterion()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}

		// constructors [12/26/2021 Amir]

		Cad_ApprxMetricCriterion
		(
			const Standard_Real theTol,
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator
		)
			: theTolerance_(theTol)
			, theCalculator_(theCalculator)
		{}

	public:


		static TnbCad_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// public functions and operators [12/26/2021 Amir]

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& MetricCalculator() const
		{
			return theCalculator_;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetMetricCalculator(const std::shared_ptr<Cad_MetricCalculator>& theCalculator)
		{
			theCalculator_ = theCalculator;
		}

		virtual Standard_Boolean Subdivide
		(
			const Entity2d_Box& theDomain,
			const std::shared_ptr<Geo2d_SamplePoints>& theSamples,
			const Handle(Geom_Surface)& theGeometry
		) const = 0;
	};
}

#endif // !_Cad_ApproxMetricCriterion_Header
