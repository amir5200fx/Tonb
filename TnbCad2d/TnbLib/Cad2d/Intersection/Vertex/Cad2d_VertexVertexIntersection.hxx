#pragma once
#ifndef _Cad2d_VertexVertexIntersection_Header
#define _Cad2d_VertexVertexIntersection_Header

#include <Cad2d_EntityEntityIntersection.hxx>
#include <Global_AccessMethod.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/27/2022 Amir]
	class Pln_Vertex;

	class Cad2d_VertexVertexIntersection
		: public Cad2d_EntityEntityIntersection
	{

		/*Private Data*/

		std::shared_ptr<Pln_Vertex> theVtx0_;
		std::shared_ptr<Pln_Vertex> theVtx1_;

	public:

		// default constructor [1/27/2022 Amir]

		Cad2d_VertexVertexIntersection()
		{}

		// constructors [1/27/2022 Amir]

		Cad2d_VertexVertexIntersection
		(
			const std::shared_ptr<Pln_Vertex>& theVtx0, 
			const std::shared_ptr<Pln_Vertex>& theVtx1
		)
			: theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		Cad2d_VertexVertexIntersection
		(
			std::shared_ptr<Pln_Vertex>&& theVtx0,
			std::shared_ptr<Pln_Vertex>&& theVtx1
		)
			: theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
		{}


		// override functions and operators [1/27/2022 Amir]

		Standard_Boolean IsVertexVertex() const override
		{
			return Standard_True;
		}

		// public functions and operators [1/27/2022 Amir]

		const auto& Vtx0() const
		{
			return theVtx0_;
		}

		const auto& Vtx1() const
		{
			return theVtx1_;
		}

		TnbCad2d_EXPORT std::shared_ptr<Cad2d_VertexVertexIntersection> 
			operator()
			(
				const std::shared_ptr<Pln_Vertex>& theVtx0, 
				const std::shared_ptr<Pln_Vertex>& theVtx1,
				const Standard_Real theTol
				) const;

		// static functions and operators [2/4/2022 Amir]

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_VertexVertexIntersection> 
			Intersect
			(
				const std::shared_ptr<Pln_Vertex>& theVtx0,
				const std::shared_ptr<Pln_Vertex>& theVtx1, 
				const Standard_Real theTol
			);
	};
}

#endif // !_Cad2d_VertexVertexIntersection_Header
