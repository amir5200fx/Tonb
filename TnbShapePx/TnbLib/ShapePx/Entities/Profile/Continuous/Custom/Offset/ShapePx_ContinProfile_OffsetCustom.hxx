#pragma once
#ifndef _ShapePx_ContinProfile_OffsetCustom_Header
#define _ShapePx_ContinProfile_OffsetCustom_Header

#include <Global_Done.hxx>
#include <ShapePx_ContinProfile_Custom.hxx>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_ExtrProfile;

	namespace shapePxLib
	{

		class ContinProfile_OffsetCustom
			: public ContinProfile_Custom
			, public Global_Done
		{

		public:

			enum class interplType
			{
				cspline,
				cspline_periodic,
				linear,
				polynomial,
				akima,
				akima_perodic,
				steffen
			};

		private:

			/*Private Data*/

			std::shared_ptr<SectPx_ExtrProfile> theQ_;


			interplType theType_;

			gsl_spline* theSpline_;
			gsl_interp_accel* theAcc_;

		public:

			//- default constructor

			ContinProfile_OffsetCustom()
			{}


			//- constructors

			ContinProfile_OffsetCustom
			(
				const Standard_Integer theIndex,
				const word& theName
			);

			ContinProfile_OffsetCustom
			(
				const std::shared_ptr<SectPx_ExtrProfile>& theProfile
			);

			ContinProfile_OffsetCustom
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<SectPx_ExtrProfile>& theProfile
			);


			//- public functions and operators

			const auto& ExtrudeProfile() const
			{
				return theQ_;
			}

			void SetExtrudeProfile(const std::shared_ptr<SectPx_ExtrProfile>& theQ)
			{
				theQ_ = theQ;
			}

			void SetInterplType(const interplType t)
			{
				theType_ = t;
			}

			void Perform();

			Standard_Boolean IsOffset() const override;

			Standard_Real Lower() const override;

			Standard_Real Upper() const override;

			Standard_Real Value(const Standard_Real x) const override;

			void Update() override;
		};
	}
}

#endif // !_ShapePx_ContinProfile_OffsetCustom_Header
