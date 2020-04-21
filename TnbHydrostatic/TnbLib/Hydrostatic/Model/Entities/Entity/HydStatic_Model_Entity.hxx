#pragma once
#ifndef _HydStatic_ModelEntity_Header
#define _HydStatic_ModelEntity_Header

#include <HydStatic_Entity.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Model_Entity
			: public HydStatic_Entity
		{

			/*Private Data*/

		protected:

			Model_Entity();

			Model_Entity(const Standard_Integer theIndex);

			Model_Entity(const Standard_Integer theIndex, const word& theName);

		public:


		};
	}
}

#endif // !_HydStatic_ModelEntity_Header
