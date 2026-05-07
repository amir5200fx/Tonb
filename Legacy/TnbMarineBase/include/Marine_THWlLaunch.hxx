#pragma once
#ifndef _Marine_THWlLaunch_Header
#define _Marine_THWlLaunch_Header

#include <Marine_Launch.hxx>

namespace tnbLib
{

	class Marine_THWlLaunch
		: public Marine_Launch
	{

		/*Private Data*/

		Standard_Real theTrim_;
		Standard_Real theHeel_;

	public:

		Marine_THWlLaunch();

		void Perform();
	};
}

#endif // !_Marine_THWlLaunch_Header
