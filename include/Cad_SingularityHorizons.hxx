#pragma once
#ifndef _Cad_SingularityHorizons_Header
#define _Cad_SingularityHorizons_Header

#include <Global_Done.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Geo2d_PolygonGraphFwd.hxx>
#include <Mesh_Module.hxx>

#include <Standard_Handle.hxx>

#include <vector>
#include <memory>

// Forward Declarations [1/2/2022 Amir]
class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [1/2/2022 Amir]
	class Cad_MetricCalculator;

	class Cad_SingularityHorizons
		: public Global_Done
	{

		/*Private Data*/

		// inputs [1/2/2022 Amir]
		
		Handle(Geom_Surface) theGeometry_;

		std::shared_ptr<Entity2d_Triangulation> theApproximation_;
		std::shared_ptr<Cad_MetricCalculator> theCalculator_;

		Standard_Real theCriterion_;
		Standard_Real theMergeTolerance_;
		
		// output results [1/2/2022 Amir]

		std::shared_ptr<Geo2d_PolygonGraph> theHorizons_;

	public:

		// default constructor [1/2/2022 Amir]

		Cad_SingularityHorizons()
		{}

		// constructors [1/2/2022 Amir]


		// public functions and operators [1/2/2022 Amir]

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

		const auto& Horizons() const
		{
			return theHorizons_;
		}

		auto Criterion() const
		{
			return theCriterion_;
		}

		auto MergingTolerance() const
		{
			return theMergeTolerance_;
		}

		TnbMesh_EXPORT void Perform();
	};
}

#endif // !_Cad_SingularityHorizons_Header
