#pragma once
#ifndef _StbGMaker_IntplSect_Closer_Header
#define _StbGMaker_IntplSect_Closer_Header

#include <StbGMaker_IntplSect.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class IntplSect_Closer
			: public StbGMaker_IntplSect
		{

			/*Private Data*/

		public:

			IntplSect_Closer()
			{}

			IntplSect_Closer
			(
				const std::shared_ptr<Marine_CmpSection>& theS0,
				const std::shared_ptr<Marine_CmpSection>& theS1
			)
				: StbGMaker_IntplSect(theS0, theS1)
			{}

			void Perform(const gp_Pln& thePln);
		};
	}
}

#endif // !_StbGMaker_IntplSect_Closer_Header
