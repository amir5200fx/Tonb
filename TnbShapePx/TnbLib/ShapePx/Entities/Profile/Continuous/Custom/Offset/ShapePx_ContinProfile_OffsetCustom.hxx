#pragma once
#ifndef _ShapePx_ContinProfile_OffsetCustom_Header
#define _ShapePx_ContinProfile_OffsetCustom_Header

#include <ShapePx_ContinProfile_Custom.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_ExtrProfile;

	namespace shapePxLib
	{

		class ContinProfile_OffsetCustom
			: public ContinProfile_Custom
		{

			/*Private Data*/

			std::shared_ptr<SectPx_ExtrProfile> theQ_;

		public:

			//- default constructor

			ContinProfile_OffsetCustom()
			{}


			//- constructors

			ContinProfile_OffsetCustom(const Standard_Integer theIndex, const word& theName);

			ContinProfile_OffsetCustom(const std::shared_ptr<SectPx_ExtrProfile>& theProfile);

			ContinProfile_OffsetCustom(const Standard_Integer theIndex, const word& theName, const std::shared_ptr<SectPx_ExtrProfile>& theProfile);


			//- public functions and operators

			const auto& ExtrudeProfile() const
			{
				return theQ_;
			}

			void SetExtrudeProfile(const std::shared_ptr<SectPx_ExtrProfile>& theQ)
			{
				theQ_ = theQ;
			}

			Standard_Real Lower() const override;

			Standard_Real Upper() const override;

			Standard_Real Value(const Standard_Real x) const override;
		};
	}
}

#endif // !_ShapePx_ContinProfile_OffsetCustom_Header
