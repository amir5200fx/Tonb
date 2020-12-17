#pragma once
#ifndef _ShapePx_ContinProfile_Custom_Header
#define _ShapePx_ContinProfile_Custom_Header

#include <ShapePx_ContinProfile.hxx>

namespace tnbLib
{

	namespace shapePxLib
	{

		class ContinProfile_Custom
			: public ShapePx_ContinProfile
		{

			/*Private Data*/

		protected:

			
			template<class... _Types>
			ContinProfile_Custom(_Types&&... _Args)
				: ShapePx_ContinProfile(_Args...)
			{}

		public:

			TnbShapePx_EXPORT virtual Standard_Boolean IsOffset() const;

			TnbShapePx_EXPORT virtual Standard_Boolean IsGenerated() const;
		};
	}
}

#endif // !_ShapePx_ContinProfile_Custom_Header
