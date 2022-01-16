#pragma once
#ifndef _Global_Table_Header
#define _Global_Table_Header

#include <Global_RowTable.hxx>
#include <Global_ColumnTable.hxx>
#include <Global_Module.hxx>

namespace tnbLib
{

	class Global_Table
		: public Global_Named
	{

	public:

		class EntitiesTable
		{

			/*Private Data*/

			std::vector<std::vector<Standard_Real>> theValues_;

		public:

			// default constructor [1/11/2022 Amir]

			EntitiesTable()
			{}

			// constructors [1/11/2022 Amir]

			TnbGlobal_EXPORT EntitiesTable
			(
				const Standard_Integer nbRows,
				const Standard_Integer nbColumns
			);

			// public functions and operators [1/11/2022 Amir]

			const auto& Values() const
			{
				return theValues_;
			}

			TnbGlobal_EXPORT Standard_Integer NbRows() const;
			TnbGlobal_EXPORT Standard_Integer NbColumns() const;

			TnbGlobal_EXPORT Standard_Real 
				Value
				(
					const Standard_Integer theRow,
					const Standard_Integer theCol
				) const;

			TnbGlobal_EXPORT void 
				Set
				(
					const Standard_Integer theRow, 
					const Standard_Integer theCol,
					const Standard_Real theValue
				);
		};

	private:

		/*Private Data*/

		Global_RowTable theRow_;
		Global_ColumnTable theColumn_;

		EntitiesTable theEntities_;

	public:

		// default constructor [1/11/2022 Amir]


		// constructors [1/11/2022 Amir]

		TnbGlobal_EXPORT Global_Table
		(
			const Global_RowTable& theRow, 
			const Global_ColumnTable& theCol
		);

		TnbGlobal_EXPORT Global_Table
		(
			Global_RowTable&& theRow,
			Global_ColumnTable&& theCol
		);


		// public functions and operators [1/11/2022 Amir]

		TnbGlobal_EXPORT std::pair<Standard_Real, Standard_Real> RowSpan() const;
		TnbGlobal_EXPORT std::pair<Standard_Real, Standard_Real> ColumnSpan() const;

		auto NbRows() const
		{
			return theRow_.Size();
		}

		auto NbColumns() const
		{
			return theColumn_.Size();
		}

		const auto& Row() const
		{
			return theRow_;
		}

		const auto& Column() const
		{
			return theColumn_;
		}

		const auto& Entities() const
		{
			return theEntities_;
		}

		auto& EntitiesRef()
		{
			return theEntities_;
		}

		TnbGlobal_EXPORT std::vector<Standard_Real>
			RowEntities
			(
				const Standard_Real xCol,
				const std::vector<Standard_Integer>&
			) const;

		TnbGlobal_EXPORT std::vector<Standard_Real>
			ColEntities
			(
				const Standard_Real xRow, 
				const std::vector<Standard_Integer>&
			) const;

		static TnbGlobal_EXPORT std::vector<std::pair<Standard_Real, Standard_Real>> 
			RowEntities
			(
				const Standard_Real xCol,
				const std::vector<Standard_Integer>&,
				const Global_Table&
			);

		static TnbGlobal_EXPORT std::vector<std::pair<Standard_Real, Standard_Real>> 
			ColEntities
			(
				const Standard_Real xRow,
				const std::vector<Standard_Integer>&,
				const Global_Table&
			);
		
	};
}

#endif // !_Global_Table_Header
