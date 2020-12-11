#pragma once
#ifndef _NModel_Surface_Header
#define _NModel_Surface_Header

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <NModel_Entity.hxx>
#include <NModel_SurfaceGeometry.hxx>
#include <NModel_SurfaceOrientation.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Vertex;
	class NModel_Wire;
	class NModel_Edge;
	class Entity2d_Metric1;

	class NModel_Surface
		: public NModel_Entity
		, public NModel_SurfaceGeometry
	{

		typedef std::shared_ptr<NModel_Wire> outer;
		typedef std::shared_ptr<std::vector<std::shared_ptr<NModel_Wire>>> inner;
		typedef std::vector<std::shared_ptr<NModel_Edge>> edgeList;

		/*Private Data*/

		outer theOuter_;
		inner theInner_;

		std::shared_ptr<edgeList> theEdges_;

		Entity2d_Box theParaBoundingBox_;
		Entity3d_Box theBoundingBox_;

		NModel_SurfaceOrientation theOrientation_;


		//- Private functions and operators

		Entity2d_Box CalcParametricBoundingBox() const;

		Entity3d_Box CalcBoundingBox() const;


	public:

		TnbCad_EXPORT NModel_Surface
		(
			const Handle(Geom_Surface)& theGeometry,
			const outer& theOuter,
			const inner& theInner = nullptr,
			const std::shared_ptr<edgeList>& theEdges = nullptr
		);

		TnbCad_EXPORT NModel_Surface
		(
			const Standard_Integer theIndex,
			const Handle(Geom_Surface)& theGeometry,
			const outer& theOuter,
			const inner& theInner = nullptr,
			const std::shared_ptr<edgeList>& theEdges = nullptr
		);

		TnbCad_EXPORT NModel_Surface
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Surface)& theGeometry,
			const outer& theOuter,
			const inner& theInner = nullptr,
			const std::shared_ptr<edgeList>& theEdges = nullptr
		);

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

		const auto& BoundingBox() const
		{
			return theBoundingBox_;
		}

		const auto& ParaBoundingBox() const
		{
			return theParaBoundingBox_;
		}

		TnbCad_EXPORT std::vector<std::shared_ptr<NModel_Edge>>
			RetrieveEdges() const;

		TnbCad_EXPORT std::vector<std::shared_ptr<NModel_Vertex>>
			RetrieveVertices();

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
				const std::shared_ptr<NModel_Surface>& theS0,
				const std::shared_ptr<NModel_Surface>& theS1
			)
		{
			Debug_Null_Pointer(theS0);
			Debug_Null_Pointer(theS1);

			return theS0->Index() < theS1->Index();
		}
	};
}

#endif // !_NModel_Surface_Header
