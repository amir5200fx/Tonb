#pragma once
#ifndef _Pln_Segment_Header
#define _Pln_Segment_Header

#include <Pln_Edge.hxx>

namespace tnbLib
{

	// Forward Declarations [3/25/2022 Amir]
	class Pln_Tools;

	class Pln_Segment
		: public Pln_Edge
	{

		friend class Cad2d_MergeCurves;
		friend class Pln_Tools;

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

		TnbCad2d_EXPORT Standard_Boolean IsDangle() const override;
		TnbCad2d_EXPORT Standard_Boolean IsOrphan() const override;

		TnbCad2d_EXPORT edgePoint GetPoint(const std::shared_ptr<Pln_Vertex>& theVertex) const override;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Vertex> Vertex(const edgePoint) const;

		Standard_Boolean IsSegment() const override
		{
			return Standard_True;
		}

		TnbCad2d_EXPORT std::shared_ptr<Pln_Entity>
			Copy() const override;

		TnbCad2d_EXPORT void RetrieveEntitiesTo
		(
			std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
			const Pln_EntityType t
		) const override;

		TnbCad2d_EXPORT void Transform(const gp_Trsf2d& t) override;
		TnbCad2d_EXPORT void Reverse(const Standard_Boolean ApplyToMesh) override;

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

BOOST_CLASS_EXPORT_KEY(tnbLib::Pln_Segment);

#endif // !_Pln_Segment_Header
