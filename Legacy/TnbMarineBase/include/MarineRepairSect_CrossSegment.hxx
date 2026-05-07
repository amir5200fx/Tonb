#pragma once
#ifndef _MarineRepairSect_CrossSegment_Header
#define _MarineRepairSect_CrossSegment_Header

#include <MarineRepairSect_Segment.hxx>

namespace tnbLib
{

	class MarineRepairSect_CrossSegment
		: public MarineRepairSect_Segment
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<MarineRepairSect_Segment>(*this);
		}


		//- default constructor

		MarineRepairSect_CrossSegment()
		{}

	public:


		//- constructors

		MarineRepairSect_CrossSegment(const std::shared_ptr<Cad2d_RemoveNonManifold::Segment>& theSegment)
			: MarineRepairSect_Segment(theSegment)
		{}

		MarineRepairSect_CrossSegment(std::shared_ptr<Cad2d_RemoveNonManifold::Segment>&& theSegment)
			: MarineRepairSect_Segment(std::move(theSegment))
		{}

		MarineRepairSect_CrossSegment
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Cad2d_RemoveNonManifold::Segment>& theSegment
		)
			: MarineRepairSect_Segment(theIndex, theSegment)
		{}

		MarineRepairSect_CrossSegment
		(
			const Standard_Integer theIndex,
			std::shared_ptr<Cad2d_RemoveNonManifold::Segment>&& theSegment
		)
			: MarineRepairSect_Segment(theIndex, std::move(theSegment))
		{}


		//- public functions and operators

		Standard_Boolean IsCrossed() const override
		{
			return Standard_True;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::MarineRepairSect_CrossSegment);

#endif // !_MarineRepairSect_CrossSegment_Header
