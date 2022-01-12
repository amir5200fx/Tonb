#pragma once
#ifndef _Global_RowTable_Header
#define _Global_RowTable_Header

#include <Global_EntityTable.hxx>

namespace tnbLib
{

	class Global_RowTable
		: public Global_EntityTable
	{

		/*Private Data*/

	public:

		// default constructor [1/11/2022 Amir]

		Global_RowTable()
		{}

		// constructors [1/11/2022 Amir]

		explicit Global_RowTable(const word& theName)
			: Global_EntityTable(theName)
		{}

		explicit Global_RowTable(const std::vector<Standard_Real>& theValues)
			: Global_EntityTable(theValues)
		{}

		Global_RowTable(std::vector<Standard_Real>&& theValues)
			: Global_EntityTable(std::move(theValues))
		{}

		Global_RowTable
		(
			const word& theName,
			const std::vector<Standard_Real>& theValues
		)
			: Global_EntityTable(theName, theValues)
		{}

		Global_RowTable
		(
			const word& theName,
			std::vector<Standard_Real>&& theValues
		)
			: Global_EntityTable(theName, std::move(theValues))
		{}

		
		// public functions and operators [1/11/2022 Amir]
	};
}

#endif // !_Global_RowTable_Header
