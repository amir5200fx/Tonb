#pragma once
#ifndef _TModel_Surface_Header
#define _TModel_Surface_Header

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <TModel_Entity.hxx>
#include <GModel_SurfaceGeometry.hxx>
#include <TModel_FaceOrientation.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class TModel_Wire;
	class TModel_Edge;
	class Entity2d_Metric1;

	class TModel_Surface
		: public TModel_Entity
		, public GModel_SurfaceGeometry
	{

		typedef std::shared_ptr<TModel_Wire> outer;
		typedef std::shared_ptr<std::vector<std::shared_ptr<TModel_Wire>>> inner;

		/*Private Data*/

		outer theOuter_;
		inner theInner_;

		Entity2d_Box theParaBoundingBox_;

		TModel_FaceOrientation theOrientation_;


		//- Private functions and operators

		TnbCad_EXPORT Entity2d_Box CalcParametricBoundingBox() const;

		//TnbCad_EXPORT Entity3d_Box CalcBoundingBox() const;


		TNB_SERIALIZATION(TnbCad_EXPORT);


	protected:


		//- default constructor

		TModel_Surface()
		{}

	public:


		// constructors

		TnbCad_EXPORT TModel_Surface
		(
			const std::shared_ptr<Cad_GeomSurface>& theGeometry,
			const outer& theOuter,
			const inner& theInner = nullptr
		);

		TnbCad_EXPORT TModel_Surface
		(
			std::shared_ptr<Cad_GeomSurface>&& theGeometry,
			outer&& theOuter,
			inner&& theInner
		);

		TnbCad_EXPORT TModel_Surface
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Cad_GeomSurface>& theGeometry,
			const outer& theOuter,
			const inner& theInner = nullptr
		);

		TnbCad_EXPORT TModel_Surface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Cad_GeomSurface>& theGeometry,
			const outer& theOuter,
			const inner& theInner = nullptr
		);


		//- public functions and operators

		TnbCad_EXPORT Standard_Integer NbHoles() const;

		TnbCad_EXPORT Standard_Boolean HasHole() const;

		TnbCad_EXPORT Standard_Boolean IsClamped() const;

		const auto& Outer() const
		{
			return theOuter_;
		}

		const auto& Inner() const
		{
			return theInner_;
		}

		const auto& ParaBoundingBox() const
		{
			return theParaBoundingBox_;
		}

		TnbCad_EXPORT std::vector<std::shared_ptr<TModel_Edge>>
			RetrieveEdges() const;

		TnbCad_EXPORT Entity2d_Metric1 MetricAt
			(
				const Pnt2d& theCoord
			) const;

		TnbCad_EXPORT Pnt3d Value
		(
			const Pnt2d& theCoord
		) const;

		TnbCad_EXPORT void ExportPlaneCurvesToPlt(OFstream& File) const;

		//- static functions and operators

		static Standard_Boolean
			IsLess
			(
				const std::shared_ptr<TModel_Surface>& theS0,
				const std::shared_ptr<TModel_Surface>& theS1
			)
		{
			Debug_Null_Pointer(theS0);
			Debug_Null_Pointer(theS1);

			return theS0->Index() < theS1->Index();
		}
	};
}


BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_Surface);

#endif // !_TModel_Surface_Header
