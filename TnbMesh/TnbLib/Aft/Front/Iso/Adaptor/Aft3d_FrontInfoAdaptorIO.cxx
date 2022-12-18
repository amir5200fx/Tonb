#include <Aft3d_FrontInfoAdaptor.hxx>

#include <Aft3d_Facet.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_ElementTraits.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Aft3d_FrontInfoAdaptor::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& thePairedFacet0_;
		ar& thePairedFacet1_;
		ar& thePairedFacet2_;

		ar& thePairedEdge3_;
		ar& thePairedEdge4_;
		ar& thePairedEdge5_;

		ar& theCreatedFacet0_;
		ar& theCreatedFacet1_;
		ar& theCreatedFacet2_;
		
		ar& theCreatedEdge3_;
		ar& theCreatedEdge4_;
		ar& theCreatedEdge5_;
	}

	template<>
	template<>
	void Aft3d_FrontInfoAdaptor::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar& thePairedFacet0_;
		ar& thePairedFacet1_;
		ar& thePairedFacet2_;

		ar& thePairedEdge3_;
		ar& thePairedEdge4_;
		ar& thePairedEdge5_;

		ar& theCreatedFacet0_;
		ar& theCreatedFacet1_;
		ar& theCreatedFacet2_;

		ar& theCreatedEdge3_;
		ar& theCreatedEdge4_;
		ar& theCreatedEdge5_;
	}
}