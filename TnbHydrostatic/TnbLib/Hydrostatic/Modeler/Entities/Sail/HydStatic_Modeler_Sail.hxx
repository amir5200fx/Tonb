#pragma once
#ifndef _HydStatic_Modeler_Sail_Header
#define _HydStatic_Modeler_Sail_Header

#include <HydStatic_Modeler_Entity.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Modeler_Sail
			: public Modeler_Entity
		{

			/*Private Data*/

		public:

			Modeler_Sail();

			Modeler_Sail(const Standard_Integer theIndex);

			Modeler_Sail(const Standard_Integer theIndex, const word& theName);


		};
	}
}

#endif // !_HydStatic_Modeler_Sail_Header
