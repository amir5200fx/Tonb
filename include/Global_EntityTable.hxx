#pragma once
#ifndef _Global_EntityTable_Header
#define _Global_EntityTable_Header

#include <Global_Named.hxx>
#include <Standard_TypeDef.hxx>

#include <vector>

namespace tnbLib
{

	class Global_EntityTable
		: public Global_Named
	{

		/*Private Data*/

		std::vector<Standard_Real> theValues_;

	protected:

		// default constructor [1/11/2022 Amir]

		Global_EntityTable()
		{}

		// constructors [1/11/2022 Amir]

		explicit Global_EntityTable(const word& theName)
			: Global_Named(theName)
		{}

		explicit Global_EntityTable(const std::vector<Standard_Real>& theValues)
			: theValues_(theValues)
		{}

		Global_EntityTable(std::vector<Standard_Real>&& theValues)
			: theValues_(std::move(theValues))
		{}

		Global_EntityTable
		(
			const word& theName,
			const std::vector<Standard_Real>& theValues
		)
			: Global_Named(theName)
			, theValues_(theValues)
		{}

		Global_EntityTable
		(
			const word& theName,
			std::vector<Standard_Real>&& theValues
		)
			: Global_Named(theName)
			, theValues_(std::move(theValues))
		{}

	public:

		// public functions and operators [1/11/2022 Amir]

		auto Size() const
		{
			return (Standard_Integer)theValues_.size();
		}

		const auto& Values() const
		{
			return theValues_;
		}

		auto& ValuesRef()
		{
			return theValues_;
		}

		TnbGlobal_EXPORT std::pair<Standard_Real, Standard_Real> 
			SpanValues
			(
				const Standard_Integer theSpan
			) const;

		void SetValues(const std::vector<Standard_Real>& theValues)
		{
			theValues_ = theValues;
		}

		void SetValues(std::vector<Standard_Real>&& theValues)
		{
			theValues_ = std::move(theValues);
		}
	};
}

#endif // !_Global_EntityTable_Header
