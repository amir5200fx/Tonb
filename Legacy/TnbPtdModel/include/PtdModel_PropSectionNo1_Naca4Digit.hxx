#pragma once
#ifndef _PtdModel_PropSectionNo1_Naca4Digit_Header
#define _PtdModel_PropSectionNo1_Naca4Digit_Header

#include <PtdModel_PropSectionNo1.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class PropSectionNo1_Naca4Digit
			: public PtdModel_PropSectionNo1
		{

			/*Private Data*/

			Standard_Real theTrailEdgeGap_;


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<PtdModel_PropSectionNo1>(*this);
				ar & theTrailEdgeGap_;
			}

		public:

			//- default constructor

			PropSectionNo1_Naca4Digit()
				: theTrailEdgeGap_(0)
			{}


			//- constructors


			//- public functions and operators

			auto TrailEdgeGap() const
			{
				return theTrailEdgeGap_;
			}

			TnbPtdModel_EXPORT std::shared_ptr<PtdModel_BladeSectionQ>
				SectionQ
				(
					const Standard_Integer, 
					const PtdModel_PropBlade&
				) const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ptdModel::PropSectionNo1_Naca4Digit);

#endif // !_PtdModel_PropSectionNo1_Naca4Digit_Header
