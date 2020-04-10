#pragma once
#ifndef _Cad2d_IntsctEntity_Segment_Header
#define _Cad2d_IntsctEntity_Segment_Header

#include <Cad2d_IntsctEntity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_Curve;

	class Cad2d_IntsctEntity_Segment
		: public Cad2d_IntsctEntity
	{

		/*Private Data*/

		std::shared_ptr<Pln_Edge> theEdge_;

	public:

		Cad2d_IntsctEntity_Segment()
		{}

		Cad2d_IntsctEntity_Segment(const Standard_Integer theIndex);

		Cad2d_IntsctEntity_Segment(const Standard_Integer theIndex, const word& theName);


		const auto& ParentEdge() const
		{
			return theEdge_;
		}

		virtual Standard_Boolean IsTangential() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsOrthogonal() const
		{
			return Standard_False;
		}

		virtual Standard_Real CharParameter() const = 0;

		Standard_Boolean IsSegment() const override
		{
			return Standard_True;
		}

		void SetParentEdge
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		)
		{
			theEdge_ = theEdge;
		}

		static Standard_Boolean
			CompareEntities
			(
				const std::shared_ptr<Cad2d_IntsctEntity_Segment>& theEntity0,
				const std::shared_ptr<Cad2d_IntsctEntity_Segment>& theEntity1
			);

		static void
			SortEntities
			(
				std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>>& theEntities
			);

		static std::vector<std::shared_ptr<Pln_Curve>>
			SubdivideEdge
			(
				const std::shared_ptr<Pln_Edge>& theEdge,
				const std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>>& theEntities,
				const Standard_Real theTol
			);
	};
}

#endif // !_Cad2d_IntsctEntity_Segment_Header
