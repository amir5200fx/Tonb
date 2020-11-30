#pragma once
#ifndef _ShapePx_ContinProfile_Uniform_Header
#define _ShapePx_ContinProfile_Uniform_Header

#include <ShapePx_ContinProfile.hxx>

namespace tnbLib
{

	namespace shapePxLib
	{

		class ContinProfile_Uniform
			: public ShapePx_ContinProfile
		{

			/*Private Data*/

			Standard_Real theValue_;

			Standard_Real theX0_;
			Standard_Real theX1_;

		public:

			ContinProfile_Uniform()
				: theValue_(0)
			{}

			ContinProfile_Uniform
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const Standard_Real theValue,
				const Standard_Real x0,
				const Standard_Real x1
			)
				: ShapePx_ContinProfile(theIndex, theName)
				, theValue_(theValue)
				, theX0_(x0)
				, theX1_(x1)
			{}

			Standard_Real Lower() const override
			{
				return theX0_;
			}

			Standard_Real Upper() const override
			{
				return theX1_;
			}

			Standard_Real Value(const Standard_Real x) const override;

			std::vector<offsetPoint> RetrieveOffsets() const override;

			void SetValue(const Standard_Real x)
			{
				theValue_ = x;
			}

			void SetX0(const Standard_Real x0)
			{
				theX0_ = x0;
			}

			void SetX1(const Standard_Real x1)
			{
				theX1_ = x1;
			}
		};
	}
}

#endif // !_ShapePx_ContinProfile_Uniform_Header
