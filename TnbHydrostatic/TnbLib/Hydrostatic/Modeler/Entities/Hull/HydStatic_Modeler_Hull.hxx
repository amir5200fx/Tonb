#pragma once
#ifndef _HydStatic_Modeler_Hull_Header
#define _HydStatic_Modeler_Hull_Header

#include <HydStatic_Modeler_Volume.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Modeler_Hull
			: public Modeler_Volume
		{

			/*Private Data*/

		public:

			Modeler_Hull();

			Modeler_Hull(const Standard_Integer theIndex);

			Modeler_Hull(const Standard_Integer theIndex, const word& theName);


		};
	}
}

#endif // !_HydStatic_Modeler_Hull_Header
