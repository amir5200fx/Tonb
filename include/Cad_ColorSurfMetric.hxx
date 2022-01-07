#pragma once
#ifndef _Cad_ColorSurfMetric_Header
#define _Cad_ColorSurfMetric_Header

#include <Global_Done.hxx>
#include <Entity2d_BoxFwd.hxx>

#include <Standard_Handle.hxx>

#include <memory>

// Forward Declarations [12/31/2021 Amir]
class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [12/31/2021 Amir]
	class Entity2d_MetricMeshValue;
	class Cad_MetricCalculator;

	class Cad_ColorSurfMetric
		: public Global_Done
	{

		/*Private Data*/


		// input data [12/31/2021 Amir]

		Handle(Geom_Surface) theGeometry_;

		std::shared_ptr<Entity2d_MetricMeshValue> theMetrics_;
		std::shared_ptr<Cad_MetricCalculator> theCalculator_;

		// output results [12/31/2021 Amir]



	public:

		// default constructor [12/31/2021 Amir]

		Cad_ColorSurfMetric()
		{}

		// constructors [12/31/2021 Amir]

		Cad_ColorSurfMetric
		(
			const Handle(Geom_Surface)& theGeometry, 
			const std::shared_ptr<Entity2d_MetricMeshValue>& theMetrics,
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator
		)
			: theGeometry_(theGeometry)
			, theMetrics_(theMetrics)
			, theCalculator_(theCalculator)
		{}


		// public functions and operators [12/31/2021 Amir]

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		const auto& Metrics() const
		{
			return theMetrics_;
		}

		const auto& Calculator() const
		{
			return theCalculator_;
		}

		void Perform();

		void LoadGeometry(const Handle(Geom_Surface)& theGeom)
		{
			theGeometry_ = theGeom;
		}

		void LoadMetrics(const std::shared_ptr<Entity2d_MetricMeshValue>& theMetrics)
		{
			theMetrics_ = theMetrics;
		}

		void SetCalculator(const std::shared_ptr<Cad_MetricCalculator>& theCalculator)
		{
			theCalculator_ = theCalculator;
		}

		void SetCalculator(std::shared_ptr<Cad_MetricCalculator>&& theCalculator)
		{
			theCalculator_ = std::move(theCalculator);
		}
	};
}

#endif // !_Cad_ColorSurfMetric_Header
