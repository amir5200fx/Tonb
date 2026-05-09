#pragma once
#ifndef _PtdModel_WingSectionNo1_Naca4Digit_Header
#define _PtdModel_WingSectionNo1_Naca4Digit_Header

#include <PtdModel_WingSectionNo1.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		class WingSectionNo1_Naca4Digit
			: public PtdModel_WingSectionNo1
		{

			/*Private Data*/

			Standard_Real theTrailEdgeGap_;

		public:

			//- default constructor

			WingSectionNo1_Naca4Digit()
				: theTrailEdgeGap_(0)
			{}


			//- constructors


			//- public functions and operators

			auto TrailEdgeGap() const
			{
				return theTrailEdgeGap_;
			}

			TnbPtdModel_EXPORT std::shared_ptr<PtdModel_WingSectionQ>
				SectionQ
				(
					const Standard_Integer,
					const PtdModel_Wing&
				) const override;
		};
	}
}

#endif // !_PtdModel_WingSectionNo1_Naca4Digit_Header
