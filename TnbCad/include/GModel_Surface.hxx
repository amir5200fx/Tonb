#pragma once
#ifndef _GModel_Surface_Header
#define _GModel_Surface_Header

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <GModel_Entity.hxx>
#include <GModel_SurfaceGeometry.hxx>
#include <TModel_FaceOrientation.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class GModel_Wire;
	class GModel_Edge;
	class Entity2d_Metric1;

	class GModel_Surface
		: public GModel_Entity
		, public GModel_SurfaceGeometry
	{

		typedef std::shared_ptr<GModel_Wire> outer;
		typedef std::shared_ptr<std::vector<std::shared_ptr<GModel_Wire>>> inner;

		/*Private Data*/

		outer theOuter_;
		inner theInner_;

		Entity2d_Box theParaBoundingBox_;

		TModel_FaceOrientation theOrientation_;


		//- Private functions and operators

		TnbCad_EXPORT Entity2d_Box CalcParametricBoundingBox() const;

	public:

		TnbCad_EXPORT GModel_Surface
		(
			const Handle(Geom_Surface)& theGeometry,
			const outer& theOuter,
			const inner& theInner = nullptr
		);

		TnbCad_EXPORT GModel_Surface
		(
			const Standard_Integer theIndex,
			const Handle(Geom_Surface)& theGeometry,
			const outer& theOuter,
			const inner& theInner = nullptr
		);

		TnbCad_EXPORT GModel_Surface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Surface)& theGeometry,
			const outer& theOuter,
			const inner& theInner = nullptr
		);

		TnbCad_EXPORT Standard_Integer NbHoles() const;

		TnbCad_EXPORT Standard_Boolean HasHole() const;

		const auto& Outer() const
		{
			return theOuter_;
		}

		const auto& Inner() const
		{
			return theInner_;
		}

		TnbCad_EXPORT Entity3d_Box CalcBoundingBox() const;

		const auto& ParaBoundingBox() const
		{
			return theParaBoundingBox_;
		}

		TnbCad_EXPORT std::vector<std::shared_ptr<GModel_Edge>>
			RetrieveEdges() const;

		TnbCad_EXPORT Entity2d_Metric1 MetricAt
		(
			const Pnt2d& theCoord
		) const;

		TnbCad_EXPORT Pnt3d Value
		(
			const Pnt2d& theCoord
		) const;

		//- static functions and operators

		static Standard_Boolean
			IsLess
			(
				const std::shared_ptr<GModel_Surface>& theS0,
				const std::shared_ptr<GModel_Surface>& theS1
			)
		{
			Debug_Null_Pointer(theS0);
			Debug_Null_Pointer(theS1);

			return theS0->Index() < theS1->Index();
		}
	};
}

#endif // !_GModel_Surface_Header
