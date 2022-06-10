#pragma once
#ifndef _Cad_MergeParaCurves_Entity_Header
#define _Cad_MergeParaCurves_Entity_Header

#include <Global_Indexed.hxx>

#include <memory>

namespace tnbLib
{

	namespace cadLib
	{

		namespace mergeParaCurves
		{

			class Entity
				: public Global_Indexed
				, public std::enable_shared_from_this<Entity>
			{

				/*Private Data*/

			protected:

				// default constructor [6/3/2022 Amir]

				Entity()
				{}

				// constructors [6/3/2022 Amir]

				explicit Entity(const Standard_Integer theIndex)
					: Global_Indexed(theIndex)
				{}


			public:

				// public functions and operators [6/3/2022 Amir]

			};
		}
	}
}

#endif // !_Cad_MergeParaCurves_Entity_Header
