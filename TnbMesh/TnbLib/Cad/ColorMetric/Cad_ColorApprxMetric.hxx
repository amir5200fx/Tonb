#pragma once
#ifndef _Cad_ColorApprxMetric_Header
#define _Cad_ColorApprxMetric_Header

#include <Standard_Handle.hxx>

#include <Global_Done.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Mesh2d_ElementFwd.hxx>

#include <memory>
#include <vector>

// Forward Declarations [1/1/2022 Amir]
class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [1/1/2022 Amir]
	class Cad_MetricCalculator;

	class Cad_ColorApprxMetric
		: public Global_Done
	{

		/*Private Data*/


		// inputs [1/1/2022 Amir]

		Handle(Geom_Surface) theGeometry_;

		std::shared_ptr<Entity2d_Triangulation> theApproximation_;
		std::shared_ptr<Cad_MetricCalculator> theCalculator_;

		Standard_Real theCriterion_;

		// output results [1/1/2022 Amir]

		std::vector<std::pair<std::shared_ptr<Mesh2d_Element>, Standard_Integer>> theElements_;

	public:

		static const Standard_Real DEFAULT_CRITERION;

		// default constructor [1/1/2022 Amir]

		Cad_ColorApprxMetric()
		{}

		// constructors [1/1/2022 Amir]

		Cad_ColorApprxMetric
		(
			const Handle(Geom_Surface)& theGeometry,
			const std::shared_ptr<Entity2d_Triangulation>& theApprox,
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator
		)
			: theGeometry_(theGeometry)
			, theApproximation_(theApprox)
			, theCalculator_(theCalculator)
		{}

		// public functions and operators [1/1/2022 Amir]

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		const auto& Approximation() const
		{
			return theApproximation_;
		}

		const auto& MetricCalculator() const
		{
			return theCalculator_;
		}

		const auto& Elements() const
		{
			return theElements_;
		}

		auto Criterion() const
		{
			return theCriterion_;
		}

		void Perform();

		void LoadGeoemtry(const Handle(Geom_Surface)& theGeometry)
		{
			theGeometry_ = theGeometry;
		}

		void LoadApproximation(const std::shared_ptr<Entity2d_Triangulation>& theApprox)
		{
			theApproximation_ = theApprox;
		}

		void LoadMetricCalculator(const std::shared_ptr<Cad_MetricCalculator>& theCalculator)
		{
			theCalculator_ = theCalculator;
		}

		void SetCriterion(const Standard_Real theCrit)
		{
			theCriterion_ = theCrit;
		}
	};
}

#endif // !_Cad_ColorApprxMetric_Header
