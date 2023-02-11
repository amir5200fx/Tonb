#pragma once
#ifndef _Model_Entity_Header
#define _Model_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

namespace tnbLib
{

	class Model_Entity
		: public Global_Named
		, public Global_Indexed
	{

		/*Private Data*/

	protected:

		// default constructor [12/20/2022 Payvand]

		Model_Entity()
			: Global_Named("model_entity")
			, Global_Indexed(0)
		{}


		// constructors [12/20/2022 Payvand]

		Model_Entity(const Standard_Integer theIndex, const word& theName)
			: Global_Named(theName)
			, Global_Indexed(theIndex)
		{}

	public:

		// Public functions and operators [12/20/2022 Payvand]

	};
}

#endif // !_Model_Entity_Header
