#pragma once
#ifndef _Cad2d_EdgeEdgeIntersection_Header
#define _Cad2d_EdgeEdgeIntersection_Header

#include <Cad2d_EntityEntityIntersection.hxx>
#include <Global_AccessMethod.hxx>
#include <Cad2d_Module.hxx>

#include <memory>
#include <tuple>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Cad2d_IntsctEntity;
	class Cad2d_IntsctEntity_Segment;
	class Cad2d_VertexEdgeIntersection;

	class Cad2d_EdgeEdgeIntersection
		: public Cad2d_EntityEntityIntersection
	{

		/*Private Data*/

		std::shared_ptr<Pln_Edge> theEdge0_;
		std::shared_ptr<Pln_Edge> theEdge1_;

	public:

		TnbCad2d_EXPORT Cad2d_EdgeEdgeIntersection();

		TnbCad2d_EXPORT Cad2d_EdgeEdgeIntersection
		(
			const Standard_Integer theIndex
		);

		TnbCad2d_EXPORT Cad2d_EdgeEdgeIntersection
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		const auto& Edge0() const
		{
			return theEdge0_;
		}

		const auto& Edge1() const
		{
			return theEdge1_;
		}

		Standard_Boolean IsEdgeEdge() const override
		{
			return Standard_True;
		}

		void LoadEdge0
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		)
		{
			theEdge0_ = theEdge;
		}

		void LoadEdge1
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		)
		{
			theEdge1_ = theEdge;
		}

		TnbCad2d_EXPORT void Perform();

		static TnbCad2d_EXPORT std::tuple
			<
			std::shared_ptr<Cad2d_EdgeEdgeIntersection>,
			std::shared_ptr<Cad2d_EdgeEdgeIntersection>
			>
			ConvertFrom
			(
				const Cad2d_VertexEdgeIntersection& theAlg,
				const Standard_Real theTol
			);
	};
}

#endif // !_Cad2d_EdgeEdgeIntersection_Header
