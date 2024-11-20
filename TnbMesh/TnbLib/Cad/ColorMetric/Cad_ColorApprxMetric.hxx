#pragma once
#ifndef _Cad_ColorApprxMetric_Header
#define _Cad_ColorApprxMetric_Header

#include <Mesh2d_ElementFwd.hxx>
#include <Mesh_Module.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>
#include <Global_Handle.hxx>

#include <memory>
#include <vector>

// Forward Declarations [1/1/2022 Amir]
class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [1/1/2022 Amir]
	class Cad_MetricCalculator;

	struct Cad_ColorApprxMetricCache
	{

		mutable std::shared_ptr<Mesh2d_Element> theStart_;
	};

	class Cad_ColorApprxMetric
		: public Global_Done
		, public Cad_ColorApprxMetricCache
	{

		/*Private Data*/


		// inputs [1/1/2022 Amir]

		Handle(Geom_Surface) theGeometry_;

		std::shared_ptr<Entity2d_Triangulation> theApproximation_;
		std::shared_ptr<Cad_MetricCalculator> theCalculator_;

		Standard_Real theCriterion_;
		Standard_Real theMaxDet_;

		// output results [1/1/2022 Amir]

		std::vector<std::pair<std::shared_ptr<Mesh2d_Element>, Standard_Integer>> theElements_;
	

	public:

		static TnbMesh_EXPORT const Standard_Real DEFAULT_CRITERION;

		// default constructor [1/1/2022 Amir]

		Cad_ColorApprxMetric()
			: theCriterion_(DEFAULT_CRITERION)
			, theMaxDet_(1.0)
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
			, theCriterion_(DEFAULT_CRITERION)
			, theMaxDet_(1.0)
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

		auto MaxDet() const
		{
			return theMaxDet_;
		}

		TnbMesh_EXPORT Standard_Integer NbElements() const;
		TnbMesh_EXPORT Standard_Integer Value(const Standard_Integer theIndex) const;
		TnbMesh_EXPORT Standard_Integer Value(const Pnt2d& theCoord) const;

		TnbMesh_EXPORT void Perform();

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

		void SetMaxDet(const Standard_Real theDet)
		{
			theMaxDet_ = theDet;
		}

		static TnbMesh_EXPORT Standard_Real 
			CalcCriterion
			(
				const Standard_Real theMaxDet
			);

		static TnbMesh_EXPORT void Check
		(
			const Entity2d_Polygon&,
			const Cad_ColorApprxMetric&
		);
	};
}

#endif // !_Cad_ColorApprxMetric_Header
