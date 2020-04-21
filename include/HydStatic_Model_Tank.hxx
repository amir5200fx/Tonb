#pragma once
#ifndef _HydStatic_Model_Tank_Header
#define _HydStatic_Model_Tank_Header

#include <HydStatic_Model_Volume.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Model_Tank
			: public Model_Volume
		{

			/*Private Data*/

		public:

			Model_Tank();

			Model_Tank(const Standard_Integer theIndex);

			Model_Tank(const Standard_Integer theIndex, const word& theName);


		};
	}
}

#endif // !_HydStatic_Model_Tank_Header
