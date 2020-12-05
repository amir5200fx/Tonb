#pragma once
#ifndef _ShapePx_ContinProfile_ThreePoints_Header
#define _ShapePx_ContinProfile_ThreePoints_Header

#include <Global_Done.hxx>
#include <ShapePx_ContinProfile_Linear.hxx>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>


namespace tnbLib
{

	namespace shapePxLib
	{

		class ContinProfile_ThreePoints
			: public ContinProfile_Linear
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

			offsetPoint theQ2_;


			interplType theType_;

			gsl_spline* theSpline_;
			gsl_interp_accel* theAcc_;

		public:

			

			ContinProfile_ThreePoints()
			{}

			ContinProfile_ThreePoints
			(
				const offsetPoint& theQ0,
				const offsetPoint& theQ1,
				const offsetPoint& theQ2
			)
				: ContinProfile_Linear(theQ0, theQ1)
				, theQ2_(theQ2)
			{}

			ContinProfile_ThreePoints
			(
				const Standard_Integer theIndex,
				const word& theName,
				const offsetPoint& theQ0,
				const offsetPoint& theQ1,
				const offsetPoint& theQ2
			)
				: ContinProfile_Linear
				(
					theIndex, theName,
					theQ0, theQ1
				)
				, theQ2_(theQ2)
			{}

			ContinProfile_ThreePoints
			(
				offsetPoint&& theQ0,
				offsetPoint&& theQ1,
				offsetPoint&& theQ2
			)
				: ContinProfile_Linear
				(
					std::move(theQ0),
					std::move(theQ1)
				)
				, theQ2_(std::move(theQ2))
			{}

			ContinProfile_ThreePoints
			(
				const Standard_Integer theIndex,
				const word& theName,
				const offsetPoint& theQ0,
				const offsetPoint& theQ1,
				const offsetPoint& theQ2
			)
				: ContinProfile_Linear
				(
					theIndex, theName, 
					std::move(theQ0), 
					std::move(theQ1)
				)
				, theQ2_(std::move(theQ2))
			{}

			~ContinProfile_ThreePoints();

			auto X2() const
			{
				return theQ2_.x;
			}

			auto Value2() const
			{
				return theQ2_.y;
			}

			Standard_Real Upper() const override
			{
				return X2();
			}

			Standard_Real UpperValue() const override
			{
				return Value2();
			}

			Standard_Real Value
			(
				const Standard_Real x
			) const override;

			void Perform();

			void SetQ2(const offsetPoint& q2)
			{
				theQ2_ = q2;
			}

			void SetQ2(offsetPoint&& q2)
			{
				theQ2_ = std::move(q2);
			}

			void SetInterplType(const interplType t)
			{
				theType_ = t;
			}
		};
	}
}

#endif // !_ShapePx_ContinProfile_ThreePoints_Header