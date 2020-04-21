#pragma once
#ifndef _HydStatic_Modeler_Entity_Header
#define _HydStatic_Modeler_Entity_Header

#include <HydStatic_Entity.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Modeler_Entity
			: public HydStatic_Entity
		{

			/*Private Data*/

		protected:

			Modeler_Entity();

			Modeler_Entity(const Standard_Integer theIndex);

			Modeler_Entity(const Standard_Integer theIndex, const word& theName);

		public:


		};
	}
}

#endif // !_HydStatic_Modeler_Entity_Header
