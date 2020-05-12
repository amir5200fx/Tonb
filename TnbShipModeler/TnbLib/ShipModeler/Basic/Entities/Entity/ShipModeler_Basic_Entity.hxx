#pragma once
#ifndef _ShipModeler_Basic_Entity_Header
#define _ShipModeler_Basic_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	namespace shipModelerLib
	{

		class Basic_Entity
			: public Global_Indexed
			, public Global_Named
			, public std::enable_shared_from_this<Basic_Entity>
		{

			/*Private Data*/

		protected:

			Basic_Entity()
			{}

			Basic_Entity
			(
				const Standard_Integer theIndex
			)
				: Global_Indexed(theIndex)
			{}

			Basic_Entity
			(
				const Standard_Integer theIndex,
				const word& theName
			)
				: Global_Indexed(theIndex)
				, Global_Named(theName)
			{}

		public:

			virtual ~Basic_Entity()
			{}

		};
	}
}

#endif // !_ShipModeler_Basic_Entity_Header
