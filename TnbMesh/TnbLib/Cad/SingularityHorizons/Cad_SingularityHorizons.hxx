#pragma once
#ifndef _Cad_SingularityHorizons_Header
#define _Cad_SingularityHorizons_Header

#include <Global_Done.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Geo2d_PolygonGraphFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
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
		Standard_Real theMaxDet_;
		
		// output results [1/2/2022 Amir]

		std::shared_ptr<Geo2d_PolygonGraph> theHorizons_;

	public:

		static TnbMesh_EXPORT const Standard_Real DEFAULT_DEGEN_CRITERION;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_MERGING_TOLERANCE;

		// default constructor [1/2/2022 Amir]

		Cad_SingularityHorizons()
			: theCriterion_(DEFAULT_DEGEN_CRITERION)
			, theMergeTolerance_(DEFAULT_MERGING_TOLERANCE)
			, theMaxDet_(0)
		{}

		// constructors [1/2/2022 Amir]

		Cad_SingularityHorizons
		(
			const Handle(Geom_Surface)& theGeom,
			const std::shared_ptr<Entity2d_Triangulation>& theApprox,
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator,
			const Standard_Real theMaxDet
		)
			: theGeometry_(theGeom)
			, theApproximation_(theApprox)
			, theCalculator_(theCalculator)
			, theCriterion_(DEFAULT_DEGEN_CRITERION)
			, theMergeTolerance_(DEFAULT_MERGING_TOLERANCE)
			, theMaxDet_(theMaxDet)
		{}

		// public functions and operators [1/2/2022 Amir]

		TnbMesh_EXPORT Standard_Boolean HasHorizon() const;
		TnbMesh_EXPORT Standard_Integer NbHorizons() const;

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

		auto MaxDet() const
		{
			return theMaxDet_;
		}

		TnbMesh_EXPORT void Perform();

		void LoadGeometry(const Handle(Geom_Surface)& theGeom)
		{
			theGeometry_ = theGeom;
		}

		void LoadApproximation(const std::shared_ptr<Entity2d_Triangulation>& theApprox)
		{
			theApproximation_ = theApprox;
		}

		void LoadMetricCalculato(const std::shared_ptr<Cad_MetricCalculator>& theCalculator)
		{
			theCalculator_ = theCalculator;
		}

		void SetDegeneracyCriterion(const Standard_Real x)
		{
			theCriterion_ = x;
		}

		void SetMergingTolerance(const Standard_Real x)
		{
			theMergeTolerance_ = x;
		}

		void SetMaxDet(const Standard_Real theMax)
		{
			theMaxDet_ = theMax;
		}

		static TnbMesh_EXPORT Entity2d_Box
			RetrieveDomain
			(
				const Cad_SingularityHorizons&
			);

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Entity2d_Polygon>> 
			RetrieveHorizons
			(
				const Cad_SingularityHorizons&
			);
	};
}

#endif // !_Cad_SingularityHorizons_Header
