#pragma once
#ifndef _HydStatic_Modeler_Tank_Header
#define _HydStatic_Modeler_Tank_Header

#include <HydStatic_Modeler_Volume.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Modeler_Tank
			: public Modeler_Volume
		{

			/*Private Data*/

		public:

			Modeler_Tank();

			Modeler_Tank(const Standard_Integer theIndex);

			Modeler_Tank(const Standard_Integer theIndex, const word& theName);


		};
	}
}

#endif // !_HydStatic_Modeler_Tank_Header
