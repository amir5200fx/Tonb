#pragma once
#ifndef _Cad_MergeParaCurves_Curve_Header
#define _Cad_MergeParaCurves_Curve_Header

#include <Cad_MergeParaCurves_Entity.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			class Curve
				: public Entity
			{

				/*Private Data*/

			protected:

				// default constructor [6/4/2022 Amir]

				Curve()
				{}

				// constructors [6/4/2022 Amir]

				explicit Curve(const Standard_Integer theIndex)
					: Entity(theIndex)
				{}

			public:

				// public functions and operators [6/4/2022 Amir]
			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_Curve_Header
