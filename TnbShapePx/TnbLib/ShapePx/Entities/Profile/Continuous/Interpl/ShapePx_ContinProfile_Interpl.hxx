#pragma once
#ifndef _ShapePx_ContinProfile_Interpl_Header
#define _ShapePx_ContinProfile_Interpl_Header

#include <ShapePx_ContinProfile.hxx>
#include <Global_Done.hxx>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

namespace tnbLib
{

	namespace shapePxLib
	{

		class ContinProfile_Interpl
			: public ShapePx_ContinProfile
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

			std::vector<offsetPoint> theQs_;

			interplType theType_;

			gsl_spline* theSpline_;
			gsl_interp_accel* theAcc_;

		public:


			ContinProfile_Interpl()
			{}

			ContinProfile_Interpl
			(
				const std::vector<offsetPoint>& theQs
			)
				: theQs_(theQs)
			{}

			ContinProfile_Interpl
			(
				std::vector<offsetPoint>&& theQs
			)
				: theQs_(std::move(theQs))
			{}

			ContinProfile_Interpl
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::vector<offsetPoint>& theQs
			)
				: ShapePx_ContinProfile(theIndex, theName)
				, theQs_(theQs)
			{}

			ContinProfile_Interpl
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::vector<offsetPoint>&& theQs
			)
				: ShapePx_ContinProfile(theIndex, theName)
				, theQs_(std::move(theQs))
			{}

			~ContinProfile_Interpl();

			Standard_Real Lower() const override;

			Standard_Real Upper() const override;

			Standard_Real LowerValue() const override;

			Standard_Real UpperValue() const override;

			Standard_Real Value(const Standard_Real x) const override;

			void Perform();

			void SetQs(const std::vector<offsetPoint>& theQs)
			{
				theQs_ = theQs;
			}

			void SetQs(std::vector<offsetPoint>&& theQs)
			{
				theQs_ = std::move(theQs);
			}

			void SetInterplType(const interplType t)
			{
				theType_ = t;
			}
		};
	}
}

#endif // !_ShapePx_ContinProfile_Interpl_Header
