#pragma once
#ifndef _Pln_Segment_Header
#define _Pln_Segment_Header

#include <Pln_Edge.hxx>

namespace tnbLib
{

	class Pln_Segment
		: public Pln_Edge
	{

		friend class Cad2d_MergeCurves;

		/*Private Data*/

		std::shared_ptr<Pln_Vertex> theVtx0_;
		std::shared_ptr<Pln_Vertex> theVtx1_;


		// private functions and operators [3/23/2022 Amir]

		auto& Vtx0Ref()
		{
			return theVtx0_;
		}

		auto& Vtx1Ref()
		{
			return theVtx1_;
		}

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	public:

		// default constructor [3/23/2022 Amir]

		Pln_Segment()
		{}

		// constructors [3/23/2022 Amir]

		Pln_Segment
		(
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(Sense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		Pln_Segment
		(
			std::shared_ptr<Pln_Vertex>&& theVtx0,
			std::shared_ptr<Pln_Vertex>&& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(Sense)
			, theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
		{}

		Pln_Segment
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, Sense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		Pln_Segment
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Pln_Vertex>&& theVtx0,
			std::shared_ptr<Pln_Vertex>&& theVtx1,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, Sense)
			, theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
		{}

		Pln_Segment
		(
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theCurve, Sense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		Pln_Segment
		(
			std::shared_ptr<Pln_Vertex>&& theVtx0,
			std::shared_ptr<Pln_Vertex>&& theVtx1,
			std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(std::move(theCurve), Sense)
			, theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
		{}

		Pln_Segment
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Vertex>& theVtx0,
			const std::shared_ptr<Pln_Vertex>& theVtx1,
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, theCurve, Sense)
			, theVtx0_(theVtx0)
			, theVtx1_(theVtx1)
		{}

		Pln_Segment
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Pln_Vertex>&& theVtx0,
			std::shared_ptr<Pln_Vertex>&& theVtx1,
			std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean Sense = Standard_True
		)
			: Pln_Edge(theIndex, theName, std::move(theCurve), Sense)
			, theVtx0_(std::move(theVtx0))
			, theVtx1_(std::move(theVtx1))
		{}

		// override functions and operators [3/23/2022 Amir]

		Standard_Boolean IsOrphan() const override;

		Standard_Boolean IsSegment() const override
		{
			return Standard_True;
		}

		// public functions and operators [3/23/2022 Amir]

		const auto& Vtx0() const
		{
			return theVtx0_;
		}

		const auto& Vtx1() const
		{
			return theVtx1_;
		}

	};
}

#endif // !_Pln_Segment_Header
