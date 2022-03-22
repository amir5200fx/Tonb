#pragma once
#ifndef _Cad2d_VertexEdgeIntersection_Header
#define _Cad2d_VertexEdgeIntersection_Header

#include <Cad2d_EntityEntityIntersection.hxx>
#include <Global_AccessMethod.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;
	class Pln_Edge;
	class Cad2d_IntsctEntity_Point;
	class Cad2d_IntsctEntity_Segment;

	class Cad2d_VertexEdgeIntersection
		: public Cad2d_EntityEntityIntersection
	{

		/*Private Data*/

		std::shared_ptr<Pln_Vertex> theVtx_;
		std::shared_ptr<Pln_Edge> theEdge_;

	public:

		//- default constructor

		Cad2d_VertexEdgeIntersection()
		{}


		//- constructors

		Cad2d_VertexEdgeIntersection
		(
			const std::shared_ptr<Pln_Vertex>& theVtx,
			const std::shared_ptr<Pln_Edge>& theCurve
		)
			: theVtx_(theVtx)
			, theEdge_(theCurve)
		{}

		// override functions and operators [3/19/2022 Amir]

		Standard_Boolean IsVertexEdge() const override
		{
			return Standard_True;
		}

		//- public functions and operators

		const auto& Vtx() const
		{
			return theVtx_;
		}

		const auto& Edge() const
		{
			return theEdge_;
		}

		void SetVertex(const std::shared_ptr<Pln_Vertex>& theVtx)
		{
			theVtx_ = theVtx;
		}

		void SetEdge(const std::shared_ptr<Pln_Edge>& theEdge)
		{
			theEdge_ = theEdge;
		}

		TnbCad2d_EXPORT std::shared_ptr<Cad2d_VertexEdgeIntersection>
			operator()
			(
				const std::shared_ptr<Pln_Vertex>& theVtx, 
				const std::shared_ptr<Pln_Edge>& theEdge, 
				const Standard_Real theTol
				) const;

		// static functions and operators [2/4/2022 Amir]

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_VertexEdgeIntersection> 
			Intersect
			(
				const std::shared_ptr<Pln_Vertex>& theVtx,
				const std::shared_ptr<Pln_Edge>& theEdge,
				const Standard_Real theTol
			);

		//- Macros

	};
}

#endif // !_Cad2d_VertexEdgeIntersection_Header
