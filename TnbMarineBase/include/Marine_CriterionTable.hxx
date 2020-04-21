#pragma once
#ifndef _Marine_CriterionTable_Header
#define _Marine_CriterionTable_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Criterion;

	class Marine_CriterionTable
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Marine_Criterion>>
			theTable_;

	public:

		Marine_CriterionTable();


		auto NbRows() const
		{
			return (Standard_Integer)theTable_.size();
		}

		const auto& Table() const
		{
			return theTable_;
		}

		auto& ChangeTable()
		{
			return theTable_;
		}

		const auto& Row(const Standard_Integer theIndex) const
		{
			return theTable_[theIndex];
		}


	};
}

#endif // !_Marine_CriterionTable_Header
