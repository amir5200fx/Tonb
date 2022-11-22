#pragma once
#ifndef _Ship_Entity_Header
#define _Ship_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

namespace tnbLib
{

	class Ship_Entity
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

	protected:

		// default constructor [10/31/2022 Amir]

		Ship_Entity()
		{}


		// constructors [10/31/2022 Amir]

		Ship_Entity(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}


	public:

		// public functions and operators [10/31/2022 Amir]

		virtual ~Ship_Entity()
		{}

	};
}

#endif // !_Ship_Entity_Header
