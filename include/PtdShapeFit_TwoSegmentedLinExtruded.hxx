#pragma once
#ifndef _PtdShapeFit_TwoSegmentedLinExtruded_Header
#define _PtdShapeFit_TwoSegmentedLinExtruded_Header

#include <PtdShapeFit_Extruded.hxx>

namespace tnbLib
{

	class PtdShapeFit_TwoSegmentedLinExtruded
		: public PtdShapeFit_Extruded
	{

		/*Private Data*/

		Standard_Real theSegmented_;

		// Private functions and operators [4/10/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<PtdShapeFit_Extruded>(*this);
			ar& theSegmented_;
		}

	public:

		// default constructor [4/10/2023 Payvand]

		PtdShapeFit_TwoSegmentedLinExtruded()
			: theSegmented_(0)
		{}


		// constructors [4/10/2023 Payvand]

		PtdShapeFit_TwoSegmentedLinExtruded(const Standard_Integer theIndex, const word& theName)
			: PtdShapeFit_Extruded(theIndex, theName)
			, theSegmented_(0)
		{}


		// Public functions and operators [4/10/2023 Payvand]

		auto Segmented() const { return theSegmented_; }

		void SetSegmented(const Standard_Real theX) { theSegmented_ = theX; }

		TnbPtdShapeFit_EXPORT std::vector<std::shared_ptr<PtdShapeFit_Section::Parameters>>
			CalcParameters
			(
				const std::vector<std::shared_ptr<PtdShapeFit_Section>>& theSections,
				const gp_Ax1& theAxis,
				const std::vector<Standard_Real>& theXs
			) const override;

		TnbPtdShapeFit_EXPORT std::pair
			<
			std::shared_ptr<Cad_Shape>,
			std::vector<std::shared_ptr<PtdShapeFit_Section::Parameters>>
			>
			CreateExtrapolated
			(
				const std::vector<std::pair<std::shared_ptr<PtdShapeFit_Section::Parameters>, Standard_Real>>&,
				const std::shared_ptr<PtdShapeFit_Section>&,
				const gp_Ax1&,
				const std::vector<Standard_Real>&
			) const override;

		static TnbPtdShapeFit_EXPORT std::vector<Standard_Real>
			CalcLS
			(
				const std::vector<std::pair<Standard_Real, Standard_Real>>&, const Standard_Real theX
			);

	};

}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdShapeFit_TwoSegmentedLinExtruded);

#endif // !_PtdShapeFit_TwoSegmentedLinExtruded_Header
