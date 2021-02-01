#pragma once
#ifndef _Marine_MidSectionApprox_Near_Header
#define _Marine_MidSectionApprox_Near_Header

#include <Marine_MidSectionApprox.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class MidSectionApprox_Near
			: public Marine_MidSectionApprox
		{

			/*Private Data*/

		public:

			MidSectionApprox_Near()
			{}

			TnbMarine_EXPORT void Perform(const Standard_Real x);


		};
	}
}

#endif // !_Marine_MidSectionApprox_Near_Header
