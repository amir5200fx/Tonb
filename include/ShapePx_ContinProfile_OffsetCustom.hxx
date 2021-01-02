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

			TnbShapePx_EXPORT ContinProfile_OffsetCustom
			(
				const Standard_Integer theIndex,
				const word& theName
			);

			TnbShapePx_EXPORT ContinProfile_OffsetCustom
			(
				const std::shared_ptr<SectPx_ExtrProfile>& theProfile
			);

			TnbShapePx_EXPORT ContinProfile_OffsetCustom
			(
				std::shared_ptr<SectPx_ExtrProfile>&& theProfile
			);

			TnbShapePx_EXPORT ContinProfile_OffsetCustom
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<SectPx_ExtrProfile>& theProfile
			);

			TnbShapePx_EXPORT ContinProfile_OffsetCustom
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::shared_ptr<SectPx_ExtrProfile>&& theProfile
			);


			//- public functions and operators

			Standard_Integer NbQs() const;

			const auto& ExtrudeProfile() const
			{
				return theQ_;
			}

			void SetExtrudeProfile(const std::shared_ptr<SectPx_ExtrProfile>& theQ)
			{
				theQ_ = theQ;
			}

			void SetExtrudeProfile(std::shared_ptr<SectPx_ExtrProfile>&& theQ)
			{
				theQ_ = std::move(theQ);
			}

			void SetInterplType(const interplType t)
			{
				theType_ = t;
			}

			TnbShapePx_EXPORT void Perform();

			TnbShapePx_EXPORT Standard_Boolean IsOffset() const override;

			TnbShapePx_EXPORT Standard_Real Lower() const override;

			TnbShapePx_EXPORT Standard_Real Upper() const override;

			TnbShapePx_EXPORT Standard_Real MinLower() const override;

			TnbShapePx_EXPORT Standard_Real MaxUpper() const override;

			TnbShapePx_EXPORT Standard_Real Value(const Standard_Real x) const override;

			TnbShapePx_EXPORT std::vector<offsetPoint> RetrieveOffsets() const override;

			TnbShapePx_EXPORT std::vector<Standard_Real> X() const override;

			TnbShapePx_EXPORT void Update() override;
		};
	}
}

#endif // !_ShapePx_ContinProfile_OffsetCustom_Header
