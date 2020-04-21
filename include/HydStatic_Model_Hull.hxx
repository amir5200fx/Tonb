#pragma once
#ifndef _HydStatic_Model_Hull_Header
#define _HydStatic_Model_Hull_Header

#include <HydStatic_Model_Volume.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Model_Hull
			: public Model_Volume
		{

			/*Private Data*/

		public:

			Model_Hull();

			Model_Hull(const Standard_Integer theIndex);

			Model_Hull(const Standard_Integer theIndex, const word& theName);


			
		};
	}
}

#endif // !_HydStatic_Model_Hull_Header
