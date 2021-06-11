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

#endif // !_PtdModel_PropSectionNo1_Naca4Digit_Header
