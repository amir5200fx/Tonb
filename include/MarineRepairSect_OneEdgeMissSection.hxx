#pragma once
#ifndef _MarineRepairSect_OneEdgeMissSection_Header
#define _MarineRepairSect_OneEdgeMissSection_Header

#include <MarineRepairSect_Section.hxx>

namespace tnbLib
{

	// Forward Declarations
	class MarineRepairSect_CrossSegment;

	class MarineRepairSect_OneEdgeMissSection
		: public MarineRepairSect_Section
	{

		/*Private Data*/

		std::shared_ptr<MarineRepairSect_CrossSegment> theSegment_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMarine_EXPORT);

	public:

		//- default constructor

		MarineRepairSect_OneEdgeMissSection()
		{}


		//- constructors

		MarineRepairSect_OneEdgeMissSection
		(
			const std::shared_ptr<MarineRepairSect_CrossSegment>& theSegment
		)
			: theSegment_(theSegment)
		{}

		MarineRepairSect_OneEdgeMissSection
		(
			std::shared_ptr<MarineRepairSect_CrossSegment>&& theSegment
		)
			: theSegment_(std::move(theSegment))
		{}

		MarineRepairSect_OneEdgeMissSection
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<MarineRepairSect_CrossSegment>& theSegment
		)
			: MarineRepairSect_Section(theIndex, theName)
			, theSegment_(theSegment)
		{}

		MarineRepairSect_OneEdgeMissSection
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			std::shared_ptr<MarineRepairSect_CrossSegment>&& theSegment
		)
			: MarineRepairSect_Section(theIndex, theName)
			, theSegment_(std::move(theSegment))
		{}


		//- public functions and operators

		const auto& Segment() const
		{
			return theSegment_;
		}

		TnbMarine_EXPORT std::vector<std::shared_ptr<Pln_Curve>> FillingCurves() const override;


		void LoadSegment(const std::shared_ptr<MarineRepairSect_CrossSegment>& theSegment)
		{
			theSegment_ = theSegment;
		}

		void LoadSegment(std::shared_ptr<MarineRepairSect_CrossSegment>&& theSegment)
		{
			theSegment_ = std::move(theSegment);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::MarineRepairSect_OneEdgeMissSection);

#endif // !_MarineRepairSect_OneEdgeMissSection_Header
