#pragma once
#ifndef _Global_ColumnTable_Header
#define _Global_ColumnTable_Header

#include <Global_EntityTable.hxx>

namespace tnbLib
{

	class Global_ColumnTable
		: public Global_EntityTable
	{

		/*Private Data*/

	public:

		// default constructor [1/11/2022 Amir]

		Global_ColumnTable()
		{}

		// constructors [1/11/2022 Amir]

		explicit Global_ColumnTable(const word& theName)
			: Global_EntityTable(theName)
		{}

		explicit Global_ColumnTable(const std::vector<Standard_Real>& theValues)
			: Global_EntityTable(theValues)
		{}

		Global_ColumnTable(std::vector<Standard_Real>&& theValues)
			: Global_EntityTable(std::move(theValues))
		{}

		Global_ColumnTable
		(
			const word& theName,
			const std::vector<Standard_Real>& theValues
		)
			: Global_EntityTable(theName, theValues)
		{}

		Global_ColumnTable
		(
			const word& theName,
			std::vector<Standard_Real>&& theValues
		)
			: Global_EntityTable(theName, std::move(theValues))
		{}


		// public functions and operators [1/11/2022 Amir]
	};
}

#endif // !_Global_ColumnTable_Header
